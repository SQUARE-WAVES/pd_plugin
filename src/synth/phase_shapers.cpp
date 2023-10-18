#include <cmath>
#include "phase_shapers.h"

float phase_shapers::x_distort(const float ph, const float amt)
{
  float half_point = 0.5f + (amt/2.0f);

  if(ph < half_point)
  {
    return ph * (0.5f/half_point);
  }
  else 
  {
    return 0.5f + ( (ph - half_point) * (0.5f/(1.0f-half_point))); 
  }
}

float phase_shapers::minusx_distort(const float ph, const float amt)
{
  float half_point = 0.5f - (amt/2.0f);

  if(ph < half_point)
  {
    return ph * (0.5f/half_point);
  }
  else 
  {
    return 0.5f + ( (ph - half_point) * (0.5f/(1.0f-half_point))); 
  }
}

float phase_shapers::mirror_phase(const float ph,const float amt)
{
  if(ph >= 0.5f)
  {
    const float vph = 2.0f * (1.0f - ph);
    return 1.0f - (0.5f * phase_shapers::minusx_distort(vph,amt));
  }
  else 
  {
    return 0.5f * phase_shapers::minusx_distort(2*ph,amt);
  }
}

float phase_shapers::two_peaks(const float ph, const float amt)
{
  const float stretch = 0.25f * amt;
  const float p1_left = 0.25f - stretch;
  const float p1_right = 0.25f + stretch;

  const float p2_left = 0.75f - stretch;
  const float p2_right = 0.75f + stretch;

  if(ph <= p1_left)
  {
    return std::lerp(0.0f,0.25f,ph/p1_left);
  }
  
  if(ph<=p1_right)
  {
   return .25;
  }
  
  if(ph<=p2_left)
  {
   return std::lerp(0.25f,0.75f,(ph-p1_right)/(p2_left - p1_right));
  }

  if(ph <= p2_right)
  {
    return 0.75f;
  }

  return std::lerp(0.75f,1.0f,(ph-p2_right)/(1.0f-p2_right));
}

float phase_shapers::stretch_middle(const float ph, const float amt)
{
  float left = 0.5f * (1.0f - amt);
  float right = 0.5f * (1.0f + amt);

  if(ph <= left)
  {
    return std::lerp(0.0f,0.5f,ph/left);
  }

  if(ph <= right)
  {
    return 0.5;
  }

  return std::lerp(0.5f,1.0f,(ph-right)/(1.0f - right));
}

float phase_shapers::sync(const float ph, const float amt)
{
  const float multiple = (amt * 12.0f) + 1.0f;
  const float big_phase = ph*multiple;
  const float wrapped = fmodf(big_phase,1.0f);
  return (wrapped < 0.0f) ? 1.0f + wrapped : wrapped;
}
