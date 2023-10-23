#ifndef PHASE_GUY_DOT_H
#define PHASE_GUY_DOT_H

#include <cmath>

class phase_accumulator
{
  float current_phase = 0;
  float max;
  float rateInverse = 1.0f/48000.0f;
  float increment = 0.01f;
  float frequency = 220.0f;

  inline void calculate_increment()
  {
    increment = (frequency * max) * rateInverse;
  }

  public:
  phase_accumulator(float mx = 1.0f):max(mx){}

  inline void set_samplerate(float sr)
  {
    rateInverse = 1.0f/sr;
    calculate_increment();
  }

  inline void set_frequency(float f)
  {
    frequency = f;
    calculate_increment();
  }

  inline float value() const
  {
    return current_phase;
  }

  inline void update()
  {
    float next_phase = current_phase + increment;
    float wrapped = fmodf(next_phase,max);
    current_phase = (wrapped < 0) ? max + wrapped : wrapped;
  }

  inline void reset()
  {
    current_phase = 0.0f;
  }
};

#endif
