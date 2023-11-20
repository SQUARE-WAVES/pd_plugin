#include "pd_voice.h"
#include "specialosc.h"
#include "waveshapers.h"
#include "curves.h"

static const float calc_shaper(const float amt, const waveshaper ws, const float val)
{
  switch(ws)
  {
    case waveshaper::off:
      return val;
    break;

    case waveshaper::tri:
      return waveshapers::tri(val, amt);
    break;

    case waveshaper::sin:
      return waveshapers::sin(val,amt);
    break;

    case waveshaper::sig:
      return waveshapers::sigm(val,amt);
    break;
  }
}

float pd_voice::value()
{
  float o1 = osc1.value();
  float o2 = osc2.value();
  
  float o1v = o1_vol.value();
  float o2v = o2_vol.value();

  float xmod = o1 * o2;
  float xmod_v = xmod_vol.value();

  float v = (o1 * o1v) + (o2 * o2v) + (xmod * xmod_v);
  float shp_amt = out_shaper_amt.value();

  return calc_shaper(shp_amt,out_shaper,v) * curves::exp(voice_volume.value()) * 0.5f;
}

void pd_voice::update(float lfo, float bend,float mod)
{
  note_freq.update();
  o1_lfo_amt.update();
  o2_lfo_amt.update();

  osc1.set_freq(note_freq.value() + (o1_lfo_amt.value() * lfo) + bend);
  osc2.set_freq(note_freq.value() + (o2_lfo_amt.value() * lfo) + bend);

  osc1.update(mod);
  osc2.update(mod);

  o1_vol.update();
  o2_vol.update();
  xmod_vol.update();

  out_shaper_amt.update();
  voice_volume.update();
}

bool pd_voice::done()
{
  return osc1.done() && osc2.done();
}

void pd_voice::set_samplerate(float sr)
{
  osc1.set_samplerate(sr);
  osc2.set_samplerate(sr);
  samplerate = sr;
}

void pd_voice::set_freq(float nf) 
{
  note_freq.set_value(nf);
}

void pd_voice::set_freq_portamento(float nf,float nt) 
{
  note_freq.set_timed(nf,nt,samplerate);
}

void pd_voice::gate_on()
{
  gate = true;
  osc1.set_gate(true);
  osc2.set_gate(true);
}

void pd_voice::gate_off()
{
  gate = false;
  osc1.set_gate(false);
  osc2.set_gate(false);
}

