#include "Widgets.hpp"

bool Widgets::get_egeralatt(genv::event ev)
{
    if(ev.button == genv::btn_left && x <= ev.pos_x && ev.pos_x <= x+meret_x && y <= ev.pos_y && ev.pos_y <= y+meret_y) return true;
    else return false;
}

Widgets::Widgets(int fx,int fy,int merx,int mery) : os_x(fx), os_y(fy),x(fx), y(fy), meret_x(merx), meret_y(mery)
{
    focusban = false;
}
