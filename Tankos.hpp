#ifndef TANKOS_HPP_INCLUDED
#define TANKOS_HPP_INCLUDED

#include "JatekMester.hpp"


///--------------------------------
#include <iostream>
using namespace std;
///--------------------------------


const int SX = 1000;
const int SY = 600;
const int palya_hossz = 6000;
const float PI = 3.14159;

class Tankos : public JatekMester
{
    int jatekos = 0;
    int menu_allasa = 0;

    bool szel_on_off = true;
    bool hard_core_mode = false;

    GameMenu * menu;

    RandomClouds * felhok;
    RandomTrack * palya;

    Lovedekek * lovedekek;

    TankAdatok * P1_adatok;
    TankAdatok * P2_adatok;

    int x_tolas = 0;
    int y_tolas = 0;

    /// :::::::::: CONTROL WIDGETS :::::::::: ///

    KDStaticText * P1_felirat;
    KDStaticText * P2_felirat;

    KDStaticText * P1_elet;
    KDStaticText * P2_elet;

    KDNumericControll * P1_szogallito;
    KDNumericControll * P2_szogallito;

    KDStatusBar * P1_erossegallito;
    KDStatusBar * P2_erossegallito;

    Lovesgomb * P1_lovesgomb;
    Lovesgomb * P2_lovesgomb;

    /// :::::::::::::::::::::::::::::::::::: ///

