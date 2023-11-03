#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "types.h"
#include "sliders.h"
#include "butttons.h"

namespace gui
{
  class midline_interface : public juce::Component
  {
    class env_sync_btn : public btn
    {
      fparam* a1;
      fparam* a2;

      fparam* d1;
      fparam* d2;

      fparam* s1;
      fparam* s2;

      fparam* r1;
      fparam* r2;

      public:
      env_sync_btn
      (
        vts& st,str name, 
        str a1n,str d1n, str s1n,str r1n,
        str a2n,str d2n,str s2n,str r2n
      );

      void on_click();
    };

    class background : public juce::Component
    {
      str panel_name;

      public:
      background(str name):panel_name(name){}
      rect text_box();

      void paint(gfx& g) override;
    };

    background bg;
    bar_slider porta;
    preset_bar porta_pres;
    bar_slider voice_count;

    bar_slider bend_range;
    bar_slider p_lfo_rate;
    choice_bar p_lfo_wave;

    bar_slider o1_lfo_amt;
    bar_slider o2_lfo_amt;
    bar_slider o1_out;
    bar_slider o2_out;
    bar_slider xmod_out;

    env_sync_btn top_pch;
    env_sync_btn btm_pch;

    env_sync_btn top_pd;
    env_sync_btn btm_pd;
    
    env_sync_btn top_ws;
    env_sync_btn btm_ws;
    
    env_sync_btn top_amp;
    env_sync_btn btm_amp;

    public:
    midline_interface(juce::AudioProcessorValueTreeState& st,str panel_name);
    void resized() override;
  };
}
