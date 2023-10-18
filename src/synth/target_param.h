#ifndef TARGET_PARAM_DOT_H
#define TARGET_PARAM_DOT_H
#include <algorithm>
#include <atomic>
#include <cmath>

class target_float
{
  std::atomic<float> target;
  float val;
  float increment = 0.01f;

  float min;
  float max;

  public:
    target_float(float init=0.0f, float mn =0.0f, float mx = 1.0f):
    target(init),
    val(init),
    min(mn),
    max(mx)
    {
    }

    float value() const
    {
      return val;
    }

    void update()
    {
      float dist = val - target;

      if(dist > 0.0f)
      {
        val = std::max(val-increment,target.load());
      }
      else if(dist < 0.0f)
      {
        val = std::min(val+increment,target.load());
      }
    }

    void set_target(const float targ)
    {
      target = std::clamp(targ,min,max);
    }

    void set_increment(const float i)
    {
      increment = i;
    }

    void set_value(const float new_val)
    {
      target = std::clamp(new_val,min,max);
      val = target;
    }

    //for constant time stuff
    void set_timed(const float targ, const float time, const float samplerate)
    {
      float dist = std::fabs(val - targ);
      set_target(targ);
      increment = dist/(time * samplerate);
    }
};

#endif
