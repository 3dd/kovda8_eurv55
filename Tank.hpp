#ifndef TANK_HPP_INCLUDED
#define TANK_HPP_INCLUDED

#include "graphics.hpp"

#include <math.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>

int x_forgato(int x,int y,float rad,int X,int Y);
int y_forgato(int x,int y,float rad,int X,int Y);

struct KOORD
{
    int x,y;
    int r,g,b;

    KOORD(int x_, int y_, int r_, int g_, int b_);
};

extern const float PI;

class Tank
{
    float cso_rad;
    float tank_rad;

    int elet = 100;

    int x,y;
    genv::canvas kep;
    std::vector<KOORD*> cso;
    int cso_eleje_x;
    int cso_eleje_y;

    int player;

public:
    Tank( int y1_0, int y2_100, int x_ , int y_, int player_ );

    bool talalat(int fx, int fy);
    void rajzol(int tolas_x, int tolas_y);
    void set_sebzes(int temp) { elet -= temp; }

    int get_elet() { return elet; }

    void set_cso_rad(float temp) { if( player == 1 ) cso_rad = temp; else cso_rad = -temp; }
    float get_cso_rad() { return cso_rad; }

    int get_cso_e_x() { return cso_eleje_x; }
    int get_cso_e_y() { return cso_eleje_y; }
};

#endif // TANK_HPP_INCLUDED
