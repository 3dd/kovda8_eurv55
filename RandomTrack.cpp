#include "RandomTrack.hpp"

void RandomTrack::general(int x1, int x2, float range)
{
    int c = x2 - x1;
    if(c <= 1) return;
    float hx = (x2 - x1) / 2;

    float a = track[x1]->y;
    float b = track[x2]->y;
    float d = (a + b) / 2 + random() * range;

    float f = (a + b + d + d) / 4 + random() * range;
    track[x1 + hx]->y = f;

    general(x1, x1 + hx, range / 2.0);
    general(x1 + hx, x2, range / 2.0);
}

RandomTrack::RandomTrack(int palya_hossza)
{
    srand(time(0));

    track.push_back(new KOORD_palya(0, SY / 3));
    for(int i = 1; i < palya_hossza - 1; i++) track.push_back(new KOORD_palya(i, 0));
    track.push_back(new KOORD_palya(palya_hossza - 1, SY / 3));

    general(0, palya_hossza - 1, 500);

    for(int i = 0; i < palya_hossza; i++) track[i]->csikok();

    P1 = new Tank(track[300]->y, track[400]->y, 250, SY - track[250]->y - 140, 1);
    P2 = new Tank(track[palya_hossza - 400]->y, track[palya_hossza - 300]->y, palya_hossza - 450, SY - track[palya_hossza - 450]->y - 140, 2);

    tolas_x = 0;
    tolas_y = 0;
}

void RandomTrack::rajzol()
{
    genv::gout << genv::move_to(0, 0) << genv::color(10, 10, 50) << genv::box(SX, SY);

    for(int i = 0 + tolas_x; i < SX + tolas_x; i++)
    {
        genv::gout << genv::stamp(track[i]->csik, track[i]->x - tolas_x, SY - track[i]->y - tolas_y);
    }

    if(tolas_x <= 500) P1->rajzol(tolas_x, tolas_y);
    if(palya_hossz - 500 - SX <= tolas_x) P2->rajzol(tolas_x, tolas_y);
}

bool RandomTrack::talalat(int fx, int fy)
{
    if( SY - track[fx]->y <= fy ) return true;
    else return false;
}
