#include <juce_gui_basics/juce_gui_basics.h>

#include "plug_main.h"
#include "gui/fonts.h"

using namespace juce;

static void setup_styles()
{
  auto& lnf = juce::LookAndFeel::getDefaultLookAndFeel();
  lnf.setDefaultSansSerifTypeface(gui::tf);
}

pd_proc::editor::editor(pd_proc& pxer):
AudioProcessorEditor(pxer),
proc(pxer),
o1(proc.state,"osc1","oscil 1"),
mid(proc.state,"-=mods=-"),
o2(proc.state,"osc2","oscil 2")
{
  setup_styles();
  setSize(1500,900);

  addAndMakeVisible(&o1);
  addAndMakeVisible(&o2);
  addAndMakeVisible(&mid);
}

void pd_proc::editor::paint(gfx &g)
{
  g.setColour(Colour(0xFF000000));
  g.fillAll();
}

void pd_proc::editor::resized()
{
  o1.setBounds(0,0,1500,275);  
  o2.setBounds(0,600,1500,275);
  mid.setBounds(0,300,1500,275);
}

