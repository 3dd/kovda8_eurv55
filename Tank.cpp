#include "Tank.hpp"

int x_forgato(int x,int y,float rad,int X,int Y)
{
    int tempx = x-X/2;
    int tempy = -(y-Y/2);
    x = (tempx*cos(rad)) - (tempy*sin(rad));
    return x+X/2;
}
int y_forgato(int x,int y,float rad,int X,int Y)
{
    int tempx = x-X/2;
    int tempy = -(y-Y/2);
    y = (tempx*sin(rad)) + (tempy*cos(rad));
    return Y-(y+Y/2);
}

KOORD::KOORD(int x_, int y_, int r_, int g_, int b_)
{
    x = x_;
    y = y_;
    r = r_;
    g = g_;
    b = b_;
}

bool Tank::talalat(int fx, int fy)
{
    float dx = fx-x-114;
    float dy = fy-y-120;
    float tav = sqrt( pow(dx,2) + pow(dy,2) );

    return tav < 90;
}

void Tank::rajzol(int tolas_x, int tolas_y)
{
    genv::canvas cso_;
    cso_.open(178,178);
    cso_.transparent(true);

    cso_rad = (player == 1)?tank_rad + cso_rad : - tank_rad + cso_rad;
    for(int i = 0; i<cso.size(); i++)
    {
        float cso_x = x_forgato(cso[i]->x, cso[i]->y,cso_rad,178,178);
        float cso_y = y_forgato(cso[i]->x, cso[i]->y,cso_rad,178,178);

        cso_ << genv::move_to( cso_x , cso_y ) << genv::color(cso[i]->r,cso[i]->g,cso[i]->b) << genv::box(2,2);

        if(i == cso.size()/2)
        {
            cso_eleje_x = cso_x + x + ((player == 1)?32:20);
            cso_eleje_y = cso_y + y - 40;
        }
    }

    genv::gout << genv::stamp(cso_,x+((player == 1)?32:20)-tolas_x,y-40-tolas_y);

    genv::gout << genv::stamp(kep,x-tolas_x,y-tolas_y);
}

Tank::Tank( int y1_0, int y2_100, int x_ ,int y_,int player_ )
{
    cso_rad = 0;
    player = player_;
    x = x_;
    y = y_;

    cso_eleje_x = 0;
    cso_eleje_y = 0;

    float dy = (player == 1)?y1_0 - y2_100:y2_100 - y1_0;

    tank_rad = atan2(100,dy);

    if(tank_rad >= PI/2-0.01 && tank_rad <= PI/2+0.01)
    {
        tank_rad = 0;
    }
    else tank_rad -= PI/2;

    std::ifstream f("tank_test.kep");
    int X,Y,r,g,b;
    f >> X >> Y >> std::ws;
    kep.open(X,Y);
    kep.transparent(true);

    for(int i = 0; i<Y; i++)
    {
        for(int j = 0; j<X; j++)
        {
            f >> r >> g >> b >> std::ws;

            if(player == 1 && g >= 180)
            {
                r = 0;
                g = 200;
                b = 255;
            }
            if(player == 2 && g >= 180)
            {
                r = 255;
                g = 200;
                b = 0;
            }

            kep << genv::move_to((player == 1)?x_forgato(j,i,tank_rad,X,Y):X-x_forgato(j,i,tank_rad,X,Y),y_forgato(j,i,tank_rad,X,Y)) << genv::color(r,g,b) << genv::box(2,2);
        }
    }

    std::ifstream cso_f("tank_cso.kep");
    cso_f >> X >> Y >> std::ws;

    for(int i = 0; i<Y; i++)
    {
        for(int j = 0; j<X; j++)
        {
            cso_f >> r >> g >> b >> std::ws;

            if(player == 1 && g >= 230)
            {
                r = 0;
                g = 200;
                b = 255;
            }
            if(player == 2 && g >= 230)
            {
                r = 255;
                g = 200;
                b = 0;
            }

            if(r != 0 || g != 0 || b != 0) cso.push_back(new KOORD((player == 1)?j:X-j,i,r,g,b));
        }
    }
}
