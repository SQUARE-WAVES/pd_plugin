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

