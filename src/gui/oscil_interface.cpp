#include "oscil_interface.h"
#include "colors.h"

using namespace juce;

gui::oscil_interface::oscil_interface(AudioProcessorValueTreeState& st, str pfx, str panel_name):
bg(panel_name),
wave(st,pfx + "_wave"),
tune(st,pfx + "_tune"),
tune_presets(st,pfx + "_tune",{-12.0f,-7.0f,0.0f,7.0f,12.0f}),
windows(st,pfx + "_window"),
pd_waves(st,pfx + "_phaseshaper"),
pd_base(st,pfx + "_pd_base"),
pd_env_amt(st,pfx + "_pd_env_amt"),
shaper_form(st,pfx + "_waveshaper"),
shaper_base(st,pfx + "_waveshaper_base"),
shaper_env_amt(st,pfx + "_waveshaper_env_amt"),
pd_env_a(st,pfx + "_pd_env_attack"),
pd_env_d(st,pfx + "_pd_env_decay"),
pd_env_s(st,pfx + "_pd_env_sustain"),
pd_env_r(st,pfx + "_pd_env_release"),
shp_env_a(st,pfx + "_shp_env_attack"),
shp_env_d(st,pfx + "_shp_env_decay"),
shp_env_s(st,pfx + "_shp_env_sustain"),
shp_env_r(st,pfx + "_shp_env_release"),
amp_env_a(st,pfx + "_amp_env_attack"),
amp_env_d(st,pfx + "_amp_env_decay"),
amp_env_s(st,pfx + "_amp_env_sustain"),
amp_env_r(st,pfx + "_amp_env_release")
{
  addAndMakeVisible(&bg);
  addAndMakeVisible(&wave);
  addAndMakeVisible(&tune);
  addAndMakeVisible(&tune_presets);
  addAndMakeVisible(&windows);
  addAndMakeVisible(&pd_waves);
  addAndMakeVisible(&pd_base);
  addAndMakeVisible(&pd_env_amt);
  addAndMakeVisible(&shaper_form);
  addAndMakeVisible(&shaper_base);
  addAndMakeVisible(&shaper_env_amt);
  addAndMakeVisible(&pd_env_a);
  addAndMakeVisible(&pd_env_d);
  addAndMakeVisible(&pd_env_s);
  addAndMakeVisible(&pd_env_r);
  addAndMakeVisible(&shp_env_a);
  addAndMakeVisible(&shp_env_d);
  addAndMakeVisible(&shp_env_s);
  addAndMakeVisible(&shp_env_r);
  addAndMakeVisible(&amp_env_a);
  addAndMakeVisible(&amp_env_d);
  addAndMakeVisible(&amp_env_s);
  addAndMakeVisible(&amp_env_r);
}

static inline Rectangle<int> gridbox(int x, int y)
{
  return {2+(250*x),14 + (25 * y), 246,25};
}

void gui::oscil_interface::resized()
{
  bg.setBounds(0,0,1500,275);

  //panel 1 
  wave.setBounds(gridbox(0,2));
  tune.setBounds(gridbox(0,4));
  tune_presets.setBounds(gridbox(0,5));
  windows.setBounds(gridbox(0,7));

  //panel 2
  pd_waves.setBounds(gridbox(1,2));
  pd_base.setBounds(gridbox(1,4));
  pd_env_amt.setBounds(gridbox(1,6));

  //panel 3
  shaper_form.setBounds(gridbox(2,2));
  shaper_base.setBounds(gridbox(2,4));
  shaper_env_amt.setBounds(gridbox(2,6));

  //panel4
  pd_env_a.setBounds(gridbox(3,2));
  pd_env_d.setBounds(gridbox(3,4));
  pd_env_s.setBounds(gridbox(3,6));
  pd_env_r.setBounds(gridbox(3,8));

  //panel5
  shp_env_a.setBounds(gridbox(4,2));
  shp_env_d.setBounds(gridbox(4,4));
  shp_env_s.setBounds(gridbox(4,6));
  shp_env_r.setBounds(gridbox(4,8));

  //panel 6
  amp_env_a.setBounds(gridbox(5,2));
  amp_env_d.setBounds(gridbox(5,4));
  amp_env_s.setBounds(gridbox(5,6));
  amp_env_r.setBounds(gridbox(5,8));
}

