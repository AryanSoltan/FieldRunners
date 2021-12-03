#ifndef GATTLING
#define GATTLING "gatling"
#include "RSDL-master/src/rsdl.hpp"
#include "Tower.hpp"

class Gattling : public Tower
{
public:
    Gattling(double input_x, double input_y);
    virtual void draw(Window* game_window);
    virtual void attack(Wave* wave);
private:
};
#endif
