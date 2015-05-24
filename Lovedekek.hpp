#ifndef LOVEDEK_HPP_INCLUDED
#define LOVEDEK_HPP_INCLUDED

#include "RandomTrack.hpp"
#include "RandomCloud.hpp"

#include <stdlib.h>

extern const int SX;
extern const int SY;
extern const int palya_hossz;
extern const float PI;

class Lovedek
{
protected:
    float x, y;
    int sebesseg;

    std::vector<KOORD*> golyo;
    float golyo_rad;

    int sebzes = 15;
    float rad;

    float ido = 0;

    float szelirany = 0;

public:
    Lovedek(int fx, int fy, int sebesseg_, float rad_);
    void mozog();
    void rajzol(int fx, int fy);

    float get_x() {return x;}
    float get_y() {return y;}

    float get_sebzes() {return sebzes + abs(sebesseg);}

    void set_szelirany(float temp) {szelirany = temp;}
};

class Lovedekek
{
    std::vector<Lovedek> lovedekek;

    int tolas_x = 0;
    int tolas_y = 0;

    bool csere = false;
    int * jatekos;

    RandomTrack * rt;
    RandomClouds * rc;
    bool * szel;
    bool * hard;

public:
    Lovedekek(int * jatekos_, bool * szel_, bool * hard_, RandomTrack * rt_ , RandomClouds * rc_);
    void loves(float x, float y, float sebesseg, float rad);

    void set_tolas_x(int temp) {tolas_x = temp;}
    void set_tolas_y(int temp) {tolas_y = temp;}

    bool get_ures_e() {return lovedekek.size();}
    int get_x() {return lovedekek[0].get_x();}
    int get_y() {return lovedekek[0].get_y();}

    void set_csere(bool temp) {csere = temp;}
    bool get_csere() {return csere;}

    void rajzol();

};

#endif // LOVEDEK_HPP_INCLUDED
