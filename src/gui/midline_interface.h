#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "colors.h"
#include "butttons.h"
#include "sliders.h"

namespace gui
{
  class midline_interface : public juce::Component
  {
    using gfx = juce::Graphics;
    using str = juce::String;
    using color = juce::Colour;
    using rect = juce::Rectangle<int>;
    using jst = juce::Justification;

    class background : public juce::Component
    {
      str panel_name;

      public:
      background(str name):panel_name(name){}
      rect text_box();

      void paint(gfx& g) override;
    };

    background bg;

    //the voicer
    bar_slider porta;
    preset_bar porta_pres;
    bar_slider bend_range;


    //the pitch_lfo
    bar_slider p_lfo_rate;
    choice_bar p_lfo_wave;
    bar_slider o1_lfo_amt;
    bar_slider o2_lfo_amt;

    //the output mixer
    bar_slider o1_out;
    bar_slider o2_out;
    bar_slider xmod_out;

    public:
    midline_interface(juce::AudioProcessorValueTreeState& st,str panel_name);
    void resized() override;
  };
}
