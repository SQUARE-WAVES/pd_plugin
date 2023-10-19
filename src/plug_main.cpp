#include "plug_main.h"
#include "synth/specialosc.h"
#include <algorithm>
#include <memory>

using namespace juce;
using fparam = AudioParameterFloat;
using iparam = AudioParameterInt;
using cparam = AudioParameterChoice;

template <class T> using rng = NormalisableRange<T>;

static std::unique_ptr<fparam> float_param(String name, float min, float max, float start)
{
  return std::make_unique<fparam>(ParameterID{name,1},name,rng<float>(min,max),start);
}

/*static std::unique_ptr<iparam> int_param(String name, int min, int max, int start)
{
  return std::make_unique<iparam>(ParameterID{name,1},name,min,max,start);
}*/

static std::unique_ptr<cparam> choice_param(String name,const StringArray& choices,int start)
{
  return std::make_unique<cparam>(ParameterID{name,1},name,choices,start);
}

static float get_float_val(AudioProcessorValueTreeState& state,String name)
{
  return static_cast<fparam*>(state.getParameter(name))->get();
}

/*static int get_int_val(AudioProcessorValueTreeState& state,String name)
{
  return static_cast<iparam*>(state.getParameter(name))->get();
}*/

static int get_choice_val(AudioProcessorValueTreeState& state,String name)
{
  return static_cast<cparam*>(state.getParameter(name))->getIndex();
}

template<class T> T get_enum_choice(AudioProcessorValueTreeState& state,String name)
{
  int cindex = get_choice_val(state, name);
  return static_cast<T>(cindex);
}

pd_proc::pd_proc():
AudioProcessor(get_buses()),
state(*this,nullptr,"state",
{
  std::make_unique<AudioProcessorParameterGroup>("osc1","osc1","-",
    float_param("osc1_vol",0.0f,1.0f,0.5f),
    choice_param("osc1_wave",{"sin","cos"},0),
    float_param("osc1_tune",-12.0f,12.0f,0.0f),

    choice_param("osc1_window",{"off","tri","ramp","para"},0),

    choice_param("osc1_phaseshaper",{"single","mirror","square","sync"},0),
    float_param("osc1_pd_base",0.0f,1.0f,0.0f),
    float_param("osc1_pd_env_amt",0.0f,1.0f,0.0f),

    choice_param("osc1_waveshaper",{"off","tri","c3"},0),
    float_param("osc1_waveshaper_base",0.0f,1.0f,0.0f),
    float_param("osc1_waveshaper_env_amt",0.0f,1.0f,0.0f),

    //env times are in seconds
    float_param("osc1_amp_env_attack",0.001f,4.0f,0.001f),
    float_param("osc1_amp_env_decay",0.001f,4.0f,0.001f),
    float_param("osc1_amp_env_sustain",0.0f,1.0f,1.0f),
    float_param("osc1_amp_env_release",0.001f,4.0f,0.001f),

    //env times are in seconds
    float_param("osc1_pd_env_attack",0.001f,4.0f,0.001f),
    float_param("osc1_pd_env_decay",0.001f,4.0f,0.001f),
    float_param("osc1_pd_env_sustain",0.0f,1.0f,0.0f),
    float_param("osc1_pd_env_release",0.001f,4.0f,0.001f),

    //env times are in seconds
    float_param("osc1_shp_env_attack",0.001f,4.0f,0.001f),
    float_param("osc1_shp_env_decay",0.001f,4.0f,0.001f),
    float_param("osc1_shp_env_sustain",0.0f,1.0f,0.0f),
    float_param("osc1_shp_env_release",0.001f,4.0f,0.001f)
  ),

  std::make_unique<AudioProcessorParameterGroup>("osc2","osc2","-",
    float_param("osc2_vol",0.0f,1.0f,0.5f),
    choice_param("osc2_wave",{"sin","cos"},0),
    float_param("osc2_tune",-12.0f,12.0f,0.0f),

    choice_param("osc2_window",{"off","tri","ramp","para"},0),

    choice_param("osc2_phaseshaper",{"single","mirror","square","sync"},0),
    float_param("osc2_pd_base",0.0f,1.0f,0.0f),
    float_param("osc2_pd_env_amt",0.0f,1.0f,0.0f),

    choice_param("osc2_waveshaper",{"off","tri","c3"},0),
    float_param("osc2_waveshaper_base",0.0f,1.0f,0.0f),
    float_param("osc2_waveshaper_env_amt",0.0f,1.0f,0.0f),

    //env times are in seconds
    float_param("osc2_amp_env_attack",0.001f,4.0f,0.001f),
    float_param("osc2_amp_env_decay",0.001f,4.0f,0.001f),
    float_param("osc2_amp_env_sustain",0.0f,1.0f,1.0f),
    float_param("osc2_amp_env_release",0.001f,4.0f,0.001f),

    //env times are in seconds
    float_param("osc2_pd_env_attack",0.001f,4.0f,0.001f),
    float_param("osc2_pd_env_decay",0.001f,4.0f,0.001f),
    float_param("osc2_pd_env_sustain",0.0f,1.0f,0.0f),
    float_param("osc2_pd_env_release",0.001f,4.0f,0.001f),

    //env times are in seconds
    float_param("osc2_shp_env_attack",0.001f,4.0f,0.001f),
    float_param("osc2_shp_env_decay",0.001f,4.0f,0.001f),
    float_param("osc2_shp_env_sustain",0.0f,1.0f,0.0f),
    float_param("osc2_shp_env_release",0.001f,4.0f,0.001f)
  ),

  //shared stuff
  float_param("portamento",0.0f,1.0f,0.2f),
  float_param("cross_mod_vol",0.0f,1.0f,0.0f),
})
{
}

