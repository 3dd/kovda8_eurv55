#ifndef TANKADATOK_HPP_INCLUDED
#define TANKADATOK_HPP_INCLUDED

class TankAdatok
{
    int cso_x;
    int cso_y;
    float rad;

public:
    TankAdatok(int fx,int fy,float t_rad) : cso_x(fx), cso_y(fy), rad(t_rad)
    {

    }
    void set(int fx,int fy,float t_rad)
    {
        cso_x = fx;
        cso_y = fy;
        rad = t_rad;
    }
    int get_x() {return cso_x;}
    int get_y() {return cso_y;}
    float get_rad() {return rad;}
};

#endif // TANKADATOK_HPP_INCLUDED
