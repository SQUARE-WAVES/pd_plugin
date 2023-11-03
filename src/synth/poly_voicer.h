#pragma once
#include <array>
#include <span>
#include <algorithm>
#include <utility>

template <class T,size_t sz> class poly_voicer 
{
  struct voice
  {
    T* syn;
    int nn = -1;
  };

  std::array<voice,sz> v;
  int count = 0;
  int max = sz;

  float port_time = 0.2f;

  //make this an array to do multiples of the same voice
  std::array<T*,128> key_map;

  auto vox_end()
  {
    return v.begin() + count;
  }

  bool full()
  {
    return count >= max;
  }

  voice* check_key(int nn)
  {
    T* syn = key_map.at(static_cast<size_t>(nn));
    
    if(syn == nullptr)
    {
      return nullptr;
    }

    return &(*std::find_if(v.begin(),v.end(),[syn](voice& vx) {return vx.syn == syn;}));
  }

  void assign_voice(voice& vox,int nn)
  {
    bool legato = vox.nn != -1;
    vox.nn = nn;
    key_map.at(static_cast<size_t>(nn)) = vox.syn;
    
    if(legato)
    {
      vox.syn->set_freq_portamento(nn,port_time);
    }
    else 
    {
      vox.syn->set_freq(nn);
      vox.syn->gate_on();
    }
  }

  //returns FALSE if the voice needs to keep going
  //or TRUE if the voice is done
  bool end_voice(voice& vox,int nn)
  {
    key_map.at(static_cast<size_t>(nn)) = nullptr;

    if(vox.nn != nn)
    {
      //this voice is playing something else
      //so it's fine we can just quit
      return false;
    }

    //maybe make an index or something later?
    //seems like a pain this might be fine
    for(size_t i=0;i<key_map.size();++i)
    {
      if(key_map.at(i) == vox.syn)
      {
        vox.syn->set_freq(static_cast<float>(i));
        vox.nn = static_cast<int>(i);
        return false;
      }
    }

    vox.syn->gate_off();
    vox.nn = -1;
    return true;
  }

  void remove_voice(voice* vox)
  {
    auto spot = std::find_if(v.begin(),vox_end(),[vox](voice& v2) { return vox==&v2;});
    
    if(spot != vox_end())
    {
      std::rotate(spot,spot+1,vox_end());
      --count;
    }
  }

  public:
  poly_voicer(std::array<T,sz>& voice_pool)
  {
    auto pool = voice_pool.begin();
    for(auto& voice : v)
    {
      voice.syn = &(*pool++);
    }

    for(auto& vp : key_map)
    {
      vp = nullptr;
    }
  }

  void note_on(int nn)
  {
    if(check_key(nn) != nullptr)
    {
      //we are already playing this one skip it;
      return;
    }

    if(full())
    {
      //gotta steal!
      assign_voice(*v.begin(), nn);
      std::rotate(v.begin(),v.begin()+1,v.begin()+max);
      return;
    }

    assign_voice(*vox_end(),nn);
    ++count;
  }

  void note_off(int nn)
  {
    //ok are we playing this note?
    voice* vox = check_key(nn);
    
    if(vox == nullptr) 
    {
      //nothing to do here
      return;
    }

    if(end_voice(*vox,nn))
    {
      remove_voice(vox);
    }
  }

  void set_portamento(float nt)
  {
    port_time = nt;
  }

  void set_max(int new_max)
  {
    if(new_max < 1)
    {
      max = 1;
    }
    else if(new_max > static_cast<int>(sz))
    {
      max = static_cast<int>(sz);
    }
    else
    {
      max = new_max;
    }
  }
};

