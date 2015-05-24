#include "KDStatusBar.hpp"

KDStatusBar::KDStatusBar(int fx,int fy,int meret_x,int max_ertek_,int kezdo_ertek,int tipus_) : Widgets(fx,fy,meret_x,23)
{
    max_ertek = max_ertek_;
    ertek = kezdo_ertek;

    set_fore_col(genv::color( ertek*(255.00/max_ertek) , (max_ertek-ertek)*(255.00/max_ertek) , 0 ));

    lenyomva = false;
    tipus = tipus_;

    ujra_rajzol();
}
void KDStatusBar::kezel(genv::event ev)
{
    if( get_egeralatt(ev) )
    {
        lenyomva = true;
    }
    if( lenyomva && ev.type == genv::ev_mouse )
    {
        float dif = (tipus == 1)?ev.pos_x-x:-(ev.pos_x-x-meret_x);

        if( x <= ev.pos_x && ev.pos_x <= x+meret_x ) ertek = (dif/meret_x) * max_ertek;
        else if(x > ev.pos_x) ertek = (tipus == 1)?0:max_ertek;
        else if(x+meret_x < ev.pos_x) ertek = (tipus == 1)?max_ertek:0;

        set_fore_col(genv::color( ertek*(255.00/max_ertek) , (max_ertek-ertek)*(255.00/max_ertek) , 0 ));

        ujra_rajzol();

        if(ev.button == -genv::btn_left) lenyomva = false;
    }
}
void KDStatusBar::rajzol()
{
    genv::gout << genv::stamp(kep,x,y);
}
void KDStatusBar::ujra_rajzol()
{
    kep.open(meret_x,meret_y);
    kep.transparent(true);

    kep << genv::move_to(0,0) << background_col << genv::box(meret_x,meret_y);
    kep << genv::color(50,50,50);
    kep << genv::move_to(0,0) << genv::line(0,meret_y);
    kep << genv::move_to(0,0) << genv::line(meret_x,0);
    kep << genv::move_to(meret_x-1,meret_y-1) << genv::line(0,-meret_y);
    kep << genv::move_to(meret_x-1,meret_y-1) << genv::line(-meret_x,0);

    int bar = ertek/float(max_ertek) * (meret_x-2);
    kep << genv::move_to((tipus == 1)?1:meret_x-2,1) << foreground_col << genv::box((tipus == 1)?bar:-bar,meret_y-2);
}