bool pd_proc::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  const auto& main_out = layouts.getMainOutputChannelSet();
  const auto& main_in  = layouts.getMainInputChannelSet();

  bool input_good = main_in.isDisabled() || main_in == main_out;
  bool max_stereo = main_out.size() <= 2;

  return input_good && max_stereo; 
}

void pd_proc::prepareToPlay(double sr, int )
{
  synth.set_samplerate(static_cast<float>(sr));
}

void pd_proc::releaseResources()
{
  //nothing here
}

void pd_proc::reset()
{
  
}

void pd_proc::do_parameters()
{
  synth.o1_vol.set_target(get_float_val(state,"osc1_vol"));

  synth.osc1.set_wave(get_enum_choice<waveform>(state,"osc1_wave"));
  synth.osc1.set_tune(get_float_val(state,"osc1_tune"));

  synth.osc1.set_window(get_enum_choice<window>(state,"osc1_window"));

  synth.osc1.set_phaseshaper(get_enum_choice<phase_shaper>(state,"osc1_phaseshaper"));
  synth.osc1.set_pd(get_float_val(state,"osc1_pd_base"));
  synth.osc1.set_pd_env_amt(get_float_val(state,"osc1_pd_env_amt"));

  synth.osc1.set_waveshaper(get_enum_choice<waveshaper>(state,"osc1_waveshaper"));
  synth.osc1.set_shp(get_float_val(state,"osc1_waveshaper_base"));
  synth.osc1.set_shp_env_amt(get_float_val(state,"osc1_waveshaper_env_amt"));

  synth.osc1.amp_a(get_float_val(state,"osc1_amp_env_attack"));
  synth.osc1.amp_d(get_float_val(state,"osc1_amp_env_decay"));
  synth.osc1.amp_s(get_float_val(state,"osc1_amp_env_sustain"));
  synth.osc1.amp_r(get_float_val(state,"osc1_amp_env_release"));

  synth.osc1.pd_a(get_float_val(state,"osc1_pd_env_attack"));
  synth.osc1.pd_d(get_float_val(state,"osc1_pd_env_decay"));
  synth.osc1.pd_s(get_float_val(state,"osc1_pd_env_sustain"));
  synth.osc1.pd_r(get_float_val(state,"osc1_pd_env_release"));

  synth.osc1.shp_a(get_float_val(state,"osc1_shp_env_attack"));
  synth.osc1.shp_d(get_float_val(state,"osc1_shp_env_decay"));
  synth.osc1.shp_s(get_float_val(state,"osc1_shp_env_sustain"));
  synth.osc1.shp_r(get_float_val(state,"osc1_shp_env_release"));

  //================================================================================
  synth.o2_vol.set_target(get_float_val(state,"osc2_vol"));
  synth.osc2.set_wave(get_enum_choice<waveform>(state,"osc2_wave"));
  synth.osc2.set_tune(get_float_val(state,"osc2_tune"));

  synth.osc2.set_window(get_enum_choice<window>(state,"osc2_window"));

  synth.osc2.set_phaseshaper(get_enum_choice<phase_shaper>(state,"osc2_phaseshaper"));
  synth.osc2.set_pd(get_float_val(state,"osc2_pd_base"));
  synth.osc2.set_pd_env_amt(get_float_val(state,"osc2_pd_env_amt"));

  synth.osc2.set_waveshaper(get_enum_choice<waveshaper>(state,"osc2_waveshaper"));
  synth.osc2.set_shp(get_float_val(state,"osc2_waveshaper_base"));
  synth.osc2.set_shp_env_amt(get_float_val(state,"osc2_waveshaper_env_amt"));

  synth.osc2.amp_a(get_float_val(state,"osc2_amp_env_attack"));
  synth.osc2.amp_d(get_float_val(state,"osc2_amp_env_decay"));
  synth.osc2.amp_s(get_float_val(state,"osc2_amp_env_sustain"));
  synth.osc2.amp_r(get_float_val(state,"osc2_amp_env_release"));

  synth.osc2.pd_a(get_float_val(state,"osc2_pd_env_attack"));
  synth.osc2.pd_d(get_float_val(state,"osc2_pd_env_decay"));
  synth.osc2.pd_s(get_float_val(state,"osc2_pd_env_sustain"));
  synth.osc2.pd_r(get_float_val(state,"osc2_pd_env_release"));

  synth.osc2.shp_a(get_float_val(state,"osc2_shp_env_attack"));
  synth.osc2.shp_d(get_float_val(state,"osc2_shp_env_decay"));
  synth.osc2.shp_s(get_float_val(state,"osc2_shp_env_sustain"));
  synth.osc2.shp_r(get_float_val(state,"osc2_shp_env_release"));

  synth.portamento_time(get_float_val(state,"portamento"));
  synth.xmod_vol.set_target(get_float_val(state,"cross_mod_vol"));
}

