#ifndef KDSTATICTEXT_HPP_INCLUDED
#define KDSTATICTEXT_HPP_INCLUDED

#include "Widgets.hpp"

class KDStaticText : public Widgets
{
protected:
    std::string szoveg;
    int betumeret;

public:
    KDStaticText(int fx, int fy, int betu_merete, int x_meret, int y_meret, std::string szov);

    void rajzol();
    void kezel(genv::event ev) {};

    void ujra_rajzol();

    std::string get_string() {return szoveg;}
    void set_string(std::string temp) {szoveg = temp; ujra_rajzol();}
};

#endif // KDSTATICTEXT_HPP_INCLUDED
