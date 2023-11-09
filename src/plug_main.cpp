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

static std::unique_ptr<iparam> int_param(String name, int min, int max, int start)
{
  return std::make_unique<iparam>(ParameterID{name,1},name,min,max,start);
}

static std::unique_ptr<cparam> choice_param(String name,const StringArray& choices,int start)
{
  return std::make_unique<cparam>(ParameterID{name,1},name,choices,start);
}

static float get_float_val(AudioProcessorValueTreeState& state,String name)
{
  return static_cast<fparam*>(state.getParameter(name))->get();
}

static int get_int_val(AudioProcessorValueTreeState& state,String name)
{
  return static_cast<iparam*>(state.getParameter(name))->get();
}

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

    choice_param("osc1_waveshaper",{"off","sig","chb","sin","tri"},0),
    float_param("osc1_waveshaper_base",0.0f,1.0f,0.0f),
    float_param("osc1_waveshaper_env_amt",0.0f,1.0f,0.0f),

    //env times are in seconds
    float_param("osc1_amp_env_attack",0.001f,4.0f,0.001f),
    float_param("osc1_amp_env_decay",0.001f,4.0f,0.001f),
    float_param("osc1_amp_env_sustain",0.0f,1.0f,1.0f),
    float_param("osc1_amp_env_release",0.001f,4.0f,0.001f),

    float_param("osc1_pd_env_attack",0.001f,4.0f,0.001f),
    float_param("osc1_pd_env_decay",0.001f,4.0f,0.001f),
    float_param("osc1_pd_env_sustain",0.0f,1.0f,0.0f),
    float_param("osc1_pd_env_release",0.001f,4.0f,0.001f),

    float_param("osc1_shp_env_attack",0.001f,4.0f,0.001f),
    float_param("osc1_shp_env_decay",0.001f,4.0f,0.001f),
    float_param("osc1_shp_env_sustain",0.0f,1.0f,0.0f),
    float_param("osc1_shp_env_release",0.001f,4.0f,0.001f),

    float_param("osc1_pitch_env_amt",-24.0f,24.0f,0.0f),
    float_param("osc1_pitch_env_attack",0.001f,4.0f,0.001f),
    float_param("osc1_pitch_env_decay",0.001f,4.0f,0.001f),
    float_param("osc1_pitch_env_sustain",0.0f,1.0f,0.0f),
    float_param("osc1_pitch_env_release",0.001f,4.0f,0.001f)
  ),

  std::make_unique<AudioProcessorParameterGroup>("osc2","osc2","-",
  
    float_param("osc2_vol",0.0f,1.0f,0.5f),
    choice_param("osc2_wave",{"sin","cos"},0),
    float_param("osc2_tune",-12.0f,12.0f,0.0f),

    choice_param("osc2_window",{"off","tri","ramp","para"},0),

    choice_param("osc2_phaseshaper",{"single","mirror","square","sync"},0),
    float_param("osc2_pd_base",0.0f,1.0f,0.0f),
    float_param("osc2_pd_env_amt",0.0f,1.0f,0.0f),

    choice_param("osc2_waveshaper",{"off","sig","chb","sin","tri"},0),
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
    float_param("osc2_shp_env_release",0.001f,4.0f,0.001f),

    float_param("osc2_pitch_env_amt",-24.0f,24.0f,0.0f),
    float_param("osc2_pitch_env_attack",0.001f,4.0f,0.001f),
    float_param("osc2_pitch_env_decay",0.001f,4.0f,0.001f),
    float_param("osc2_pitch_env_sustain",0.0f,1.0f,0.0f),
    float_param("osc2_pitch_env_release",0.001f,4.0f,0.001f)
  ),

  //shared stuff
  float_param("portamento",0.0f,1.0f,0.2f),
  float_param("cross_mod_vol",0.0f,1.0f,0.0f),
  float_param("lfo_rate",0.01f,30.0f,0.01f),
  float_param("o1_lfo_amt",0.0f,24.0f,0.0f),
  float_param("o2_lfo_amt",0.0f,24.0f,0.0f),
  choice_param("mod_wheel",{"off","on"},0),
  choice_param("lfo_wave",{"sin","tri","saw","-saw","sqr"},0),
  float_param("bend_range",0.0f,12.0f,2.0f),
  int_param("voices",1,8,8)

  /*
  float_param("mod_lfo1_rate",0.01f,30.0f,0.01f),
  float_param("mod1_o1_pd",0.0f,1.0f,0.0f),
  float_param("mod1_o1_ws",0.0f,1.0f,0.0f),
  float_param("mod1_o2_pd",0.0f,1.0f,0.0f),
  float_param("mod1_o2_ws",0.0f,1.0f,0.0f),

  float_param("mod_lfo2_rate",0.01f,30.0f,0.01f),
  float_param("mod2_o1_pd",0.0f,1.0f,0.0f),
  float_param("mod2_o1_ws",0.0f,1.0f,0.0f),
  float_param("mod2_o2_pd",0.0f,1.0f,0.0f),
  float_param("mod2_o2_ws",0.0f,1.0f,0.0f),
  */
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
  synth.voicer.set_max(1);
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
  auto osc1_vol = get_float_val(state,"osc1_vol");
  auto osc1_wave = get_enum_choice<waveform>(state,"osc1_wave");
  auto osc1_tune = get_float_val(state,"osc1_tune");
  auto osc1_window = get_enum_choice<window>(state,"osc1_window");
  auto osc1_phaseshaper = get_enum_choice<phase_shaper>(state,"osc1_phaseshaper");
  auto osc1_pd_base = get_float_val(state,"osc1_pd_base");
  auto osc1_pd_env_amt = get_float_val(state,"osc1_pd_env_amt");

  auto osc1_waveshaper = get_enum_choice<waveshaper>(state,"osc1_waveshaper");
  auto osc1_waveshaper_base = get_float_val(state,"osc1_waveshaper_base");
  auto osc1_waveshaper_env_amt = get_float_val(state,"osc1_waveshaper_env_amt");

  auto osc1_amp_env_attack = get_float_val(state,"osc1_amp_env_attack");
  auto osc1_amp_env_decay = get_float_val(state,"osc1_amp_env_decay");
  auto osc1_amp_env_sustain = get_float_val(state,"osc1_amp_env_sustain");
  auto osc1_amp_env_release = get_float_val(state,"osc1_amp_env_release");

  auto osc1_pd_env_attack = get_float_val(state,"osc1_pd_env_attack");
  auto osc1_pd_env_decay = get_float_val(state,"osc1_pd_env_decay");
  auto osc1_pd_env_sustain = get_float_val(state,"osc1_pd_env_sustain");
  auto osc1_pd_env_release = get_float_val(state,"osc1_pd_env_release");

  auto osc1_shp_env_attack = get_float_val(state,"osc1_shp_env_attack");
  auto osc1_shp_env_decay = get_float_val(state,"osc1_shp_env_decay");
  auto osc1_shp_env_sustain = get_float_val(state,"osc1_shp_env_sustain");
  auto osc1_shp_env_release = get_float_val(state,"osc1_shp_env_release");

  auto osc1_pitch_env_amt = get_float_val(state,"osc1_pitch_env_amt");
  auto osc1_pitch_env_attack = get_float_val(state,"osc1_pitch_env_attack");
  auto osc1_pitch_env_decay = get_float_val(state,"osc1_pitch_env_decay");
  auto osc1_pitch_env_sustain = get_float_val(state,"osc1_pitch_env_sustain");
  auto osc1_pitch_env_release = get_float_val(state,"osc1_pitch_env_release");

  auto osc2_vol = get_float_val(state,"osc2_vol");
  auto osc2_wave = get_enum_choice<waveform>(state,"osc2_wave");
  auto osc2_tune = get_float_val(state,"osc2_tune");
  auto osc2_window = get_enum_choice<window>(state,"osc2_window");
  auto osc2_phaseshaper = get_enum_choice<phase_shaper>(state,"osc2_phaseshaper");
  auto osc2_pd_base = get_float_val(state,"osc2_pd_base");
  auto osc2_pd_env_amt = get_float_val(state,"osc2_pd_env_amt");

  auto osc2_waveshaper = get_enum_choice<waveshaper>(state,"osc2_waveshaper");
  auto osc2_waveshaper_base = get_float_val(state,"osc2_waveshaper_base");
  auto osc2_waveshaper_env_amt = get_float_val(state,"osc2_waveshaper_env_amt");

  auto osc2_amp_env_attack = get_float_val(state,"osc2_amp_env_attack");
  auto osc2_amp_env_decay = get_float_val(state,"osc2_amp_env_decay");
  auto osc2_amp_env_sustain = get_float_val(state,"osc2_amp_env_sustain");
  auto osc2_amp_env_release = get_float_val(state,"osc2_amp_env_release");

  auto osc2_pd_env_attack = get_float_val(state,"osc2_pd_env_attack");
  auto osc2_pd_env_decay = get_float_val(state,"osc2_pd_env_decay");
  auto osc2_pd_env_sustain = get_float_val(state,"osc2_pd_env_sustain");
  auto osc2_pd_env_release = get_float_val(state,"osc2_pd_env_release");

  auto osc2_shp_env_attack = get_float_val(state,"osc2_shp_env_attack");
  auto osc2_shp_env_decay = get_float_val(state,"osc2_shp_env_decay");
  auto osc2_shp_env_sustain = get_float_val(state,"osc2_shp_env_sustain");
  auto osc2_shp_env_release = get_float_val(state,"osc2_shp_env_release");

  auto osc2_pitch_env_amt = get_float_val(state,"osc2_pitch_env_amt");
  auto osc2_pitch_env_attack = get_float_val(state,"osc2_pitch_env_attack");
  auto osc2_pitch_env_decay = get_float_val(state,"osc2_pitch_env_decay");
  auto osc2_pitch_env_sustain = get_float_val(state,"osc2_pitch_env_sustain");
  auto osc2_pitch_env_release = get_float_val(state,"osc2_pitch_env_release");

  auto o1_lfo_amt = get_float_val(state,"o1_lfo_amt");
  auto o2_lfo_amt = get_float_val(state,"o2_lfo_amt");
  auto cross_mod_vol = get_float_val(state,"cross_mod_vol");

  for(auto& v : synth.voices)
  {
    v.o1_vol.set_target(osc1_vol);
    v.osc1.set_wave(osc1_wave);
    v.osc1.set_tune(osc1_tune);
    v.osc1.set_window(osc1_window);
    v.osc1.set_phaseshaper(osc1_phaseshaper);
    v.osc1.set_pd(osc1_pd_base);
    v.osc1.set_pd_env_amt(osc1_pd_env_amt);

    v.osc1.set_waveshaper(osc1_waveshaper);
    v.osc1.set_shp(osc1_waveshaper_base);
    v.osc1.set_shp_env_amt(osc1_waveshaper_env_amt);

    v.osc1.amp_a(osc1_amp_env_attack);
    v.osc1.amp_d(osc1_amp_env_decay);
    v.osc1.amp_s(osc1_amp_env_sustain);
    v.osc1.amp_r(osc1_amp_env_release);

    v.osc1.pd_a(osc1_pd_env_attack);
    v.osc1.pd_d(osc1_pd_env_decay);
    v.osc1.pd_s(osc1_pd_env_sustain);
    v.osc1.pd_r(osc1_pd_env_release);

    v.osc1.shp_a(osc1_shp_env_attack);
    v.osc1.shp_d(osc1_shp_env_decay);
    v.osc1.shp_s(osc1_shp_env_sustain);
    v.osc1.shp_r(osc1_shp_env_release);

    v.osc1.set_ptch_env_amt(osc1_pitch_env_amt);
    v.osc1.ptch_a(osc1_pitch_env_attack);
    v.osc1.ptch_d(osc1_pitch_env_decay);
    v.osc1.ptch_s(osc1_pitch_env_sustain);
    v.osc1.ptch_r(osc1_pitch_env_release);

    //============================================================================
    v.o2_vol.set_target(osc2_vol);
    v.osc2.set_wave(osc2_wave);
    v.osc2.set_tune(osc2_tune);
    v.osc2.set_window(osc2_window);
    v.osc2.set_phaseshaper(osc2_phaseshaper);
    v.osc2.set_pd(osc2_pd_base);
    v.osc2.set_pd_env_amt(osc2_pd_env_amt);

    v.osc2.set_waveshaper(osc2_waveshaper);
    v.osc2.set_shp(osc2_waveshaper_base);
    v.osc2.set_shp_env_amt(osc2_waveshaper_env_amt);

    v.osc2.amp_a(osc2_amp_env_attack);
    v.osc2.amp_d(osc2_amp_env_decay);
    v.osc2.amp_s(osc2_amp_env_sustain);
    v.osc2.amp_r(osc2_amp_env_release);

    v.osc2.pd_a(osc2_pd_env_attack);
    v.osc2.pd_d(osc2_pd_env_decay);
    v.osc2.pd_s(osc2_pd_env_sustain);
    v.osc2.pd_r(osc2_pd_env_release);

    v.osc2.shp_a(osc2_shp_env_attack);
    v.osc2.shp_d(osc2_shp_env_decay);
    v.osc2.shp_s(osc2_shp_env_sustain);
    v.osc2.shp_r(osc2_shp_env_release);

    v.osc2.set_ptch_env_amt(osc2_pitch_env_amt);
    v.osc2.ptch_a(osc2_pitch_env_attack);
    v.osc2.ptch_d(osc2_pitch_env_decay);
    v.osc2.ptch_s(osc2_pitch_env_sustain);
    v.osc2.ptch_r(osc2_pitch_env_release);
    //============================================================================

    v.o1_lfo_amt.set_target(o1_lfo_amt);
    v.o2_lfo_amt.set_target(o2_lfo_amt);
    v.xmod_vol.set_target(cross_mod_vol);
  }

  //================================================================================
  synth.portamento_time(get_float_val(state,"portamento"));
  synth.pitch_lfo.set_rate(get_float_val(state,"lfo_rate"));
  synth.pitch_lfo.set_wave(get_enum_choice<lfo::wave>(state,"lfo_wave"));
  synth.set_bend_range(get_float_val(state,"bend_range"));
  synth.voicer.set_max(get_int_val(state,"voices"));
  synth.mw_on(static_cast<float>(get_choice_val(state, "mod_wheel")));
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
    synth.set_pitch_bend(m.getPitchWheelValue());
  }

  if(m.isControllerOfType(1))
  {
    synth.set_mod_wheel(static_cast<float>(m.getControllerValue()));
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


