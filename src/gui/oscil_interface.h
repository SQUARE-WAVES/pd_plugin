#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "colors.h"
#include "sliders.h"
#include "butttons.h"

namespace gui
{

  class oscil_interface : public juce::Component
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

    //the wave
    choice_bar wave;
    bar_slider tune;
    preset_bar tune_presets;

    //the window
    choice_bar windows;

    //the pd
    choice_bar pd_waves;
    bar_slider pd_base;
    bar_slider pd_env_amt;

    //the shaper
    choice_bar shaper_form;
    bar_slider shaper_base;
    bar_slider shaper_env_amt;

    //pd_env
    bar_slider pd_env_a;
    bar_slider pd_env_d;
    bar_slider pd_env_s;
    bar_slider pd_env_r;

    //shp_env
    bar_slider shp_env_a;
    bar_slider shp_env_d;
    bar_slider shp_env_s;
    bar_slider shp_env_r;

    //amp_env
    bar_slider amp_env_a;
    bar_slider amp_env_d;
    bar_slider amp_env_s;
    bar_slider amp_env_r;

    public:
    oscil_interface(juce::AudioProcessorValueTreeState& st,str prefix,str panel_name);
    void resized() override;
  };
}
