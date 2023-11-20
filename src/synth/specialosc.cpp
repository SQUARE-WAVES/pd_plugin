#include "specialosc.h"
#include "waveshapers.h"

float special_oscillator::calc_phase(const float raw_ph, const float pd_amt, const phase_shaper ps)
{
  switch(ps)
  {
    case phase_shaper::single:
      return phase_shapers::x_distort(raw_ph,pd_amt);
    break;

    case phase_shaper::mirrored:
      return phase_shapers::mirror_phase(raw_ph,pd_amt);
    break;   

    case phase_shaper::square:
      return phase_shapers::two_peaks(raw_ph,pd_amt);
    break;

    case phase_shaper::sync:
      return phase_shapers::sync(raw_ph,pd_amt);
    break;
  }
}

float special_oscillator::calc_wave(const float ph,const waveform wf)
{
  switch(wf)
  {
    case waveform::sin:
      return waveforms::sin(ph);
    break;

    case waveform::cos:
      return waveforms::cos(ph);
    break;
  }
}

float special_oscillator::calc_window(const float ph, const window wnd)
{
  switch(wnd)
  {
    case window::off:
      return 1.0f;
    break;

    case window::tri:
      return windows::tri(ph);
    break;

    case window::ramp:
      return windows::ramp(ph);
    break;

    case window::parabola:
      return windows::para(ph);
    break;
  }
}

float special_oscillator::calc_shaper(const float wave,const float shp_amt, const waveshaper shp)
{
  switch(shp)
  {
    case waveshaper::off:
      return wave;
    break;

    case waveshaper::tri:
      return waveshapers::tri(wave, shp_amt);
    break;

    case waveshaper::sin:
      return waveshapers::sin(wave,shp_amt);
    break;

    case waveshaper::sig:
      return waveshapers::sigm(wave,shp_amt);
    break;
  }
}

void special_oscillator::update()
{
  phasor.update();
}

float special_oscillator::value()
{
  const float raw_ph = phasor.value();
  const float ph = calc_phase(raw_ph,pd_amt,ps);
  const float wave = calc_wave(ph,wf);
  const float window = calc_window(raw_ph,wnd);
  float f = calc_shaper(window * wave,shp_amt,shp);

  return f;
}

float special_oscillator::value(const float raw_ph)
{
  const float ph = calc_phase(raw_ph,pd_amt,ps);
  const float wave = calc_wave(ph,wf);
  const float window = calc_window(raw_ph,wnd);
  float f = calc_shaper(window * wave,shp_amt,shp);

  return f;
}