    void grafika();
    void csere();
    void tolas();

public:
    Tankos();
    void gm_main()
    {
        switch(menu_allasa)
        {
        case 0:
        {
            menu->kezel(ev);
            menu->rajzol();
        }
        break;
        case 1:
        {
            grafika();
            csere();
            tolas();

            ///--------- Gomnyomasok ----------///

            P1_lovesgomb->nyomva(ev);
            P2_lovesgomb->nyomva(ev);

            ///--------------------------------///

            menu->game_over(palya);
        }
        break;
        case 2:
        {
            menu->game_over(palya);
        }
        break;
        }
    }
};
Tankos::Tankos() : JatekMester("Tankos")
{
    srand(time(0));

    ///-------------///
    gout << move_to(SX/2-gout.twidth("EURV55")/2,SY/2-200) << text("EURV55™") << refresh;
    string asd = "bla bla bla nevek nevek nevek amiket senki nem olvas el nevek nevek nevek nevek nevek bla bla bla";
    for(int i = 0;i<20;i++)
    {
        gout << move_to(SX/2-gout.twidth(asd)/2,SY/2-100+20*i)
          << text(asd) << refresh;
    }
    ///-------------///

    felhok = new RandomClouds;
    palya = new RandomTrack(palya_hossz);

    menu = new GameMenu(&menu_allasa, &szel_on_off, &hard_core_mode);

    lovedekek = new Lovedekek(&jatekos, &szel_on_off, &hard_core_mode, palya, felhok);

    P1_adatok = new TankAdatok(0, 0, 0);
    P2_adatok = new TankAdatok(0, 0, 0);

    /// :::::::::: CONTROL WIDGETS :::::::::: ///

    gui(P1_felirat = new KDStaticText(50, 50, 100, 250, 120, "P1"));
    gui(P1_elet = new KDStaticText(160, 130, 40, 200, 100, "100%"));
    P1_felirat->set_fore_col(genv::color(0, 200, 250));
    P1_elet->set_fore_col(genv::color(0, 200, 250));
    gui(P1_szogallito = new KDNumericControll(30, SY - 52, 200, 0, 0, 90, 3));
    P1_szogallito->set_button_col(genv::color(0, 200, 255));
    gui(P1_erossegallito = new KDStatusBar(260, SY - 52, 300, 150 + rand() % 31 - 15, 20, 1));
    gui(P1_lovesgomb = new Lovesgomb(P1_erossegallito, lovedekek, P1_adatok, 30, SY - 100, 200, 30, 20, "Fire!!", 0, 200, 250));

    gui(P2_felirat = new KDStaticText(palya_hossz - 280, 50, 100, 250, 120, "P2"));
    gui(P2_elet = new KDStaticText(palya_hossz - 150, 130, 40, 200, 100, "100%"));
    P2_felirat->set_fore_col(genv::color(250, 200, 0));
    P2_elet->set_fore_col(genv::color(250, 200, 0));
    gui(P2_szogallito = new KDNumericControll(palya_hossz - 230, SY - 52, 200, 0, 0, 90, 3));
    P2_szogallito->set_button_col(genv::color(250, 200, 0));
    gui(P2_erossegallito = new KDStatusBar(palya_hossz - 560, SY - 52, 300, 150 + rand() % 31 - 15, 20, 2));
    gui(P2_lovesgomb = new Lovesgomb(P2_erossegallito, lovedekek, P2_adatok, palya_hossz - 230, SY - 100, 200, 30, 20, "Fire!!", 250, 200, 0));

    /// ::::::::::::::::::::::::::::::::::::: ///
}
void Tankos::grafika()
{
    if(ev.type == ev_timer)
    {
        stringstream P1_elet_;
        P1_elet_ << palya->P1_elet();
        P1_elet->set_string(P1_elet_.str() + "%");
        stringstream P2_elet_;
        P2_elet_ << palya->P2_elet();
        P2_elet->set_string(P2_elet_.str() + "%");

        palya->set_P1_cso_rad( P1_szogallito->get_ertek() / 180.0 * PI );
        palya->set_P2_cso_rad( P2_szogallito->get_ertek() / 180.0 * PI );

        palya->rajzol();

        P1_adatok->set(palya->get_P1_cso_x(), palya->get_P1_cso_y(), palya->get_P1_cso_rad());
        P2_adatok->set(palya->get_P2_cso_x(), palya->get_P2_cso_y(), palya->get_P2_cso_rad() + PI);

        widget_rajzol();
        lovedekek->rajzol();
        felhok->rajzol();
    }
}
void Tankos::tolas()
{
    if( lovedekek->get_ures_e() )
    {
        switch(jatekos)
        {
        case 0:
        {
            y_tolas = lovedekek->get_y() - palya->get_P1_cso_y();
            if( y_tolas > 0 ) y_tolas = 0;
            x_tolas = lovedekek->get_x() - palya->get_P1_cso_x();
            if( x_tolas < 0 ) x_tolas = 0;
            else if( x_tolas > palya_hossz - SX ) x_tolas = palya_hossz - SX;
        }
        break;
        case 1:
        {
            y_tolas = lovedekek->get_y() - palya->get_P2_cso_y();
            if( y_tolas > 0 ) y_tolas = 0;
            x_tolas = (palya_hossz - SX) - (palya->get_P2_cso_x() - lovedekek->get_x());
            if( x_tolas < 0 ) x_tolas = 0;
            else if( x_tolas > palya_hossz - SX ) x_tolas = palya_hossz - SX;
        }
        break;
        }
    }

    felhok->set_tolas_x(x_tolas);
    palya->set_tolas_x(x_tolas);
    lovedekek->set_tolas_x(x_tolas);

    felhok->set_tolas_y(y_tolas);
    palya->set_tolas_y(y_tolas);
    lovedekek->set_tolas_y(y_tolas);

    for(Widgets * t : widgets) t->set_x_y(-x_tolas, -y_tolas);
}
void Tankos::csere()
{
    if( lovedekek->get_csere() )
    {
        switch(jatekos)
        {
        case 0:
        {
            if( x_tolas < 4900 ) x_tolas += 100;
            else
            {
                x_tolas = 5000;
                jatekos = 1;
                lovedekek->set_csere(false);
            }
            y_tolas = 0;
        }
        break;
        case 1:
        {
            if( x_tolas > 100 ) x_tolas -= 100;
            else
            {
                x_tolas = 0;
                jatekos = 0;
                lovedekek->set_csere(false);
            }
            y_tolas = 0;
        }
        break;
        }
    }
}

#endif // TANKOS_HPP_INCLUDED
