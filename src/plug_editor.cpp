#include <juce_gui_basics/juce_gui_basics.h>

#include "plug_main.h"
#include "gui/sliders.h"

using namespace juce;

static void setup_styles()
{
  auto& lnf = juce::LookAndFeel::getDefaultLookAndFeel();
  lnf.setDefaultSansSerifTypefaceName("Perfect DOS VGA 437");
}

pd_proc::editor::editor(pd_proc& pxer):
AudioProcessorEditor(pxer),
proc(pxer),
o1(proc.state,"osc1","oscil 1"),
o2(proc.state,"osc2","oscil 2"),
mix(proc.state,"mix"),
vox(proc.state,"voicer"),
draw1(
  proc.state,
  "wave-1",
  "osc1_wave",
  "osc1_phaseshaper",
  "osc1_waveshaper",
  "osc1_window",
  "osc1_pd_base",
  "osc1_waveshaper_base"
),
draw2(
  proc.state,
  "wave-2",
  "osc2_wave",
  "osc2_phaseshaper",
  "osc2_waveshaper",
  "osc2_window",
  "osc2_pd_base",
  "osc2_waveshaper_base"
)
{
  setup_styles();
  setSize(1500,900);

  addAndMakeVisible(&o1);
  addAndMakeVisible(&o2);
  addAndMakeVisible(&mix);
  addAndMakeVisible(&vox);
  addAndMakeVisible(&draw1);
  addAndMakeVisible(&draw2);
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
  vox.setBounds(0,300,250,275);
  mix.setBounds(1250,300,250,275);

  draw1.setBounds(251,300,250,275);
  draw2.setBounds(502,300,250,275);
}

