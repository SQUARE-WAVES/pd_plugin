#include "midline_interface.h"
#include "grid.h"

using namespace juce;

gui::midline_interface::midline_interface(AudioProcessorValueTreeState& st, str panel_name):
bg(panel_name),
porta(st,"portamento"),
porta_pres(st,"portamento",{0.0f,0.1f,1.0f}),
bend_range(st,"bend_range"),
p_lfo_rate(st,"lfo_rate"),
p_lfo_wave(st,"lfo_wave"),
o1_lfo_amt(st,"o1_lfo_amt"),
o2_lfo_amt(st,"o2_lfo_amt"),
o1_out(st,"osc1_vol"),
o2_out(st,"osc2_vol"),
xmod_out(st,"cross_mod_vol")
{
  addAndMakeVisible(&bg);
  addAndMakeVisible(&porta);
  addAndMakeVisible(&porta_pres);
  addAndMakeVisible(&bend_range);
  addAndMakeVisible(&p_lfo_rate);
  addAndMakeVisible(&p_lfo_wave);
  addAndMakeVisible(&o1_lfo_amt);
  addAndMakeVisible(&o2_lfo_amt);
  addAndMakeVisible(&o1_out);
  addAndMakeVisible(&o2_out);
  addAndMakeVisible(&xmod_out);
}

void gui::midline_interface::resized()
{
  bg.setBounds(0,0,1500,275);
  rect text_box = bg.text_box();
  grid grd = {{0,text_box.getBottom(),1500,275-text_box.getBottom()},10,6};
  //int txt_slice = grd.col_w() - 60;
  
  //voicer
  porta.setBounds(grd.cell(0,2,2,1));
  porta_pres.setBounds(grd.cell(0,3,2,1));
  bend_range.setBounds(grd.cell(0,5,2,1));

  //lfo
  p_lfo_rate.setBounds(grd.cell(1,2,2,1));
  //this is where the sync bits will go
  p_lfo_wave.setBounds(grd.cell(1,5,2,1));
  o1_lfo_amt.setBounds(grd.cell(1,7,2,1));
  o2_lfo_amt.setBounds(grd.cell(1,9,2,1));

  //mixer
  o1_out.setBounds(grd.cell(5,2,2,1));
  o2_out.setBounds(grd.cell(5,4,2,1));
  xmod_out.setBounds(grd.cell(5,6,2,1));
}

void gui::midline_interface::background::paint(gfx &g)
{
  g.setColour(cga::black);
  g.fillAll();

  auto fnt = g.getCurrentFont();
  int tw = fnt.getStringWidth(panel_name);
  int fh = static_cast<int>(fnt.getHeight());
  rect text_box = {(getWidth()-tw)/2 - 1,0,tw+2,fh+2};
  int text_center_line = (fh+2)/2;
  rect frame = {0,text_center_line,getWidth(),getHeight()-text_center_line};
  
  grid grd = {{0,text_box.getBottom(),getWidth(),getHeight()-text_box.getBottom()},10,6};
  //int txt_slice = 60;

  //voicer panel
  {
    auto panel_bounds = grd.cell_rect(0,0,1,10);
    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(0,0,2,1));
    g.setColour(cga::black);
    g.drawText("VOICER",grd.cell(0,0),jst::centred);

    g.setColour(cga::grey);
    g.drawText("portamento",grd.cell(0,1),jst::centred);
    g.drawText("bend range",grd.cell(0,4),jst::centred);
  }

  //pitch_lfo
  {
    auto panel_bounds = grd.cell_rect(1,1,1,10);
    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(1,0,2,1));
    g.setColour(cga::black);
    g.drawText("PITCH LFO",grd.cell(1,0),jst::centred);

    g.setColour(cga::grey);
    g.drawText("rate",grd.cell(1,1),jst::centred);
    g.drawText("waveform",grd.cell(1,4),jst::centred);
    g.drawText("osc1 amt",grd.cell(1,6),jst::centred);
    g.drawText("osc2 amt",grd.cell(1,8),jst::centred);
  }

  //e1
  {
    auto panel_bounds = grd.cell_rect(2,0,1,10);
    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(2,0,2,1));
    g.setColour(cga::black);
    g.drawText("NOTHING YET",grd.cell(2,0),jst::centred);

  }

  //e1
  {
    auto panel_bounds = grd.cell_rect(3,0,1,10);
    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(3,0,2,1));
    g.setColour(cga::black);
    g.drawText("NOTHING YET",grd.cell(3,0),jst::centred);

  } 

  //e1
  {
    auto panel_bounds = grd.cell_rect(4,0,1,10);
    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(4,0,2,1));
    g.setColour(cga::black);
    g.drawText("NOTHING YET",grd.cell(4,0),jst::centred);
  }

  //out mixer
  {
    auto panel_bounds = grd.cell_rect(5,1,1,10);
    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(5,0,2,1));
    g.setColour(cga::black);
    g.drawText("OUT MIX",grd.cell(5,0),jst::centred);

    g.setColour(cga::grey);
    g.drawText("oscil 1",grd.cell(5,1),jst::centred);
    g.drawText("oscil 2",grd.cell(5,3),jst::centred);
    g.drawText("X-mod",grd.cell(5,5),jst::centred);
  }

  g.setColour(cga::black);
  g.fillRect(text_box);

  g.setColour(cga::white);
  g.drawText(panel_name,text_box,jst::centred,false);

}

Rectangle<int> gui::midline_interface::background::text_box()
{
  Font fnt; //default constructor should get you the right things
  int tw = fnt.getStringWidth(panel_name);
  int fh = static_cast<int>(fnt.getHeight());
  return {(getWidth()-tw)/2 - 1,0,tw+2,fh+2};
}
