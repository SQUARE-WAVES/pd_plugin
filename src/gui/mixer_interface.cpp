#include "mixer_interface.h"

using namespace juce;

gui::mixer_interface::mixer_interface(AudioProcessorValueTreeState& st, str name):
bg(name),
osc_1_vol(st,"osc1_vol"),
osc_2_vol(st,"osc2_vol"),
xmod_vol(st,"cross_mod_vol")
{
  addAndMakeVisible(&bg);
  addAndMakeVisible(&osc_1_vol);
  addAndMakeVisible(&osc_2_vol);
  addAndMakeVisible(&xmod_vol);
}

static inline Rectangle<int> gridbox(int y)
{
  return {2,14 + (25*y),246,25};
}

void gui::mixer_interface::mixer_interface::resized()
{
  bg.setBounds(0,0,250,275);

  osc_1_vol.setBounds(gridbox(2));
  osc_2_vol.setBounds(gridbox(4));
  xmod_vol.setBounds(gridbox(6));
}

void gui::mixer_interface::background::paint(gfx &g)
{
  g.setColour(cga::black);
  g.fillAll();

  auto fnt = g.getCurrentFont();
  int tw = fnt.getStringWidth(panel_name);
  int fh = static_cast<int>(fnt.getHeight());
  rect text_box = {(getWidth()-tw)/2 - 1,0,tw+2,fh+2};
  int text_center_line = (fh+2)/2;

  g.setColour(cga::white);
  g.drawRect(0,text_center_line,250,getHeight()-text_center_line);

  g.setColour(cga::hi_cyan);
  g.fillRect(gridbox(0));
  g.setColour(cga::black);
  g.drawText("OUT",gridbox(0),jst::centred);

  g.setColour(cga::grey);
  g.drawText("osc1 volume",gridbox(1),jst::centred);
  g.drawText("osc2 volume",gridbox(3),jst::centred);
  g.drawText("xmod volume",gridbox(5),jst::centred);

  g.setColour(cga::black);
  g.fillRect(text_box);

  g.setColour(cga::white);
  g.drawText(panel_name,text_box,jst::centred,false);
}
