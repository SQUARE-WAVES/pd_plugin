#include "grid.h"

using rect = gui::grid::rect;

int gui::grid::row_h() const
{
  return bounds.getHeight() / rows;
}

int gui::grid::col_w() const
{
  return bounds.getWidth() / cols;
}

rect gui::grid::row(const int y, const int xpd,const int ypd) const
{
  const rect out = 
  {
    bounds.getX() + xpd, 
    bounds.getY() + (y * row_h() ) + ypd, 
    bounds.getWidth() - (2 * xpd),
    row_h() - (2 * ypd)
  };

  return out;
}

rect gui::grid::col(int x, const int xpd, const int ypd) const
{
  const rect out =
  {
    bounds.getX() + (x * col_w()) + xpd,
    bounds.getY() + ypd,
    col_w() - ( 2 * xpd),
    bounds.getHeight() - (2 * ypd)
  };

  return out;
}

rect gui::grid::cell(int x, int y, const int xpd, const int ypd) const
{
  const int corner_x = bounds.getX() + (x * col_w());
  const int corner_y = bounds.getY() + (y * row_h());
      
  return {
    corner_x + xpd,
    corner_y + ypd,
    col_w() - (2*xpd),
    row_h() - (2*ypd)
  };
}

rect gui::grid::cell_rect(int x, int y, int w, int h, const int xpd, const int ypd) const
{
  const int corner_x = bounds.getX() + (x * col_w());
  const int corner_y = bounds.getY() + (y * row_h());

  return {
    corner_x + xpd,
    corner_y + ypd,
    w * col_w() - (2*xpd),
    h * row_h() - (2*ypd)
  };
}
