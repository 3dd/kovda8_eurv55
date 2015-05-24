#include "GameMenu.hpp"

GameMenu::GameMenu(int * menu,bool * _szel_,bool * _hard_)
{
    menu_ = menu;
    szel_ = _szel_;
    hard_ = _hard_;

    play = new PlayGomb(30,360,270,100,menu);
    play->set_back_col(genv::color(95,100,60));

    op = new SettingsGomb(30,470,270,100,&sett_);
    op->set_back_col(genv::color(95,100,60));

    w.push_back(szel = new KDRadioBox(400,200,250, { "wind ON" , "wind OFF" }));
    w.push_back(hard = new KDCheckBox(400,300,30,30,false));
    w.push_back(hard_core_mod = new KDStaticText(435,300,27,200,30,"hard core mod"));

    std::ifstream f("menu.kep");
    int X,Y,r,g,b;
    f >> X >> Y >> std::ws;
    menukep.open(X,Y);
    for(int i = 0; i<Y; i++)
    {
        for(int j = 0; j<X; j++)
        {
            f >> r >> g >> b >> std::ws;
            menukep << genv::move_to(j,i) << genv::color(r,g,b) << genv::dot;
        }
    }

    settkep.open(SX,SY);
    settkep.transparent(true);
    for(int i = 0; i<SY/2; i++)settkep << genv::move_to(0,i*2) << genv::color(50,50,50) << genv::line(SX,0);
    for(int i = 0; i<SX/2; i++)settkep << genv::move_to(i*2,0) << genv::color(50,50,50) << genv::line(0,SY);
}

void GameMenu::rajzol()
{
    genv::gout << genv::stamp(menukep,0,0);
    play->rajzol();

    if(sett_)
    {
        genv::gout << genv::stamp(settkep,0,0);
        genv::gout << genv::move_to(350,150) << genv::color(95+30,100+30,60+30) << genv::box(355,220);
        for(Widgets * t:w) t->rajzol();
    }
    op->rajzol();
}

void GameMenu::kezel(genv::event ev)
{
    if(sett_)
    {
        for(Widgets * t:w) t->kezel(ev);

        if(szel->get_ertek() == 0) *szel_ = true;
        if(szel->get_ertek() == 1) *szel_ = false;

        *hard_ = !hard->get_pipa();
    }
    else
    {
        play->nyomva(ev);
        play->kezel(ev);
    }

    op->kezel(ev);
    op->nyomva(ev);
}

void GameMenu::game_over(RandomTrack * rc)
{
    if(rc->P1_elet() < 0 || rc->P2_elet() < 0) *menu_ = 2;
    if( *menu_ == 2 )
    {
        genv::gout << genv::move_to(0,0) << genv::color(0,0,0) << genv::box(SX,SY);
        genv::gout.load_font("LiberationSans-Regular.ttf",100,true);

        if(rc->P2_elet() < 0) genv::gout << genv::color(0,200,255) << genv::move_to(SX/2-genv::gout.twidth("P1 won!")/2,230) << genv::text("P1 won!");
        if(rc->P1_elet() < 0) genv::gout << genv::color(255,200,0) << genv::move_to(SX/2-genv::gout.twidth("P2 won!")/2,230) << genv::text("P2 won!");
    }
}
