#include <cmath>
#include "waveforms.h"
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

float waveshapers::sin(const float v,const float amt)
{
  const float val = v * (1.0f + (amt * 6.0f));
  return waveforms::sin(val/4.0f);
}

float waveshapers::cheby(const float v, const float amt)
{
  const float c1 = v; 
  const float c2 = (2.0f * v * c1) - 1.0f;
  const float c3 = (2.0f * v * c2) - c1;
  const float c4 = (2.0f * v * c3) - c2;
  const float c5 = (2.0f * v * c4) - c3;
  const float c6 = (2.0f * v * c5) - c4;
  const float cextr = (c1 + c2 + c3 + c4 + c5 + c6)/6.0f;

  return (c1* (1.0f-amt)) + cextr*amt;
}

float waveshapers::sigm(const float v, const float amt)
{
  if(v > 0.0f)
  {
    float c = (-1.1f/((10.0f*v) + 1.0f)) + 1.1f;
    return (v * (1.0f - amt)) + c*amt;
  }
  else
  {
    float c = (-1.1f/((10.0f * -v) + 1.0f)) + 1.1f;
    return (v * (1.0f - amt)) + (-c * amt);
  }

}
