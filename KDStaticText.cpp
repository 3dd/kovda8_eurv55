#include "KDStaticText.hpp"

KDStaticText::KDStaticText(int fx,int fy,int betu_merete,int x_meret,int y_meret,std::string szov) : Widgets(fx,fy,x_meret,y_meret)
{
    szoveg = szov;
    betumeret = betu_merete;

    ujra_rajzol();
}
void KDStaticText::rajzol()
{
    genv::gout << genv::stamp(kep,x,y);
}

void KDStaticText::ujra_rajzol()
{
    kep.open(meret_x,meret_y);
    kep.transparent(true);
    kep.load_font("LiberationSans-Regular.ttf",betumeret,true);
    kep << genv::move_to(0,0) << foreground_col << genv::text(szoveg);
}
