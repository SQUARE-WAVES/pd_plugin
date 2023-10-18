#ifndef PHASE_SHAPERS_DOT_H
#define PHASE_SHAPERS_DOT_H

//these are all just functions
namespace phase_shapers
{
  float x_distort(const float ph,const float amt);
  float minusx_distort(const float ph,const float amt);
  float stretch_middle(const float ph, const float amt);
  float mirror_phase(const float ph,const float amt);
  float two_peaks(const float ph, const float amt);
  float sync(const float ph, const float amt);
}

#endif
