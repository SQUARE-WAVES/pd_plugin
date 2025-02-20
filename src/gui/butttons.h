#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "types.h"
#include "colors.h"
#include "fonts.h"

namespace gui
{
  class choice_bar : public juce::Component, juce::AudioParameterChoice::Listener
  {
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
      g.setFont(gui::fonts::small);

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
      g.setFont(gui::fonts::small);
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

  class go_bar : public juce::Component
  {
    using str = juce::String;
    using vec = std::vector<str>;

    vec opts;
    int selected = -1;
 
    std::array<color,4> colors = 
    {
      cga::black,
      cga::hi_cyan, 
      cga::white, 
      cga::magenta
    };

    inline int count()
    { 
      return static_cast<int>(opts.size()); 
    }

    inline str& opt(int idx)
    {
      return opts.at(static_cast<size_t>(idx));
    }

    public:
    go_bar(vec&& ps):
    opts(ps)
    {
    }

    ~go_bar() override
    {
    }

    void paint(gfx& g) override
    {

      g.setFont(gui::fonts::small);

      int cw = (getWidth())/count();
      int x = 0;
      
      g.setColour(colors[0]);
      g.fillAll();

      for(int i=0; i<count();++i)
      {
        rect bnds = {x,0,cw,getHeight()};

        g.setColour(colors[1]);
        g.drawRect(bnds);

        if(i == selected)
        {
          g.setColour(colors[3]);
          g.fillRect(bnds);
        }

        g.setColour(colors[2]);
        g.drawFittedText(opt(i),bnds,jst::centred,1);
        x += cw;
      }
    }

    void mouseDown(const juce::MouseEvent& ev) override
    {
      auto cw = getWidth()/count();
      int idx = ev.x/cw;
      selected = idx;
      go(idx);
      repaint();
    }

    void mouseUp(const juce::MouseEvent& ) override
    {
      selected = -1;
      repaint();
    }

    virtual void go(int idx) = 0;
  };

  class btn : public juce::Component 
  {
    str txt;
    bool holding = false;

    public:
    btn(str text):txt(text)
    {
    }

    void paint(gfx& g) override
    {

      g.setFont(gui::fonts::small);
      auto bg = holding ? cga::magenta : cga::black;
      g.setColour(bg);
      g.fillAll();

      g.setColour(cga::hi_cyan);
      g.drawRect(0,0,getWidth(),getHeight());

      g.setColour(cga::white);
      g.drawText(txt,0,0,getWidth(),getHeight(),jst::centred);
    }

    void mouseDown(const mev& ev) override
    {
      if(ev.mods.isLeftButtonDown())
      {
        holding = true;
        repaint();
      }
    }

    void mouseUp(const mev& ev) override
    {
      if(holding && ev.mods.isLeftButtonDown())
      {
        holding = false;
        repaint();
        on_click();
      }
    }

    virtual void on_click() = 0;
  };
}
