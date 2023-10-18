#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "colors.h"

namespace gui
{
  class choice_bar : public juce::Component, juce::AudioParameterChoice::Listener
  {
    using cparam = juce::AudioParameterChoice;
    using gfx = juce::Graphics;
    using str = juce::String;
    using color = juce::Colour;
    using rect = juce::Rectangle<int>;
    using jst = juce::Justification;

    std::array<color,4> colors = 
    {
      cga::black,
      cga::hi_cyan, 
      cga::white, 
      cga::magenta
    };

    cparam* param;

    public:
    choice_bar(juce::AudioProcessorValueTreeState& st, str param_id)
    {
      param = static_cast<cparam*>(st.getParameter(param_id));
      param->addListener(this);
    }

    ~choice_bar() override
    {
      param->removeListener(this);
    }

    void paint(gfx& g) override
    {
      auto cs = param->choices;
      auto cw = (getWidth())/cs.size();
      int x = 0;
      
      g.setColour(colors[0]);
      g.fillAll();

      for(str& s : cs)
      {
        rect bnds = {x,0,cw,getHeight()};

        if(s == *param)
        {
          g.setColour(colors[3]);
          g.fillRect(bnds);
        }

        g.setColour(colors[1]);
        g.drawRect(bnds);

        g.setColour(colors[2]);
        g.drawFittedText(s,bnds,jst::centred,1);
        x += cw;
      }
    }

    void mouseDown(const juce::MouseEvent& ev) override
    {
      auto cs = param->choices;
      auto cw = getWidth()/cs.size();

      int idx = ev.x/cw;

      *param = idx;
    }

    void parameterValueChanged(int ,float) override
    {
      repaint();
    }

    void parameterGestureChanged(int,bool) override
    {
      //nothing
    }
  };

  class preset_bar : public juce::Component, juce::AudioParameterFloat::Listener
  {
    using fparam = juce::AudioParameterFloat;
    using gfx = juce::Graphics;
    using str = juce::String;
    using color = juce::Colour;
    using rect = juce::Rectangle<int>;
    using jst = juce::Justification;
    using vec = std::vector<float>;

    vec presets;
 
    std::array<color,4> colors = 
    {
      cga::black,
      cga::hi_cyan, 
      cga::white, 
      cga::magenta
    };

    fparam* param;

    inline int count()
    { 
      return static_cast<int>(presets.size()); 
    }

    public:
    preset_bar(juce::AudioProcessorValueTreeState& st,str param_id, vec&& ps):
    presets(std::move(ps)),
    param(static_cast<fparam*>(st.getParameter(param_id)))
    {
      param->addListener(this);
    }

    ~preset_bar() override
    {
      param->removeListener(this);
    }

    void paint(gfx& g) override
    {
      int cw = (getWidth())/count();
      int x = 0;
      
      g.setColour(colors[0]);
      g.fillAll();

      for(float& v : presets)
      {
        rect bnds = {x,0,cw,getHeight()};

        if(juce::approximatelyEqual(v,(float)(*param)))
        {
          g.setColour(colors[3]);
          g.fillRect(bnds);
        }

        g.setColour(colors[1]);
        g.drawRect(bnds);

        g.setColour(colors[2]);
        g.drawFittedText(str(v),bnds,jst::centred,1);
        x += cw;
      }
    }

    void mouseDown(const juce::MouseEvent& ev) override
    {
      auto cw = getWidth()/count();

      int idx = ev.x/cw;

      *param = presets.at(static_cast<size_t>(idx));
    }

    void parameterValueChanged(int ,float) override
    {
      repaint();
    }

    void parameterGestureChanged(int,bool) override
    {
      //nothing
    }
  };
}
