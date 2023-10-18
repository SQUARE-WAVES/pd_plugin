#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "butttons.h"
#include "colors.h"
#include "sliders.h"

namespace gui
{
  class voicer_interface : public juce::Component
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

    bar_slider porta;
    preset_bar porta_pres;

    public:
    voicer_interface(juce::AudioProcessorValueTreeState& st,str panel_name);
    void resized();
  };
}
