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
  bend_freq.update();
  
  for(auto& v : voices)
  {
    if(!v.done())
    {
      v.update(pitch_lfo.value(),bend_freq.value());
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

/*
float pd_syn::value()
{
  float o1 = osc1.value();
  float o2 = osc2.value();
  
  float o1v = o1_vol.value();
  float o2v = o2_vol.value();

  float xmod = o1 * o2;
  float xmod_v = xmod_vol.value();

  return (o1 * o1v) + (o2 * o2v) + (xmod * xmod_v);
}

void pd_syn::update()
{
  const float lfo_v = pitch_lfo.value();
  pitch_lfo.update();

  voicer.update();
  pitch_lfo.update();

  const float o1f = voicer.freq((lfo_v*o1_lfo_amt.value()));
  osc1.set_freq(o1f);

  const float o2f = voicer.freq((lfo_v*o2_lfo_amt.value()));
  osc2.set_freq(o2f);

  osc1.update();
  osc2.update();

  o1_vol.update();
  o2_vol.update();
  xmod_vol.update();
  o1_lfo_amt.update();
  o2_lfo_amt.update();
}

void pd_syn::set_samplerate(float sr)
{
  osc1.set_samplerate(sr);
  osc2.set_samplerate(sr);
}

void pd_syn::note_on(int nn)
{
  bool gate = voicer.note_on(nn);

  osc1.set_gate(gate);
  osc2.set_gate(gate);
}

void pd_syn::note_off(int nn)
{
  bool gate = voicer.note_off(nn);

  osc1.set_gate(gate);
  osc2.set_gate(gate);
}

void pd_syn::portamento_time(float nt)
{
  voicer.set_portamento(nt);
}
*/
