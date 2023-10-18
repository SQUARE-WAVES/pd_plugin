#include <cmath>
#include "window_funcs.h"

float windows::tri(const float ph)
{
  float quad = 0.0f;
  float remainder = modff(2.0f*ph,&quad);

  if(quad < 1.0f)
  {
    return remainder;
  }
  else 
  {
    return 1.0f - remainder;
  }
}

float windows::ramp(const float ph)
{
 return 1.0f - ph;
}

//it's an upside down parabola
float windows::para(const float ph)
{
  return 1.0f - (4.0f * ( ph*ph - ph + 0.25f));
}
