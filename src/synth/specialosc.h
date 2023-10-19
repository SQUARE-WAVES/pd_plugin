#ifndef SPECIAL_OSC_DOT_H
#define SPECIAL_OSC_DOT_H

#include "phase_accumulator.h"
#include "phase_shapers.h"
#include "waveforms.h"
#include "waveshapers.h"
#include "window_funcs.h"

enum class waveform
{
  sin = 0,
  cos = 1
};

enum class phase_shaper
{
  single = 0,
  mirrored = 1,
  square = 2,
  sync = 3
};

enum class window
{
  off = 0,
  tri = 1,
  ramp = 2,
  parabola = 3
};

enum class waveshaper
{
  off = 0,
  tri = 1,
  c3 = 2
};

struct special_oscillator
{
  waveform wf = waveform::cos;
  phase_shaper ps = phase_shaper::single;
  window wnd = window::off;
  waveshaper shp = waveshaper::off;
  phase_accumulator phasor;

  float pd_amt = 0.0f;
  float shp_amt = 0.0f;

  float value();
  float value(const float ph);
  void update();

  static float calc_phase(const float raw_ph, const float pd_amt, const phase_shaper ps);
  static float calc_wave(const float ph, const waveform wf);
  static float calc_window(const float ph, const window wnd);
  static float calc_shaper(const float wave, const float shp_amt, const waveshaper shp);
};

#endif
