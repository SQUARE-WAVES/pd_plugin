#pragma once

#include "phase_accumulator.h"

struct lfo
{
  enum class wave
  {
    sin = 0,
    tri = 1,
    saw = 2,
    upsaw = 3,
    sqr = 4
  };

  float value();
  void update();

  void set_samplerate(float sr);
  void set_rate(float nr);
  void set_wave(wave w);

  void reset();

  private:

  static float sin(float ph); 
  static float tri(float ph); 
  static float saw(float ph); 
  static float upsaw(float ph); 
  static float sqr(float ph); 

  wave wv;
  phase_accumulator phasor;
};
