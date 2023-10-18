#include "envelopes.h"

void ADSR::calc_a()
{
  a_rate = 1.0f/(attack * samplerate);
}

void ADSR::calc_d()
{
  d_rate = 1.0f/(decay*samplerate);
}

void ADSR::calc_r()
{
  r_rate = 1.0f/(release*samplerate);
}

void ADSR::set_a(const float a)
{
  attack = a;
  calc_a();
}

void ADSR::set_d(const float d)
{
  decay = d;
  calc_d();
}

void ADSR::set_s(const float s)
{
  sustain = s;
}

void ADSR::set_r(const float r)
{
  release = r;
  calc_r();
}

void ADSR::set_samplerate(float s)
{
  samplerate = s;
  calc_a();
  calc_d();
  calc_r();
}

float ADSR::value() const
{
  return val;
}

void ADSR::update()
{
  switch(stage)
  {
    case ATTACK:
      a_stg();
    break;
    case DECAY:
      d_stg();
    break;
    case RELEASE:
      r_stg();
    break;
    default:
    break;
  }
}

void ADSR::set_gate(bool gv)
{
  //if the gate is on and you set it off
  //move to the release stage (it will go to off automatically)
  //when they are out

  if(gate && !gv)
  {
    stage = RELEASE;
  }
  else if(!gate && gv)
  {
    stage = ATTACK;
  }

  gate = gv;
  return;
}

void ADSR::a_stg()
{
  val += a_rate;

  if(val >= 1.0f)
  {
    val = 1.0f;
    stage = 2;
  }
}

void ADSR::d_stg()
{
  val -= d_rate;

  if(val <= sustain)
  {
    val = sustain;
    stage = 3;
  }
}

void ADSR::r_stg()
{
  val -= r_rate;
  if(val <= 0.0f)
  {
    val = 0.0f;
    stage = 0;
  }
}