void pd_proc::handle_midi_message(const juce::MidiMessage m)
{
  if(m.isNoteOn())
  {
    synth.note_on(m.getNoteNumber());
  }

  if(m.isNoteOff())
  {
    synth.note_off(m.getNoteNumber());
  }

  if(m.isPitchWheel())
  {
    synth.voicer.set_pitch_bend(m.getPitchWheelValue());
  }
}
  
void pd_proc::processBlock (a_buff<float>& buffer, m_buff& mbuff)
{
  buffer.clear();
  do_parameters();

  int frame = 0;

  for(auto msg_data : mbuff)
  {
    while(msg_data.samplePosition > frame)
    {
      float smp = synth.value();

      for(int c=0;c<buffer.getNumChannels();++c)
      {
        buffer.addSample(c,frame,smp);
      }

      synth.update();
      ++frame;
    }

    handle_midi_message(msg_data.getMessage());
  }

  while(frame < buffer.getNumSamples())
  {
    float smp = synth.value();

    for(int c=0;c<buffer.getNumChannels();++c)
    {
      buffer.addSample(c,frame,smp);
    }

    synth.update();
    ++frame;
  }
}

void pd_proc::processBlock (a_buff<double>& buffer, m_buff& mbuff)
{
  buffer.clear();
  do_parameters();

  int frame = 0;

  for(auto msg_data : mbuff)
  {
    while(msg_data.samplePosition > frame)
    {
      float smp = synth.value();

      for(int c=0;c<buffer.getNumChannels();++c)
      {
        buffer.addSample(c,frame,smp);
      }

      synth.update();
      ++frame;
    }

    handle_midi_message(msg_data.getMessage());
  }

  while(frame < buffer.getNumSamples())
  {
    float smp = synth.value();

    for(int c=0;c<buffer.getNumChannels();++c)
    {
      buffer.addSample(c,frame,smp);
    }

    synth.update();
    ++frame;
  }
}

void pd_proc::getStateInformation(juce::MemoryBlock& destination)
{
  auto xml_state = state.copyState().createXml();

  if(xml_state)
  {
    copyXmlToBinary(*xml_state,destination);
  }
}

void pd_proc::setStateInformation(const void* data , int bytes)
{
  auto xml_state = getXmlFromBinary(data,bytes);
  if(xml_state)
  {
    state.replaceState(ValueTree::fromXml (*xml_state));
  }
}

//================================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new pd_proc();
}


