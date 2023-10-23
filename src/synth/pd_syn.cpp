#include "pd_syn.h"

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
