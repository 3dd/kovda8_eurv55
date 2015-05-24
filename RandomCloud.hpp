#ifndef RANDOMCLOUD_HPP_INCLUDED
#define RANDOMCLOUD_HPP_INCLUDED

#include "graphics.hpp"

#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>

extern const int SX;
extern const int SY;
extern const int palya_hossz;

struct Cloud
{
    float x, y;
    genv::canvas kep;

    int tipus;

    Cloud(int fx, int fy,std::string nev,int tipus_);
};

class RandomClouds
{
    std::vector<Cloud*> clouds;

    float sebesseg;

    int tolas_x;
    int tolas_y;

public:
    RandomClouds();
    void rajzol();

    void set_tolas_x(int temp) {tolas_x = temp;}
    void set_tolas_y(int temp) {tolas_y = temp;}
    void set_sebesseg(float temp) {sebesseg = temp;}
    float get_sebesseg() {return sebesseg;}
};

#endif // RANDOMCLOUD_HPP_INCLUDED
