#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace gui
{
  namespace
  {
    using gfx = juce::Graphics;
    using str = juce::String;
    using color = juce::Colour;
    using rect = juce::Rectangle<int>;
    using jst = juce::Justification;
    using mev = juce::MouseEvent;

    using cparam = juce::AudioParameterChoice;
    using fparam = juce::AudioParameterFloat;
    using vts = juce::AudioProcessorValueTreeState;
  }
}
