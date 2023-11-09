#include "midline_interface.h"
#include "grid.h"

using namespace juce;

gui::midline_interface::midline_interface(juce::AudioProcessor& proc,vts& st, str panel_name):
bg(panel_name),
porta(st,"portamento"),
porta_pres(st,"portamento",{0.0f,0.1f,1.0f}),
voice_count(st,"voices"),
bend_range(st,"bend_range"),
p_lfo_rate(st,"lfo_rate"),
p_lfo_wave(st,"lfo_wave"),
p_lfo_sync(proc,st,"lfo_rate"),
o1_lfo_amt(st,"o1_lfo_amt"),
o2_lfo_amt(st,"o2_lfo_amt"),
o1_out(st,"osc1_vol"),
o2_out(st,"osc2_vol"),
xmod_out(st,"cross_mod_vol"),
top_pch(st,"1->2",
  "osc1_pitch_env_attack","osc2_pitch_env_attack",
  "osc1_pitch_env_decay","osc2_pitch_env_decay",
  "osc1_pitch_env_sustain","osc2_pitch_env_sustain",
  "osc1_pitch_env_release","osc2_pitch_env_release"
),
btm_pch(st,"2->1",
  "osc2_pitch_env_attack","osc1_pitch_env_attack",
  "osc2_pitch_env_decay","osc1_pitch_env_decay",
  "osc2_pitch_env_sustain","osc1_pitch_env_sustain",
  "osc2_pitch_env_release","osc1_pitch_env_release"
),
top_pd(st,"1->2",
  "osc1_pd_env_attack","osc2_pd_env_attack",
  "osc1_pd_env_decay","osc2_pd_env_decay",
  "osc1_pd_env_sustain","osc2_pd_env_sustain",
  "osc1_pd_env_release","osc2_pd_env_release"
),
btm_pd(st,"2->1",
  "osc2_pd_env_attack","osc1_pd_env_attack",
  "osc2_pd_env_decay","osc1_pd_env_decay",
  "osc2_pd_env_sustain","osc1_pd_env_sustain",
  "osc2_pd_env_release","osc1_pd_env_release"
),  
top_ws(st,"1->2",
  "osc1_shp_env_attack","osc2_shp_env_attack",
  "osc1_shp_env_decay","osc2_shp_env_decay",
  "osc1_shp_env_sustain","osc2_shp_env_sustain",
  "osc1_shp_env_release","osc2_shp_env_release"
),
btm_ws(st,"2->1",
  "osc2_shp_env_attack","osc1_shp_env_attack",
  "osc2_shp_env_decay","osc1_shp_env_decay",
  "osc2_shp_env_sustain","osc1_shp_env_sustain",
  "osc2_shp_env_release","osc1_shp_env_release"
),  
top_amp(st,"1->2",
  "osc1_amp_env_attack","osc2_amp_env_attack",
  "osc1_amp_env_decay","osc2_amp_env_decay",
  "osc1_amp_env_sustain","osc2_amp_env_sustain",
  "osc1_amp_env_release","osc2_amp_env_release"
),
btm_amp(st,"2->1",
  "osc2_amp_env_attack","osc1_amp_env_attack",
  "osc2_amp_env_decay","osc1_amp_env_decay",
  "osc2_amp_env_sustain","osc1_amp_env_sustain",
  "osc2_amp_env_release","osc1_amp_env_release"
),
mod_wheel(st,"mod_wheel")
{
  addAndMakeVisible(&bg);
  addAndMakeVisible(&porta);
  addAndMakeVisible(&porta_pres);
  addAndMakeVisible(&voice_count);
  addAndMakeVisible(&bend_range);
  addAndMakeVisible(&p_lfo_rate);
  addAndMakeVisible(&p_lfo_wave);
  addAndMakeVisible(&p_lfo_sync);
  addAndMakeVisible(&o1_lfo_amt);
  addAndMakeVisible(&o2_lfo_amt);
  addAndMakeVisible(&o1_out);
  addAndMakeVisible(&o2_out);
  addAndMakeVisible(&xmod_out);
  addAndMakeVisible(&top_pch);
  addAndMakeVisible(&btm_pch);
  addAndMakeVisible(&top_pd);
  addAndMakeVisible(&btm_pd);
  addAndMakeVisible(&top_ws);
  addAndMakeVisible(&btm_ws);
  addAndMakeVisible(&btm_pd);
  addAndMakeVisible(&top_amp);
  addAndMakeVisible(&btm_amp);
  addAndMakeVisible(&mod_wheel);
}

