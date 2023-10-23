#include <numbers>
#include <cmath>
#include <algorithm>

#include "lfo.h"

constexpr float tau = std::numbers::pi_v<float> * 2.0f;

float lfo::sin(float ph)
{
  return sinf(ph * tau);
}

float lfo::tri(float ph)
{
  if(ph < 0.25f)
  {
    return 4.0f * ph;
  }
  else if(ph < 0.75f)
  {
    float nph = 4.0f * (ph - 0.25f);
    return 1.0f - nph;
  }
  else 
  {
    float nph = 4.0f * (ph - 0.75f);
    return -1.0f + nph;
  }
}

float lfo::saw(float ph)
{
  return 1.0f - (2.0f * ph);
}

float lfo::upsaw(float ph)
{
  return -1.0f + (2.0f * ph);
}

float lfo::sqr(float ph)
{
  if(ph <= 0.5)
  {
    return 1.0f;
  }
  else
  {
    return -1.0f;
  }
}

void lfo::set_samplerate(float sr)
{
  phasor.set_samplerate(sr);
}

void lfo::set_rate(float nr)
{
  float real_rate = std::clamp(nr,0.01f,30.0f);
  phasor.set_frequency(real_rate);
}

void lfo::set_wave(wave w)
{
  wv = w;
}

void lfo::reset()
{
  phasor.reset();
}

float lfo::value()
{
  float ph = phasor.value();

  switch(wv)
  {
    case wave::sin:
    {
      return sin(ph);
    }
    break;
    case wave::tri:
    {
      return tri(ph);
    }
    break;
    case wave::saw:
    {
      return saw(ph);
    }
    break;
    case wave::upsaw:
    {
      return upsaw(ph);
    }
    break;
    case wave::sqr:
    {
      return sqr(ph);
    }
    break;
  }
}

void lfo::update()
{
  phasor.update(); 
}


