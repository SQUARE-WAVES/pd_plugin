#include "grid.h"

using rect = gui::grid::rect;

int gui::grid::row_h() const
{
  return bounds.getHeight() / rows;
}

int gui::grid::col_w() const
{
  return bounds.getWidth() / rows;
}

rect gui::grid::gridrow(const int y) const
{
  const rect out = 
  {
    padding, 
    (y * row_h() ) +padding, 
    bounds.getWidth() - (2*padding),
    row_h() - (2 * padding)
  };

  return out;
}

rect gui::grid::gridcol(int x) const
{
  const rect out =
  {
    (x * col_w()) + padding,
    padding,
    col_w() - ( 2 * padding),
    bounds.getHeight() - (2 * padding)
  };

  return out;
}

rect gui::grid::gridbox(int x, int y) const
{
  const int corner_x = x * col_w();
  const int corner_y = y * row_h();
      
  return {
    corner_x + padding,
    corner_y + padding,
    col_w() - (2*padding),
    row_h() - (2*padding)
  };
}

rect gui::grid::gridrect(int x, int y, int w, int h) const
{
  const int corner_x = x * col_w();
  const int corner_y = y * row_h();

  return {
    corner_x + padding,
    corner_y + padding,
    w * col_w() - (2*padding),
    h * row_h() - (2*padding)
  };
}
