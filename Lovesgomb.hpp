#ifndef LOVESGOMB_HPP_INCLUDED
#define LOVESGOMB_HPP_INCLUDED

#include "KDButton.hpp"
#include "KDNumericControll.hpp"
#include "KDStaticText.hpp"
#include "KDStatusBar.hpp"

#include "Lovedekek.hpp"      /// #include felho / #include palya
#include "TankAdatok.hpp"

class Lovesgomb : public KDButton
{
    KDStatusBar * erosseg;
    Lovedekek * lovedekek;
    TankAdatok * adatok;
    /*-------------------
    tank_adatok[0] => cso_x
    tank_adatok[1] => cso_y
    tank_adatok[2] => cso_rad
    -------------------*/

public:
    Lovesgomb(KDStatusBar * erosseg_,Lovedekek * lovedekek_,TankAdatok * adatok_,int fx,int fy,int x_meret,int y_meret,int betu_merete,std::string felir,int r,int g,int b)
        : KDButton(fx,fy,x_meret,y_meret,betu_merete,felir)
    {
        set_back_col(genv::color(r,g,b));
        lovedekek = lovedekek_;
        adatok = adatok_;
        erosseg = erosseg_;
    }
    void nyomva(genv::event ev)
    {
        if(lenyomva && ev.button == genv::btn_left)
        {
            lovedekek->loves( adatok->get_x() , adatok->get_y() , erosseg->get_ertek()/5.00 , adatok->get_rad() );
        }
    }
};

#endif // LOVESGOMB_HPP_INCLUDED
