#include "wave_drawer.h"
#include "colors.h"

using namespace juce;

gui::wave_drawer::wave_drawer(vts& st,str p1,str p2, str p3, str p4, str p5, str p6):
wave(static_cast<cparam*>(st.getParameter(p1))),
ps(static_cast<cparam*>(st.getParameter(p2))),
ws(static_cast<cparam*>(st.getParameter(p3))),
wnd(static_cast<cparam*>(st.getParameter(p4))),
pd_amt(static_cast<fparam*>(st.getParameter(p5))),
ws_amt(static_cast<fparam*>(st.getParameter(p6)))
{
  wave->addListener(this);
  ps->addListener(this);
  ws->addListener(this);
  pd_amt->addListener(this);
  ws_amt->addListener(this);
  wnd->addListener(this);

  do_parameters();
}

gui::wave_drawer::~wave_drawer()
{
  wave->removeListener(this);
  ps->removeListener(this);
  ws->removeListener(this);
  pd_amt->removeListener(this);
  ws_amt->removeListener(this);
  wnd->removeListener(this);
}

void gui::wave_drawer::do_parameters()
{
  draw_osc.wf = static_cast<waveform>(wave->getIndex());
  draw_osc.ps = static_cast<phase_shaper>(ps->getIndex());
  draw_osc.shp = static_cast<waveshaper>(ws->getIndex());
  draw_osc.wnd = static_cast<window>(wnd->getIndex());
  draw_osc.pd_amt = pd_amt->get();
  draw_osc.shp_amt = ws_amt->get(); 
}

void gui::wave_drawer::parameterValueChanged(int ,float)
{
  do_parameters();
  repaint();
}

void gui::wave_drawer::parameterGestureChanged(int,bool)
{
  //don't do shit
}


void gui::wave_drawer::paint(gfx& g)
{
  g.setColour(cga::black);
  g.fillAll();

  const rect db = {
    2,
    1,
    getWidth()-4,
    getHeight() - 2
  };

  //mid line
  g.setColour(cga::grey);
  g.drawRect(db.getX(),db.getCentreY(),db.getWidth(),1);

  //the wave itself
  g.setColour(cga::hi_cyan);

  auto get_point = [&db,this](int i) -> std::pair<int,int>
  {
    float phase = static_cast<float>(i)/static_cast<float>(db.getWidth());
    float wave_v = draw_osc.value(phase);
    float height = wave_v * static_cast<float>(db.getCentreY()-db.getY());
    int offset = -static_cast<int>(height);
    return {db.getX()+i, db.getCentreY() + offset };
  };

  auto [first_x,last_y] = get_point(0);
  g.drawRect(first_x,last_y,1,1);

  for(int i=1;i<db.getWidth();++i)
  {
    auto [x,y] = get_point(i);
    int top = std::min(y,last_y);
    int dist = std::max(y,last_y) - top;

    g.drawRect(x,top,1,std::max(dist,1));
    last_y = y;
  }
}
