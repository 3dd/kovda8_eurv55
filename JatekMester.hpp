#ifndef JATEKMESTER_HPP_INCLUDED
#define JATEKMESTER_HPP_INCLUDED

#include "GameMenu.hpp" ///minden #include

using namespace genv;

extern const int SX;
extern const int SY;
extern const int palya_hossz;
extern const float PI;

class JatekMester
{
protected:
    std::vector<Widgets*> widgets;
    event ev;

    void widget_kezel();
    void widget_rajzol();

    void gui(Widgets * temp);

    virtual void gm_main() = 0;

public:
    JatekMester(std::string nev);
    void run();
};

#endif // JATEKMESTER_HPP_INCLUDED
