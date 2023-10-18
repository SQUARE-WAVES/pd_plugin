#ifndef VOICER_DOT_H
#define VOICER_DOT_H

#include <cmath>
#include <array>

#include "target_param.h"

class mono_voicer
{
  std::array<bool,128> notes;
  int current_note = -1;

  bool set_note(int nn);
  bool clear_note(int nn);
  int low_note();

  target_float note_freq = 0.0f;
  target_float bend_freq = 0.0f;

  float bend_range = 2.0f;
  float pitch_bend = 0.0f;

  float sr = 48000.0f;
  float port_time = 0.2f;
 
  inline void set_note_freq(bool legato = false)
  {
    float note = static_cast<float>(current_note - 69)/12.0f;
    float target = std::exp2f(note);

    if(legato && port_time > 0.0f)
    {
      note_freq.set_timed(target,port_time,sr);
    }
    else 
    {
      note_freq.set_value(target);
    }
  }

  public:
   mono_voicer();

   void update();
   void set_samplerate(const float sr);
   void set_portamento(float nt);

   bool note_on(int nn);
   bool note_off(int nn);

   void set_pitch_bend(int bend_amount);

   bool gate();
   float freq();
};

#endif
