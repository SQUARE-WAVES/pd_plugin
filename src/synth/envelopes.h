#ifndef ENVELOPES_DOT_H
#define ENVELOPES_DOT_H

class ADSR
{
  static const int ATTACK = 1;
  static const int DECAY = 2;
  static const int SUSTAIN = 3;
  static const int RELEASE = 4;

  //all times are in seconds
  float samplerate = 44100.0f;
  float attack;
  float a_rate;

  float decay;
  float d_rate;

  float sustain;
  
  float release;
  float r_rate;

  int stage = 0;
  float val =0.0f;

  bool gate = false;

  void calc_a();
  void calc_d();
  void calc_r();

  void a_stg();
  void d_stg();
  void r_stg();

  public:
    ADSR(float a = 0.1f, float d=0.1f, float s=0.0f, float r=0.1f):
    attack(a),
    decay(d),
    sustain(s),
    release(r)
    {
      calc_a();
      calc_d();
      calc_r();
    }

    void update();
    float value() const ;
    void set_samplerate(float sr);

    void set_a(const float a);
    void set_d(const float d);
    void set_s(const float s);
    void set_r(const float r);

    void set_gate(bool gv);
};


#endif
