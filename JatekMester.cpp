#include "JatekMester.hpp"

JatekMester::JatekMester(std::string nev)
{
    gout.set_title(nev);
    gout.open(SX,SY);
    gin.timer(16);
}
void JatekMester::run()
{
    while(gin >> ev)
    {
        widget_kezel();
        gm_main();
        gout << refresh;
    }
}
void JatekMester::widget_kezel()
{
    if(ev.button == btn_left)for(Widgets * w:widgets) w->set_focusban(false);
    for(Widgets * w:widgets) w->kezel(ev);
}
void JatekMester::widget_rajzol()
{
    for(Widgets * w:widgets) w->rajzol();
}
void JatekMester::gui(Widgets * temp)
{
    widgets.push_back(temp);
}
