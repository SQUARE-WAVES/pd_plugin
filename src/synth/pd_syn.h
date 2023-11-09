#pragma once

#include <array>

#include "voicer.h"
#include "poly_voicer.h"
#include "target_param.h"
#include "lfo.h"
#include "pd_voice.h"

struct pd_syn
{
  std::array<pd_voice,8> voices;
  poly_voicer<pd_voice,8> voicer = poly_voicer<pd_voice,8>(voices);
  
  lfo pitch_lfo;
  lfo mod_lfo;
 
  float mod_wheel_on = 0.0f;
  target_float mod_wheel = target_float(0.0f,0.0f,1.0f);
  target_float bend_freq = target_float(0.0f,-12.0f,12.0f);
  
  float bend_range = 2.0f;
  float pitch_bend = 0.0f;

  float porta_time = 0.2f;

  float value();
  void update();
  void set_samplerate(float sr);

  void note_on(int nn);
  void note_off(int nn);

  void portamento_time(float nt);
  void set_pitch_bend(int bend_amount);
  void set_bend_range(float range);
  void set_mod_wheel(float mw);
  void mw_on(float on_off);
};
