#include "KDRadioBox.hpp"

KDRadioBox::KDRadioBox(int fx,int fy,int x_meret,std::vector<std::string> menu_pontok)
    : Widgets(fx,fy,x_meret,0)
{
    ertek = 0;

    meret_y = menu_pontok.size()*22+3;

    for(int i = 0; i< menu_pontok.size(); i++)
    {
        radiobutton.push_back(new KDRadioSwitch(x+4,y+i*22+4,16,false));
        radiotext.push_back(new KDStaticText(x+25,y+i*22+2,18,x_meret,20,menu_pontok[i]));
    }

    hatter.open(meret_x,meret_y);
    hatter << genv::move_to(0,0) << genv::color(95,100,60) << genv::box(meret_x,meret_y);

    ujra_rajzol();
}
void KDRadioBox::rajzol()
{
    genv::gout << genv::stamp(kep,x,y);

    for(int i = 0; i<radiobutton.size(); i++)
    {
        if(i==ertek)radiobutton[i]->set_pipa(true);
        radiobutton[i]->rajzol();
    }
    for(KDStaticText * temp:radiotext) temp->rajzol();
}
void KDRadioBox::ujra_rajzol()
{
    kep.open(meret_x,meret_y);
    kep.transparent(true);

    kep << genv::stamp(hatter,0,0);
    kep << foreground_col << genv::move_to(0,0) << genv::line(0,meret_y);
    kep << genv::move_to(0,0) << genv::line(meret_x,0);
    kep << genv::move_to(meret_x-1,meret_y-1) << genv::line(0,-meret_y);
    kep << genv::move_to(meret_x-1,meret_y-1) << genv::line(-meret_x,0);
}
void KDRadioBox::kezel(genv::event ev)
{
    if(Widgets::get_egeralatt(ev))
    {
        focusban = true;
    }
    if(focusban)
    {
        if(ev.button == genv::btn_left)
        {
            for(int i = 0; i<radiobutton.size(); i++) radiobutton[i]->set_pipa(false);
        }

        for(int i = 0; i<radiobutton.size(); i++)
        {
            radiobutton[i]->kezel(ev);
            if(radiobutton[i]->get_pipa()) ertek = i;

            radiobutton[i]->set_pipa(false);
        }
        if(ev.keycode == genv::key_up)
        {
            ertek = (ertek > 0)?ertek-1:radiobutton.size()-1;
        }
        if(ev.keycode == genv::key_down || ev.keycode == 32) ertek = (++ertek)%radiobutton.size();
        ujra_rajzol();
    }
}
