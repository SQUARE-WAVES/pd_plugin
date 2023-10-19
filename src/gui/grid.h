#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace gui
{
  struct grid
  {
    using rect = juce::Rectangle<int>;

    rect bounds;
    int rows;
    int cols;
    int padding;

    int row_h() const;
    int col_w() const;
    rect gridrow(const int y) const;
    rect gridcol(int x) const;
    rect gridbox(int x, int y) const;
    rect gridrect(int x, int y, int w, int h) const;
  };
}
