#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>

#include "gui/mixer_interface.h"
#include "synth/pd_syn.h"
#include "gui/butttons.h"
#include "gui/oscil_interface.h"
#include "gui/midline_interface.h"
#include "gui/wave_drawer.h"

class pd_proc : public juce::AudioProcessor
{
  template<class T> using a_buff = juce::AudioBuffer<T>;
  using m_buff = juce::MidiBuffer;
  using str = juce::String;
  using gfx = juce::Graphics;
  using slider = juce::Slider;
  using slider_attach = juce::AudioProcessorValueTreeState::SliderAttachment;

  //methods in plug_editor.cpp
  class editor : public juce::AudioProcessorEditor
  {
    pd_proc& proc;

    gui::oscil_interface o1;
    gui::midline_interface mid;
    gui::oscil_interface o2;

    public:
    editor(pd_proc& pxer);

    void paint(gfx& g) override;
    void resized() override;
  };

  juce::AudioProcessorValueTreeState state;

  static inline BusesProperties get_buses()
  {
    return BusesProperties()
      .withInput ("Input", juce::AudioChannelSet::stereo(), true)
      .withOutput ("Output", juce::AudioChannelSet::stereo(), true);
  }

  pd_syn synth;

  void do_parameters();
  void handle_midi_message(const juce::MidiMessage m);

  public:
  pd_proc();
  ~pd_proc() override = default;

  bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
  void prepareToPlay(double sr, int spb) override;
  void releaseResources() override;
  void reset() override;
  
  void processBlock (a_buff<float>& buffer, m_buff& midiMessages) override;
  void processBlock (a_buff<double>& buffer, m_buff& midiMessages) override;

  inline bool hasEditor() const override { return true; }
  
  inline juce::AudioProcessorEditor* createEditor() override
  {
    return new editor(*this);
  }

  inline const str getName() const override { return "vee-ess-test"; }
  inline bool acceptsMidi() const override { return true; }
  inline bool producesMidi() const override { return true; }
  inline double getTailLengthSeconds() const override { return 0.0; }
  inline int getNumPrograms() override { return 0; }
  inline int getCurrentProgram() override { return 0; }
  inline void setCurrentProgram (int) override {}
  inline const str getProgramName (int) override { return "the void"; }
  inline void changeProgramName (int, const str&) override {}

  void getStateInformation(juce::MemoryBlock& dest) override;
  void setStateInformation(const void* data, int size) override;
};

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter();
