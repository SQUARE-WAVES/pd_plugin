#pragma once

#include <cmath>

namespace curves
{
  //this assumes 0 to 1!
  inline float upside_down_exp(float v)
  {
    return 2.0f - std::exp2f(1.0f-v);
  }

  inline float inv_curve(float f)
  {
    return (-2.0f/(f+1.0f)) + 2.0f;
  }
}
