#ifndef GAMEMENU_HPP_INCLUDED
#define GAMEMENU_HPP_INCLUDED

#include "Lovesgomb.hpp"

#include "KDCheckBox.hpp"
#include "KDRadioBox.hpp"

class PlayGomb : public KDButton
{
    int * menu;

public:
    PlayGomb(int fx, int fy, int sx, int sy,int * menu_) : KDButton(fx,fy,sx,sy,40,"Play!")
    {
        menu = menu_;
    }
    void nyomva(genv::event ev)
    {
        if(ev.button == -genv::btn_left && lenyomva)
        {
            *menu = 1;
        }
    }
};

class SettingsGomb : public KDButton
{

    bool * sett_;

public:
    SettingsGomb(int fx, int fy, int sx, int sy,bool * _sett_) : KDButton(fx,fy,sx,sy,35,"Settings")
    {
        sett_ = _sett_;
    }
    void nyomva(genv::event ev)
    {
        if(ev.button == genv::btn_left && lenyomva)
        {
            if(*sett_)
            {
                *sett_ = false;
                set_felir("Settings");
            }
            else if(!(*sett_))
            {
                *sett_ = true;
                set_felir("<- back");
            }
        }
    }
};

class GameMenu
{
    genv::canvas menukep;
    genv::canvas settkep;

    std::vector<Widgets*> w;

    ///-----------------------------///
    ///fo menugombok
    PlayGomb * play;
    SettingsGomb * op;

    ///settings gombok
    KDRadioBox * szel;
    KDCheckBox * hard;
    KDStaticText * hard_core_mod;

    ///-----------------------------///

    int * menu_;

    bool * szel_;
    bool * hard_;

    bool sett_ = false;
    std::string szoveg = "";

public:
    GameMenu(int * menu,bool * _szel_,bool * _hard_);
    void rajzol();
    void kezel(genv::event ev);
    void game_over(RandomTrack * rc);
};


#endif // GAMEMENU_HPP_INCLUDED
