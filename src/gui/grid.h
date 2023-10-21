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

    int row_h() const;
    int col_w() const;
    rect row(const int y, const int xpd=0,const int ypd=0) const;
    rect col(int x,const int xpd=0, const int ypd=0) const;
    rect cell(int x, int y,const int xpd=0,const int ypd=0) const;
    rect cell_rect(int x, int y, int w, int h, const int xpd= 0, const int ypd=0) const;
  };
}