void gui::midline_interface::resized()
{
  bg.setBounds(0,0,1500,275);
  rect text_box = bg.text_box();
  grid grd = {{0,text_box.getBottom(),1500,275-text_box.getBottom()},10,6};
  int txt_slice = grd.col_w() - 60;
  
  //voicer
  porta.setBounds(grd.cell(0,2,2,1));
  porta_pres.setBounds(grd.cell(0,3,2,1));
  bend_range.setBounds(grd.cell(0,5,2,1));
  voice_count.setBounds(grd.cell(0,7,2,1));

  //lfo
  p_lfo_rate.setBounds(grd.cell(1,2,2,1));
  p_lfo_sync.setBounds(grd.cell(1,3,2,1));
  //this is where the sync bits will go
  p_lfo_wave.setBounds(grd.cell(1,5,2,1));
  o1_lfo_amt.setBounds(grd.cell(1,6,2,1).removeFromRight(txt_slice));
  o2_lfo_amt.setBounds(grd.cell(1,7,2,1).removeFromRight(txt_slice));
  mod_wheel.setBounds(grd.cell(1,8,2,1).removeFromRight(txt_slice));
  
  //env sync
  int half_slice = grd.col_w()/2;
  top_pch.setBounds(grd.cell(2,2,2,1).removeFromLeft(half_slice));
  btm_pch.setBounds(grd.cell(2,2,2,1).removeFromRight(half_slice));

  top_pd.setBounds(grd.cell(2,4,2,1).removeFromLeft(half_slice));
  btm_pd.setBounds(grd.cell(2,4,2,1).removeFromRight(half_slice));

  top_ws.setBounds(grd.cell(2,6,2,1).removeFromLeft(half_slice));
  btm_ws.setBounds(grd.cell(2,6,2,1).removeFromRight(half_slice));
  
  top_amp.setBounds(grd.cell(2,8,2,1).removeFromLeft(half_slice));
  btm_amp.setBounds(grd.cell(2,8,2,1).removeFromRight(half_slice));

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

    g.drawText("polyphony count",grd.cell(0,6),jst::centred);
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
    g.drawText("o1",grd.cell(1,6).removeFromLeft(60),jst::centred);
    g.drawText("o2",grd.cell(1,7).removeFromLeft(60),jst::centred);
    g.drawText("mod",grd.cell(1,8).removeFromLeft(60),jst::centred);
  }

  //env sync
  {
    auto panel_bounds = grd.cell_rect(2,0,1,10);
    g.setColour(cga::white);
    g.drawRect(panel_bounds.getX(),text_center_line,panel_bounds.getWidth(),frame.getHeight());

    g.setColour(cga::hi_cyan);
    g.fillRect(grd.cell(2,0,2,1));
    g.setColour(cga::black);
    g.drawText("ENV SYNC",grd.cell(2,0),jst::centred);
    
    g.setColour(cga::grey);
    g.drawText("pitch",grd.cell(2,1),jst::centred);
    g.drawText("pd",grd.cell(2,3),jst::centred);
    g.drawText("ws",grd.cell(2,5),jst::centred);
    g.drawText("amp",grd.cell(2,7),jst::centred);
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

//boo formatting
gui::midline_interface::env_sync_btn::env_sync_btn(
  vts& st, str name,
  str a1n,str a2n, 
  str d1n,str d2n,
  str s1n,str s2n,
  str r1n,str r2n
):
btn(name),
a1(static_cast<fparam*>(st.getParameter(a1n))),
a2(static_cast<fparam*>(st.getParameter(a2n))),
d1(static_cast<fparam*>(st.getParameter(d1n))),
d2(static_cast<fparam*>(st.getParameter(d2n))),
s1(static_cast<fparam*>(st.getParameter(s1n))),
s2(static_cast<fparam*>(st.getParameter(s2n))),
r1(static_cast<fparam*>(st.getParameter(r1n))),
r2(static_cast<fparam*>(st.getParameter(r2n)))
{
}

void gui::midline_interface::env_sync_btn::on_click()
{
  *a2 = a1->get();
  *d2 = d1->get();
  *s2 = s1->get();
  *r2 = r1->get();
}
