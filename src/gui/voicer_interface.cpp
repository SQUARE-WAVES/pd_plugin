#include "voicer_interface.h"
#include "grid.h"

using namespace juce;

gui::voicer_interface::voicer_interface(AudioProcessorValueTreeState& st, str name):
bg(name),
porta(st,"portamento"),
porta_pres(st,"portamento",{0.0f,0.1f,1.0f}),
bend_range(st,"bend_range"),
lfo_rate(st,"lfo_rate"),
lfo_wave(st,"lfo_wave"),
o1_lfo(st,"o1_lfo_amt"),
o2_lfo(st,"o2_lfo_amt")
{
  addAndMakeVisible(&bg);
  addAndMakeVisible(&porta);
  addAndMakeVisible(&porta_pres);
  addAndMakeVisible(&lfo_rate);
  addAndMakeVisible(&lfo_wave);
  addAndMakeVisible(&o1_lfo);
  addAndMakeVisible(&o2_lfo);
  addAndMakeVisible(&bend_range);
}

void gui::voicer_interface::resized()
{
  bg.setBounds(0,0,250,275);
 
  rect text_box = bg.text_box();
  grid grd = {{0,text_box.getBottom(),250,275-text_box.getBottom()},10,1};
  int txt_slice = grd.col_w() - 60;

  porta.setBounds(grd.cell(0,2,2,1));
  porta_pres.setBounds(grd.cell(0,3,2,1));
  bend_range.setBounds(grd.cell(0,4,2,1));

  lfo_wave.setBounds(grd.cell(0,5,2,2));
  lfo_rate.setBounds(grd.cell(0,6,2,2));
  o1_lfo.setBounds(grd.cell(0,7,2,2).removeFromRight(txt_slice));
  o2_lfo.setBounds(grd.cell(0,8,2,2).removeFromRight(txt_slice));
}

void gui::voicer_interface::background::paint(gfx &g)
{
  g.setColour(cga::black);
  g.fillAll();

  auto fnt = g.getCurrentFont();
  int tw = fnt.getStringWidth(panel_name);
  int fh = static_cast<int>(fnt.getHeight());
  rect text_box = {(getWidth()-tw)/2 - 1,0,tw+2,fh+2};
  int text_center_line = (fh+2)/2;

  grid grd = {{0,text_box.getBottom(),250,275-text_box.getBottom()},10,1};
  int txt_slice = 60;

  g.setColour(cga::white);
  g.drawRect(0,text_center_line,250,getHeight()-text_center_line);

  g.setColour(cga::hi_cyan);
  g.fillRect(grd.cell(0,0,2));
  g.setColour(cga::black);
  g.drawText("NOTE",grd.cell(0,0),jst::centred);

  g.setColour(cga::grey);
  g.drawText("PORTAMENTO",grd.cell(0,1),jst::centred);

  //g.drawText("lfo",grd.cell(0,4),jst::centred);
  g.drawText("o1",grd.cell(0,7).removeFromLeft(txt_slice),jst::centred);
  g.drawText("o2",grd.cell(0,8).removeFromLeft(txt_slice),jst::centred);

  g.setColour(cga::black);
  g.fillRect(text_box);

  g.setColour(cga::white);
  g.drawText(panel_name,text_box,jst::centred,false);
}

Rectangle<int> gui::voicer_interface::background::text_box()
{
  Font fnt; //default constructor should get you the right things
  int tw = fnt.getStringWidth(panel_name);
  int fh = static_cast<int>(fnt.getHeight());
  return {(getWidth()-tw)/2 - 1,0,tw+2,fh+2};
}
