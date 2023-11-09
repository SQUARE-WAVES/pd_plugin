#include "pd_syn.h"

float pd_syn::value()
{
  float sum = 0.0f;

  for(auto& v : voices)
  {
    if(!v.done())
    {
      sum += v.value();
    }
  }

  return sum; 
}

void pd_syn::update()
{
  pitch_lfo.update();
  mod_lfo.update();

  bend_freq.update();
  mod_wheel.update();

  float pw = pitch_lfo.value();
  float mw = mod_wheel.value();
  float modifier = -mod_wheel_on;

  float total_pw = pw * (mw - (mw * modifier));
  
  for(auto& v : voices)
  {
    if(!v.done())
    {
      v.update(total_pw,bend_freq.value());
    }
  }
}

void pd_syn::set_samplerate(float sr)
{
    
  for(auto& v : voices)
  {
    v.set_samplerate(sr);
  }

  pitch_lfo.set_samplerate(sr);
}

void pd_syn::note_on(int nn)
{
  voicer.note_on(nn);
}

void pd_syn::note_off(int nn)
{
  voicer.note_off(nn);
}

void pd_syn::portamento_time(float nt)
{
  voicer.set_portamento(nt);
}

void pd_syn::set_pitch_bend(int bend_amt)
{
  const static float BEND_MAX = 16383.0f;
  float bend_xp = (2.0f * (static_cast<float>(bend_amt)/BEND_MAX)) - 1.0f;
  bend_freq.set_target(bend_range * bend_xp);
}

void pd_syn::set_bend_range(float range)
{
  bend_range = range;
}


void pd_syn::set_mod_wheel(float mw)
{
  mod_wheel.set_target(mw/127.0f);
}

void pd_syn::mw_on(float on_off)
{
  mod_wheel_on = on_off;
}
