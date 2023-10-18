#pragma once

#include "oscil_line.h"
#include "voicer.h"
#include "target_param.h"

struct pd_syn
{
  oscil_line osc1;
  oscil_line osc2;
  
  target_float o1_vol;
  target_float o2_vol;
  target_float xmod_vol;

  mono_voicer voicer;

  float value();
  void update();

  void set_samplerate(float sr);

  void note_on(int nn);
  void note_off(int nn);

  void portamento_time(float nt);
};
