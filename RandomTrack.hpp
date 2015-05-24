#ifndef RANDOMTRACK_HPP_INCLUDED
#define RANDOMTRACK_HPP_INCLUDED

#include "Tank.hpp"

extern const int SX;
extern const int SY;
extern const int palya_hossz;

struct KOORD_palya
{
    float x, y;
    bool nyitva;
    genv::canvas csik;

    KOORD_palya(int x_, int y_) : x(x_), y(y_) { nyitva = false; }
    void csikok()
    {
        if(y < 0) y = 0;
        csik.open(1, y + 1);
        csik << genv::color(190, 100, 50) << genv::move_to(0, 0) << genv::box(1, y + 1);
    }
};

class RandomTrack
{
    std::vector<KOORD_palya*> track;

    int tolas_x;
    int tolas_y;

    Tank * P1;
    Tank * P2;

    float random() { return float(rand() % 101 - 50) / 100; }
    void general(int x1, int x2, float range);

public:
    RandomTrack(int palya_hossza);

    bool talalat(int fx, int fy);

    void rajzol();
    void set_tolas_x(int temp) { tolas_x = temp; }
    void set_tolas_y(int temp) { tolas_y = temp; }

    bool tank_sebzese(int fx, int fy) { return ( P1->talalat(fx, fy) || P2->talalat(fx, fy) ); }
    bool P1_sebzese(int fx, int fy) { return P1->talalat(fx, fy); }
    bool P2_sebzese(int fx, int fy) { return P2->talalat(fx, fy); }

    void P1_set_sebzes(int temp) { P1->set_sebzes(temp); }
    void P2_set_sebzes(int temp) { P2->set_sebzes(temp); }

    int P1_elet() { return P1->get_elet(); }
    int P2_elet() { return P2->get_elet(); }

    void set_P1_cso_rad(float temp) { P1->set_cso_rad(temp); }
    void set_P2_cso_rad(float temp) { P2->set_cso_rad(temp); }

    float get_P1_cso_rad() { return P1->get_cso_rad(); }
    float get_P2_cso_rad() { return P2->get_cso_rad(); }

    int get_P1_cso_x() { return P1->get_cso_e_x(); }
    int get_P2_cso_x() { return P2->get_cso_e_x(); }

    int get_P1_cso_y() { return P1->get_cso_e_y(); }
    int get_P2_cso_y() { return P2->get_cso_e_y(); }
};

#endif // RANDOMTRACK_HPP_INCLUDED
