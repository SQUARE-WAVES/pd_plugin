#include "voicer_interface.h"

using namespace juce;

gui::voicer_interface::voicer_interface(AudioProcessorValueTreeState& st, str name):
bg(name),
porta(st,"portamento"),
porta_pres(st,"portamento",{0.0f,0.1f,1.0f})
{
  addAndMakeVisible(&bg);
  addAndMakeVisible(&porta);
  addAndMakeVisible(&porta_pres);
}

static inline Rectangle<int> gridbox(int y)
{
  return {2,14 + (25*y),246,25};
}

void gui::voicer_interface::resized()
{
  bg.setBounds(0,0,250,275);

  porta.setBounds(gridbox(2));
  porta_pres.setBounds(gridbox(3));
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

  g.setColour(cga::white);
  g.drawRect(0,text_center_line,250,getHeight()-text_center_line);

  g.setColour(cga::hi_cyan);
  g.fillRect(gridbox(0));
  g.setColour(cga::black);
  g.drawText("FREQUENCY",gridbox(0),jst::centred);

  g.setColour(cga::grey);
  g.drawText("PORTAMENTO",gridbox(1),jst::centred);

  g.setColour(cga::black);
  g.fillRect(text_box);

  g.setColour(cga::white);
  g.drawText(panel_name,text_box,jst::centred,false);
}
