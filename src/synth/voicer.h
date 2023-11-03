#ifndef VOICER_DOT_H
#define VOICER_DOT_H

#include <MacTypes.h>
#include <cmath>
#include <array>

#include "target_param.h"

template <class voice_type> class mono_voicer
{
  std::array<bool,128> notes;
  int current_note = -1;
  float port_time = 0.2f;

  bool set_note(int nn)
  {
    bool& n = notes.at(static_cast<size_t>(nn));
    bool v = n;
    n = true;
    return !v;
  }

  bool clear_note(int nn)
  {
    bool& n = notes.at(static_cast<size_t>(nn));
    bool v = n;
    n = false;
    return v;
  }

  int low_note()
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

  public:
  mono_voicer()
  {
    for(bool& b : notes)
    {
      b = false;
    }
  }

  void set_portamento(float nt)
  {
    port_time = nt;
  }

  void note_on(int nn,voice_type& v)
  {
    if(set_note(nn))
    {
      bool legato = current_note != -1;
      current_note = nn;

      if(legato) 
      {
        v.set_freq_portamento(nn,port_time);
      }
      else
      {
        v.gate_on();
        v.set_freq(current_note);
      }
    }
  }

  void note_off(int nn,voice_type& v)
  {
    clear_note(nn);

    if(nn == current_note)
    {
      current_note = low_note();

      if(current_note != -1)
      {
        v.set_freq(current_note);
      }
      else
      {
        v.gate_off();
      }
    }
  }
};

#endif
