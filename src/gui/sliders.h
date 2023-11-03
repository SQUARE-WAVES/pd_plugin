#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "types.h"
#include "colors.h"

namespace gui
{
  class bar_slider : public juce::Slider, juce::AudioProcessorValueTreeState::SliderAttachment
  {
    using cids = juce::Slider::ColourIds;

    public:

      bar_slider(juce::AudioProcessorValueTreeState& state, str param_id):
      juce::AudioProcessorValueTreeState::SliderAttachment(state,param_id,*this)
      {
        setSliderStyle(juce::Slider::LinearBar);
        setColour(cids::textBoxOutlineColourId,cga::hi_cyan);
        setColour(cids::textBoxTextColourId,cga::white);
        setColour(cids::backgroundColourId,cga::black);
        setColour(cids::trackColourId,cga::magenta);
      }
  };
}
