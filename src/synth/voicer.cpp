#include "voicer.h"

mono_voicer::mono_voicer():
note_freq(69.0f,0.0f,127.0f),
bend_freq(0.0f,-12.0f,12.0f)
{
  for(bool& b : notes)
  {
    b = false;
  }
}

//returns true if things changed
bool mono_voicer::set_note(int nn)
{
  bool& n = notes.at(static_cast<size_t>(nn));
  bool v = n;
  n = true;
  return !v;
}

bool mono_voicer::clear_note(int nn)
{
  bool& n = notes.at(static_cast<size_t>(nn));
  bool v = n;
  n = false;
  return v;
}

int mono_voicer::low_note()
{
  for(size_t i=0;i<notes.size();++i)
  {
    if(notes.at(i) == true)
    {
      return static_cast<int>(i);
    }
  }

  return -1;
}

bool mono_voicer::note_on(int nn)
{
  if(set_note(nn))
  {
    bool legato = current_note != -1;
    current_note = nn;
    set_note_freq(legato);
  }

  return gate();
}

bool mono_voicer::note_off(int nn)
{
  clear_note(nn);

  if(nn == current_note)
  {
    current_note = low_note();

    if(current_note != -1)
    {
      set_note_freq(false);
    }
  }

  return gate();
}

bool mono_voicer::gate()
{
  return current_note != -1;
}


float mono_voicer::freq(float input)
{
  return 440.0f * std::exp2f( (note_freq.value() + bend_freq.value() + input - 69.0f)/12.0f );
}

void mono_voicer::update()
{
  note_freq.update();
  bend_freq.update();
}

void mono_voicer::set_portamento(float nt)
{
  port_time = nt;
}

void mono_voicer::set_pitch_bend(int bend_amt)
{
  const static float BEND_MAX = 16383.0f;
  float bend_xp = (2.0f * (static_cast<float>(bend_amt)/BEND_MAX)) - 1.0f;
  bend_freq.set_target(bend_range * bend_xp);
}

void mono_voicer::set_bend_range(float range)
{
  bend_range = range;
}