void::gui::oscil_interface::background::paint(gfx &g)
{
  g.setColour(cga::black);
  g.fillAll();

  auto fnt = g.getCurrentFont();
  int tw = fnt.getStringWidth(panel_name);
  int fh = static_cast<int>(fnt.getHeight());
  rect text_box = {(getWidth()-tw)/2 - 1,0,tw+2,fh+2};
  int text_center_line = (fh+2)/2;
 
  //====Wave and Tune====
  g.setColour(cga::white);
  g.drawRect(0,text_center_line,250,getHeight()-text_center_line);

  g.setColour(cga::hi_cyan);
  g.fillRect(gridbox(0, 0));
  g.setColour(cga::black);
  g.drawText("BASE",gridbox(0,0),jst::centred);

  g.setColour(cga::grey);
  g.drawText("waveform",gridbox(0,1),jst::centred);
  g.drawText("tune",gridbox(0,3),jst::centred);
  g.drawText("window",gridbox(0,6),jst::centred);

  //====Phase Distortion====
  g.setColour(cga::white);
  g.drawRect(250,text_center_line,250,getHeight()-text_center_line);

  g.setColour(cga::hi_cyan);
  g.fillRect(gridbox(1, 0));
  g.setColour(cga::black);
  g.drawText("PHASE DISTORTION",gridbox(1,0),jst::centred);

  g.setColour(cga::grey);
  g.drawText("shaper",gridbox(1,1),jst::centred);
  g.drawText("base_phase_distortion",gridbox(1,3),jst::centred);
  g.drawText("envelope amt",gridbox(1,5),jst::centred);

  //====Waveshaper====
  g.setColour(cga::white);
  g.drawRect(500,text_center_line,250,getHeight()-text_center_line);

  g.setColour(cga::hi_cyan);
  g.fillRect(gridbox(2, 0));
  g.setColour(cga::black);
  g.drawText("WAVE SHAPER",gridbox(2,0),jst::centred);

  g.setColour(cga::grey);
  g.drawText("wave_shaper",gridbox(2,1),jst::centred);
  g.drawText("base_distortion",gridbox(2,3),jst::centred);
  g.drawText("envelope amt",gridbox(2,5),jst::centred);

  //====PD envelope====
  g.setColour(cga::white);
  g.drawRect(750,text_center_line,250,getHeight()-text_center_line);

  g.setColour(cga::hi_cyan);
  g.fillRect(gridbox(3, 0));
  g.setColour(cga::black);
  g.drawText("PD ENVELOPE",gridbox(3,0),jst::centred);

  g.setColour(cga::grey);
  g.drawText("attack",gridbox(3,1),jst::centred);
  g.drawText("decay",gridbox(3,3),jst::centred);
  g.drawText("sustain",gridbox(3,5),jst::centred);
  g.drawText("release",gridbox(3,7),jst::centred);

  //====Waveshaper env====
  g.setColour(cga::white);
  g.drawRect(1000,text_center_line,250,getHeight()-text_center_line);

  g.setColour(cga::hi_cyan);
  g.fillRect(gridbox(4, 0));
  g.setColour(cga::black);
  g.drawText("WAVESHAPER ENVELOPE",gridbox(4,0),jst::centred);

  g.setColour(cga::grey);
  g.drawText("attack",gridbox(4,1),jst::centred);
  g.drawText("decay",gridbox(4,3),jst::centred);
  g.drawText("sustain",gridbox(4,5),jst::centred);
  g.drawText("release",gridbox(4,7),jst::centred);

  //====Amp Env
  g.setColour(cga::white);
  g.drawRect(1250,text_center_line,250,getHeight()-text_center_line);

  g.setColour(cga::hi_cyan);
  g.fillRect(gridbox(5, 0));
  g.setColour(cga::black);
  g.drawText("AMP ENVELOPE",gridbox(5,0),jst::centred);

  g.setColour(cga::grey);
  g.drawText("attack",gridbox(5,1),jst::centred);
  g.drawText("decay",gridbox(5,3),jst::centred);
  g.drawText("sustain",gridbox(5,5),jst::centred);
  g.drawText("release",gridbox(5,7),jst::centred);

  //===DONE WITH THE PANELS====
  g.setColour(cga::black);
  g.fillRect(text_box);

  g.setColour(cga::white);
  g.drawText(panel_name,text_box,jst::centred,false);
}
