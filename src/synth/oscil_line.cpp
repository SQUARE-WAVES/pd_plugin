#include "oscil_line.h"
#include <cmath>
#include <algorithm>

#include "curves.h"

oscil_line::oscil_line():
pd_amt(0.0f,0.0f,0.99f),
pd_env_amt(0.0f,0.0f,0.99f),
shp_amt(0.0f,0.0f,1.0f),
shp_env_amt(0.0f,0.0f,1.0f),
pitch_env_amt(0.0f,-24.0f,24.0),
tune(0.0f,-12.0f,12.0f),
pd_mod_amt(0.0f,0.0f,1.0),
ws_mod_amt(0.0f,0.0f,1.0),
amp_env(0.01f,0.1f,1.0f,0.01f),
pd_env(0.01f,0.1f,1.0f,0.01f),
shp_env(0.01f,0.1f,1.0f,0.01f),
pitch_env(0.01f,0.1f,1.0f,0.01f)
{
}

float oscil_line::value()
{
  float oscil = osc.value();
  float env = amp_env.value();

  return oscil * curves::exp(env);
}

void oscil_line::update(float mod_in)
{
  pd_amt.update();
  pd_env_amt.update();
  
  shp_amt.update();
  shp_env_amt.update();

  pitch_env_amt.update();

  amp_env.update();
  pd_env.update();
  shp_env.update();
  pitch_env.update();

  tune.update();
  float pitch_env_val = pitch_env_amt.value() * pitch_env.value();
  float tuned_freq = 440.0f * std::exp2( ((freq-69.0f) + tune.value() + pitch_env_val) /12.0f);
  osc.phasor.set_frequency(tuned_freq);

  pd_mod_amt.update();
  ws_mod_amt.update();

  float pd_mod_val = pd_mod_amt.value() * mod_in;
  osc.pd_amt = pd_amt.value() + (pd_env_amt.value() * pd_env.value()) + pd_mod_val;
  osc.pd_amt = std::clamp(osc.pd_amt,0.0f,1.0f);
  osc.pd_amt = curves::inv_curve(osc.pd_amt);

  float shp_mod_val = ws_mod_amt.value() * mod_in;
  float shp_env_val = curves::exp_decay(shp_env_amt.value()) * shp_env.value();

  osc.shp_amt = shp_amt.value() + shp_env_val + shp_mod_val;
  osc.shp_amt = std::clamp(osc.shp_amt,0.0f,1.0f);
  osc.shp_amt = osc.shp_amt;

  osc.update();
}

bool oscil_line::done()
{
  return amp_env.done();
}

void oscil_line::set_samplerate(float sr)
{
  amp_env.set_samplerate(sr);
  pd_env.set_samplerate(sr);
  shp_env.set_samplerate(sr);
  pitch_env.set_samplerate(sr);
  osc.phasor.set_samplerate(sr);
}

void oscil_line::set_freq(float f)
{
  freq = f;
}

void oscil_line::set_gate(bool g)
{
  gate = g;
  amp_env.set_gate(g);
  pd_env.set_gate(g);
  shp_env.set_gate(g);
  pitch_env.set_gate(g);
}

void oscil_line::set_wave(waveform wf)
{
  osc.wf = wf;
}

void oscil_line::set_phaseshaper(phase_shaper shp)
{
  osc.ps = shp;
}

void oscil_line::set_window(window wnd)
{
  osc.wnd = wnd;
}

void oscil_line::set_waveshaper(waveshaper shp)
{
  osc.shp = shp;
}

void oscil_line::set_tune(float t)
{
  tune.set_target(t);
}

void oscil_line::set_ptch_env_amt(float v)
{
  pitch_env_amt.set_target(v);
}

void oscil_line::set_pd(float v)
{
  pd_amt.set_target(v);
}

void oscil_line::set_pd_env_amt(float v)
{
  pd_env_amt.set_target(v);
}

void oscil_line::set_pd_mod_amt(float v)
{
  pd_mod_amt.set_target(v);
}
  
void oscil_line::set_shp(float v)
{
  shp_amt.set_target(v);
}

void oscil_line::set_shp_env_amt(float v)
{
  shp_env_amt.set_target(v);
}

void oscil_line::set_shp_mod_amt(float v)
{
  ws_mod_amt.set_target(v);
}

void oscil_line::amp_a(float v)
{
  amp_env.set_a(v);
}

void oscil_line::amp_d(float v)
{
  amp_env.set_d(v);
}

void oscil_line::amp_s(float v)
{
  amp_env.set_s(v);
}

void oscil_line::amp_r(float v)
{
  amp_env.set_r(v);
}

void oscil_line::pd_a(float v)
{
  pd_env.set_a(v);
}

void oscil_line::pd_d(float v)
{
  pd_env.set_d(v);
}

void oscil_line::pd_s(float v)
{
  pd_env.set_s(v);
}

void oscil_line::pd_r(float v)
{
  pd_env.set_r(v);
}

void oscil_line::shp_a(float v)
{
  shp_env.set_a(v);
}

void oscil_line::shp_d(float v)
{
  shp_env.set_d(v);
}

void oscil_line::shp_s(float v)
{
  shp_env.set_s(v);
}

void oscil_line::shp_r(float v)
{
  shp_env.set_r(v);
}

void oscil_line::ptch_a(float v)
{
  pitch_env.set_a(v);
}

void oscil_line::ptch_d(float v)
{
  pitch_env.set_d(v);
}

void oscil_line::ptch_s(float v)
{
  pitch_env.set_s(v);
}

void oscil_line::ptch_r(float v)
{
  pitch_env.set_r(v);
}
