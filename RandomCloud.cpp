#include "RandomCloud.hpp"

#include <iostream>
using namespace std;

Cloud::Cloud(int fx, int fy,std::string nev,int tipus_) : x(fx), y(fy) ,tipus(tipus_)
{
    int elteres = ((tipus <= 2 && nev == "felho.kep")?rand()%100:0);
    std::ifstream f(nev);
    int X,Y,r,g,b;
    f >> X >> Y >> std::ws;

    int tip = ((tipus <= 2 && nev == "felho.kep")?tipus:1);
    kep.open(X*tip,Y*tip);
    kep.transparent(true);

    for(int i = 0; i<Y; i++)
    {
        for(int j = 0; j<X; j++)
        {
            f >> r >> g >> b >> std::ws;
            if(r > 70 || g > 70 || b > 70)kep << genv::move_to(j*tip,i*tip) << genv::color(r-elteres,g-elteres,b-elteres) << genv::box(tip,tip);
        }
    }
}

RandomClouds::RandomClouds()
{
    for(int i = 0; i<15; i++) clouds.push_back(new Cloud(rand()%palya_hossz,rand()%101-70,"felho.kep",rand()%2+1));
    for(int i = 0; i<30; i++) clouds.push_back(new Cloud(rand()%palya_hossz,-rand()%600-50,"felho.kep",rand()%2+1));

    std::vector<string> sat = { "sat1.kep" , "sat2.kep" , "sat3.kep" , "sat4.kep" , "sat5.kep" };
    for(int i = 0; i<15; i++) clouds.push_back(new Cloud(rand()%palya_hossz,-rand()%600-2000,sat[rand()%5],rand()%5+1));

    tolas_x = 0;
    tolas_y = 0;
    sebesseg = 0;
}

void RandomClouds::rajzol()
{
    for(int i = 0; i<clouds.size(); i++)
    {
        if( -220 <= clouds[i]->x-tolas_x && clouds[i]->x-tolas_x <= SX ) genv::gout << genv::stamp(clouds[i]->kep, clouds[i]->x-tolas_x, clouds[i]->y-tolas_y);
        clouds[i]->x += sebesseg * clouds[i]->tipus;

        if( clouds[i]->x < -220 )
        {
            clouds[i]->x = palya_hossz;
            clouds[i]->y += rand()%51-25;
        }
        if( palya_hossz < clouds[i]->x )
        {
            clouds[i]->x = -220;
            clouds[i]->y += rand()%51-25;
        }
    }
}
