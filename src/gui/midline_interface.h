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

    class lfo_sync : public go_bar
    {
      using str = juce::String;

      juce::AudioProcessor* proccer;
      fparam* lfo_rate_param;

      public:
      lfo_sync(juce::AudioProcessor& proc,juce::AudioProcessorValueTreeState& st, str p_id):
      go_bar({"1/16","1/8","1/4","1/2","1"}),
      proccer(&proc),
      lfo_rate_param(static_cast<fparam*>(st.getParameter(p_id)))
      {
      }

      void set(float bpm,int idx)
      {
        float bar_seconds = (bpm/240.0f);
        float div = static_cast<float>(1<<(4-idx));


        *lfo_rate_param= bar_seconds * div;
      }

      void go(int idx) 
      {
        auto play_head = proccer->getPlayHead();

        if(play_head == nullptr)
        {
          set(120.0,idx);
          return;
        }

        auto mpi = play_head->getPosition();

        if(!mpi.hasValue())
        {
          set(120.0,idx);
          return;
        }

        auto mbpm = mpi->getBpm();

        if(!mbpm.hasValue())
        {
          set(120.0,idx);
        }

        set(static_cast<float>(*mbpm),idx);
      }
    };


    background bg;
    bar_slider porta;
    preset_bar porta_pres;
    bar_slider voice_count;

    bar_slider bend_range;
    bar_slider p_lfo_rate;
    choice_bar p_lfo_wave;
    lfo_sync p_lfo_sync;

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

    choice_bar mod_wheel;

    public:
    midline_interface(juce::AudioProcessor& proc,vts& st,str panel_name);
    void resized() override;
  };
}
