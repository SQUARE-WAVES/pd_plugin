#pragma once

#include <cmath>

namespace curves
{
  //this assumes 0 to 1!
  inline float upside_down_exp(float v)
  {
    return 2.0f - std::exp2f(1.0f-v);
  }

  inline float exp_decay(float v,float rate = 1.0f)
  {
    return 1.0f - (1.0f/std::exp2f(v*rate));
  }

  inline float exp(float v)
  {
    return std::exp2f(v) - 1.0f;
  }

  inline float inv_curve(float f)
  {
    return (-2.0f/(f+1.0f)) + 2.0f;
  }
}
