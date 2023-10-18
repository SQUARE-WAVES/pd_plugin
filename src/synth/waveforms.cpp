#include <cmath>
#include <numbers>

#include "waveforms.h"

constexpr float tau = std::numbers::pi_v<float> * 2.0f;

float waveforms::sin(const float ph)
{
  return sinf(ph * tau);
}

float waveforms::cos(const float ph)
{
  return cosf(ph * tau);
}

