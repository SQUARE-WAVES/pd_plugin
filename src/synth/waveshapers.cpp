#include <cmath>
#include "waveshapers.h"

float waveshapers::tri(const float v,const float amt)
{
  const float val = v * (1.0f + (amt*4.0f));

  const float flipper = fmodf(val,2.0f);

  if(flipper >= 1.0f)
  {
    return 2.0f - flipper;
  }
  else if(flipper <= -1.0f)
  {
    return -(2.0f + flipper);
  }
  else 
  {
    return flipper;
  }
}

float waveshapers::cheby3(const float v, const float amt)
{
  const float c1 = v * (1.0f-amt);
  const float cextr = amt * (( (4.0f * v * v *v) + (2.0f * v * v) - (3.0f * v) - 1.0f)/2.0f);
  return c1 + cextr;
}

