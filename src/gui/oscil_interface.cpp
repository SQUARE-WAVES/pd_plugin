#include "oscil_interface.h"
#include "colors.h"
#include "fonts.h"

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
amp_env_r(st,pfx + "_amp_env_release"),
pitch_env_amt(st,pfx + "_pitch_env_amt"),
pitch_env_a(st,pfx + "_pitch_env_attack"),
pitch_env_d(st,pfx + "_pitch_env_decay"),
pitch_env_s(st,pfx + "_pitch_env_sustain"),
pitch_env_r(st,pfx + "_pitch_env_release"),
wd(st,
  pfx + "_wave",
  pfx + "_phaseshaper",
  pfx + "_waveshaper",
  pfx + "_window",
  pfx + "_pd_base",
  pfx + "_waveshaper_base"
)
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
  addAndMakeVisible(&pitch_env_amt);
  addAndMakeVisible(&pitch_env_a);
  addAndMakeVisible(&pitch_env_d);
  addAndMakeVisible(&pitch_env_s);
  addAndMakeVisible(&pitch_env_r);

  addAndMakeVisible(&wd);
}

void gui::oscil_interface::resized()
{
  bg.setBounds(0,0,1200,220);

  rect text_box = bg.text_box();
  grid grd = {{0,text_box.getBottom(),1200,220-text_box.getBottom()},10,6};
  int txt_slice = grd.col_w() - 40;

  //pitch controls
  tune.setBounds(grd.cell(0,1,2,1));
  tune_presets.setBounds(grd.cell(0,2,2,1));
  pitch_env_amt.setBounds(grd.cell(0,5,2,1).removeFromRight(txt_slice));
  pitch_env_a.setBounds(grd.cell(0,6,2,1).removeFromRight(txt_slice));
  pitch_env_d.setBounds(grd.cell(0,7,2,1).removeFromRight(txt_slice));
  pitch_env_s.setBounds(grd.cell(0,8,2,1).removeFromRight(txt_slice));
  pitch_env_r.setBounds(grd.cell(0,9,2,1).removeFromRight(txt_slice));

  //waveform controls
  wave.setBounds(grd.cell(1,1,2,1));
  windows.setBounds(grd.cell(1,3,2,1));

  //PD controls
  pd_waves.setBounds(grd.cell(2,1,2,1));
  pd_base.setBounds(grd.cell(2,2,2,1));
  
  pd_env_amt.setBounds(grd.cell(2,5,2,1).removeFromRight(txt_slice));
  pd_env_a.setBounds(grd.cell(2,6,2,1).removeFromRight(txt_slice));
  pd_env_d.setBounds(grd.cell(2,7,2,1).removeFromRight(txt_slice));
  pd_env_s.setBounds(grd.cell(2,8,2,1).removeFromRight(txt_slice));
  pd_env_r.setBounds(grd.cell(2,9,2,1).removeFromRight(txt_slice));

  //waveshaper controls
  shaper_form.setBounds(grd.cell(3,1,2,1));
  shaper_base.setBounds(grd.cell(3,2,2,1));
  
  shaper_env_amt.setBounds(grd.cell(3,5,2,1).removeFromRight(txt_slice));
  shp_env_a.setBounds(grd.cell(3,6,2,1).removeFromRight(txt_slice));
  shp_env_d.setBounds(grd.cell(3,7,2,1).removeFromRight(txt_slice));
  shp_env_s.setBounds(grd.cell(3,8,2,1).removeFromRight(txt_slice));
  shp_env_r.setBounds(grd.cell(3,9,2,1).removeFromRight(txt_slice));

  //amp env
  amp_env_a.setBounds(grd.cell(4,2,2,1));
  amp_env_d.setBounds(grd.cell(4,4,2,1));
  amp_env_s.setBounds(grd.cell(4,6,2,1));
  amp_env_r.setBounds(grd.cell(4,8,2,1));

  //picture
  wd.setBounds(grd.cell_rect(5,1,1,9,2,2));
}

