#ifndef OSCIL_LINE_DOT_H
#define OSCIL_LINE_DOT_H

#include "target_param.h"
#include "specialosc.h"
#include "envelopes.h"

class oscil_line
{
  target_float pd_amt;
  target_float pd_env_amt;

  target_float shp_amt;
  target_float shp_env_amt;

  target_float pitch_env_amt;
  target_float tune;

  target_float pd_mod_amt;
  target_float ws_mod_amt;

  //parameters from other devices
  float freq;
  bool gate = false;

  ADSR amp_env;
  ADSR pd_env;
  ADSR shp_env;
  ADSR pitch_env;

  special_oscillator osc;

  public:
    oscil_line();

    float value();
    void update(float mod_in =0.0f);
    bool done();

    void set_samplerate(float sr);
    
    void set_wave(waveform wf);
    void set_phaseshaper(phase_shaper shp);
    void set_window(window wnd);
    void set_waveshaper(waveshaper shp);

    void set_tune(float v);
    void set_ptch_env_amt(float v);

    void set_pd(float v);
    void set_pd_env_amt(float v);
    void set_pd_mod_amt(float v);
    
    void set_shp(float v);
    void set_shp_env_amt(float v);
    void set_shp_mod_amt(float v);

    void amp_a(float v);
    void amp_d(float v);
    void amp_s(float v);
    void amp_r(float v);

    void pd_a(float v);
    void pd_d(float v);
    void pd_s(float v);
    void pd_r(float v);

    void shp_a(float v);
    void shp_d(float v);
    void shp_s(float v);
    void shp_r(float v);

    void ptch_a(float v);
    void ptch_d(float v);
    void ptch_s(float v);
    void ptch_r(float v);

    void set_freq(float f);
    void set_gate(bool g);
};


#endif
