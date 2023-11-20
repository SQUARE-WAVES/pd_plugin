#pragma once

#include "oscil_line.h"
#include "target_param.h"

struct pd_voice
{
  oscil_line osc1;
  oscil_line osc2;
  
  target_float o1_vol;
  target_float o2_vol;
  target_float xmod_vol;

  waveshaper out_shaper = waveshaper::off;
  target_float out_shaper_amt;
  target_float voice_volume = target_float(0.8f,0.0f,1.0f);

  target_float note_freq = target_float(69.0f,0.0f,127.0f);
  target_float o1_lfo_amt = target_float(0.0f,0.0f,24.0f);
  target_float o2_lfo_amt = target_float(0.0f,0.0f,24.0f);
  
  float samplerate = 48000.0f;
  bool gate = false;

  float value();
  void update(float lfo_value = 0.0f, float bend_val = 0.0f, float mod_val = 0.0f);
  bool done();

  void set_samplerate(float sr);

  void set_freq(float nf);
  void set_freq_portamento(float nf, float nt);
  void gate_on();
  void gate_off();
};