void::gui::oscil_interface::background::paint(gfx &g)
{
  g.setFont(gui::fonts::small);
  g.setColour(cga::black);
  g.fillAll();

  auto fnt = g.getCurrentFont();
  int tw = fnt.getStringWidth(panel_name);
  int fh = static_cast<int>(fnt.getHeight());
  rect text_box = {(getWidth()-tw)/2 - 1,0,tw+2,fh+2};
  int text_center_line = (fh+2)/2;
  rect frame = {0,text_center_line,getWidth(),getHeight()-text_center_line};
  
  grid grd = {{0,text_box.getBottom(),getWidth(),getHeight()-text_box.getBottom()},10,6};
  int txt_slice = 40;

  //pitch panel
  {
    auto panel_bounds = grd.cell_rect(0,0,1,10);

    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(0,0,2,1));
    g.setColour(cga::black);
    g.drawText("PITCH",grd.cell(0,0),jst::centred);

    g.setColour(cga::grey);
    g.drawText("envelope",grd.cell(0,4),jst::centred);
    g.drawText("AMT",grd.cell(0,5).removeFromLeft(txt_slice),jst::centred);
    g.drawText("A",grd.cell(0,6).removeFromLeft(txt_slice),jst::centred);
    g.drawText("D",grd.cell(0,7).removeFromLeft(txt_slice),jst::centred);
    g.drawText("S",grd.cell(0,8).removeFromLeft(txt_slice),jst::centred);
    g.drawText("R",grd.cell(0,9).removeFromLeft(txt_slice),jst::centred);
  }

  //wave_panel
  {
    auto panel_bounds = grd.cell_rect(1,0,1,10);

    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(1,0,2,1));
    g.setColour(cga::black);
    g.drawText("WAVEFORM",grd.cell(1,0),jst::centred);

    g.setColour(cga::grey);
    g.drawText("window",grd.cell(1,2),jst::centred);
  }

  //phase shaper
  {
    auto panel_bounds = grd.cell_rect(2,0,1,10);

    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(2,0,2,1));
    g.setColour(cga::black);
    g.drawText("PHASE DISTORT",grd.cell(2,0),jst::centred);

    g.setColour(cga::grey);
    g.drawText("envelope",grd.cell(2,4),jst::centred);
    g.drawText("AMT",grd.cell(2,5,1).removeFromLeft(txt_slice),jst::centred);
    g.drawText("A",grd.cell(2,6,1).removeFromLeft(txt_slice),jst::centred);
    g.drawText("D",grd.cell(2,7,1).removeFromLeft(txt_slice),jst::centred);
    g.drawText("S",grd.cell(2,8,1).removeFromLeft(txt_slice),jst::centred);
    g.drawText("R",grd.cell(2,9,1).removeFromLeft(txt_slice),jst::centred);
  }

  //wave shaper
  {
    auto panel_bounds = grd.cell_rect(3,0,1,10);

    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(3,0,2,1));
    g.setColour(cga::black);
    g.drawText("WAVE SHAPER",grd.cell(3,0),jst::centred);

    g.setColour(cga::grey);
    g.drawText("envelope",grd.cell(3,3),jst::centred);
    g.drawText("AMT",grd.cell(3,5,1).removeFromLeft(txt_slice),jst::centred);
    g.drawText("A",grd.cell(3,6,1).removeFromLeft(txt_slice),jst::centred);
    g.drawText("D",grd.cell(3,7,1).removeFromLeft(txt_slice),jst::centred);
    g.drawText("S",grd.cell(3,8,1).removeFromLeft(txt_slice),jst::centred);
    g.drawText("R",grd.cell(3,9,1).removeFromLeft(txt_slice),jst::centred);
  }

  //amp env
  {
    auto panel_bounds = grd.cell_rect(4,0,1,10);

    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(4,0,2,1));
    g.setColour(cga::black);
    g.drawText("AMP ENV",grd.cell(4,0),jst::centred);

    g.setColour(cga::grey);
    g.drawText("attack",grd.cell(4,1,1),jst::centred);
    g.drawText("decay",grd.cell(4,3,1),jst::centred);
    g.drawText("sustain",grd.cell(4,5,1),jst::centred);
    g.drawText("release",grd.cell(4,7,1),jst::centred);
  }

  //drawer
  {
    auto panel_bounds = grd.cell_rect(5,0,1,10);

    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(5,0,2,1));
    g.setColour(cga::black);
    g.drawText("VIEW",grd.cell(5,0),jst::centred);
  }

  g.setColour(cga::black);
  g.fillRect(text_box);

  g.setColour(cga::white);
  g.drawText(panel_name,text_box,jst::centred,false);
}

Rectangle<int> gui::oscil_interface::background::text_box()
{
  Font fnt; //default constructor should get you the right things
  int tw = fnt.getStringWidth(panel_name);
  int fh = static_cast<int>(fnt.getHeight());
  return {(getWidth()-tw)/2 - 1,0,tw+2,fh+2};
}
