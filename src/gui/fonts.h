#pragma once

#include <juce_graphics/juce_graphics.h>
#include <font_binary.h>

namespace gui
{
  namespace
  {
    using typ = juce::Typeface;
    using fnt = juce::Font;
  }

  const auto tf = typ::createSystemTypefaceFor
  (
    font_binary::PxPlus_IBM_CGA_ttf,
    font_binary::PxPlus_IBM_CGA_ttfSize
  );

  namespace fonts {
    const fnt normal(tf);
    const fnt small = normal.withHeight(11.0);
  }
}
