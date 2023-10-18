#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "../synth/specialosc.h"

namespace gui
{
  class wave_drawer : public juce::Component, public juce::RangedAudioParameter::Listener
  {
    using gfx = juce::Graphics;
    using str = juce::String;
    using vts = juce::AudioProcessorValueTreeState;
    using rect = juce::Rectangle<int>;
    using jst = juce::Justification;

    using cparam = juce::AudioParameterChoice;
    using fparam = juce::AudioParameterFloat;

    str panel_name;

    cparam* wave;
    cparam* ps;
    cparam* ws;
    cparam* wnd;

    fparam* pd_amt;
    fparam* ws_amt;

    special_oscillator draw_osc;
   
    void do_parameters();
    void parameterValueChanged(int ,float) override;
    void parameterGestureChanged(int,bool) override;

    public:
      wave_drawer(vts& st,str pname,str p1,str p2,str p3, str p4,str p5,str p6);
      ~wave_drawer() override;
      void paint(gfx& g) override;  
  };
}
