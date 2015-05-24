#include "Lovedekek.hpp"

Lovedek::Lovedek(int fx, int fy,int sebesseg_,float rad_) : x(fx), y(fy), sebesseg(sebesseg_), rad(-rad_)
{
    std::ifstream f("labda20x20.kep");
    int X,Y,r,g,b;
    f >> X >> Y >> std::ws;
    for(int i = 0; i<Y; i++)
    {
        for(int j = 0; j<X; j++)
        {
            f >> r >> g >> b >> std::ws;
            if(r != 0 || g != 0 || b != 0) golyo.push_back(new KOORD(j,i,r,g,b));
        }
    }
}

void Lovedek::mozog()
{
    x += (szelirany*sebesseg/4 + sebesseg) * cos(rad);
    y += (szelirany*sebesseg/4 + sebesseg) * sin(rad) + ido;

    ido+=.1;
    golyo_rad -=.01*(szelirany*sebesseg/2 + sebesseg);
}

void Lovedek::rajzol(int fx, int fy)
{
    mozog();

    genv::canvas golyo_;
    golyo_.open(20,20);
    golyo_.transparent(true);

    for(int i = 0; i<golyo.size(); i++)
    {
        float labda_x = x_forgato(golyo[i]->x, golyo[i]->y,golyo_rad,20,20);
        float labda_y = y_forgato(golyo[i]->x, golyo[i]->y,golyo_rad,20,20);

        golyo_ << genv::move_to( labda_x , labda_y ) << genv::color(golyo[i]->r,golyo[i]->g,golyo[i]->b) << genv::box(2,2);
    }

    genv::gout << genv::stamp(golyo_,x-fx-10,y-fy-10);
}

Lovedekek::Lovedekek(int * jatekos_,bool * szel_,bool * hard_,RandomTrack * rt_ , RandomClouds * rc_)
{
    szel = szel_;
    hard = hard_;
    rt = rt_;
    rc = rc_;
    jatekos = jatekos_;
}

void Lovedekek::loves(float x,float y,float sebesseg,float rad)
{
    if(lovedekek.empty()) lovedekek.push_back( Lovedek(x,y,sebesseg,rad) );
}

void Lovedekek::rajzol()
{
    for(Lovedek & t:lovedekek)
    {
        t.set_szelirany( (*jatekos == 0)?rc->get_sebesseg():-rc->get_sebesseg() );
        t.rajzol(tolas_x,tolas_y);
    }

    int i = 0;
    while(i < lovedekek.size())
    {
        if( lovedekek[i].get_x() <= 0 || palya_hossz <= lovedekek[i].get_x() || rt->tank_sebzese(int(lovedekek[i].get_x()),int(lovedekek[i].get_y())) || rt->talalat(int(lovedekek[i].get_x()),int(lovedekek[i].get_y())))
        {
            lovedekek[i] = lovedekek[lovedekek.size()-1];
            lovedekek.pop_back();
            rc->set_sebesseg( (*szel)?float(rand()%151-75)/100:0 );

            if(rt->P1_sebzese(int(lovedekek[i].get_x()),int(lovedekek[i].get_y()))) rt->P1_set_sebzes((*hard)?lovedekek[i].get_sebzes():110);
            if(rt->P2_sebzese(int(lovedekek[i].get_x()),int(lovedekek[i].get_y()))) rt->P2_set_sebzes((*hard)?lovedekek[i].get_sebzes():110);

            csere = true;
        }
        else i++;
    }
}

