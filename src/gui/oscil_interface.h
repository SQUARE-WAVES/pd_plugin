#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "types.h"
#include "colors.h"
#include "grid.h"
#include "sliders.h"
#include "butttons.h"
#include "wave_drawer.h"

namespace gui
{
  class oscil_interface : public juce::Component
  {
    class background : public juce::Component
    {
      str panel_name;

      public:
      background(str name):panel_name(name){}
      rect text_box();

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

    //pitch_env
    bar_slider pitch_env_amt;
    bar_slider pitch_env_a;
    bar_slider pitch_env_d;
    bar_slider pitch_env_s;
    bar_slider pitch_env_r;

    wave_drawer wd;

    public:
    oscil_interface(juce::AudioProcessorValueTreeState& st,str prefix,str panel_name);
    void resized() override;
  };
}
