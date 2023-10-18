#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "colors.h"
#include "sliders.h"

namespace gui
{
  class mixer_interface : public juce::Component
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
      void paint(gfx& g) override;
    };

    background bg;

    bar_slider osc_1_vol;
    bar_slider osc_2_vol;
    bar_slider xmod_vol;

    public:
    mixer_interface(juce::AudioProcessorValueTreeState& st,str panel_name);
    void resized();
  };
}
