#ifndef MISSILE
#define MISSILE "missile"
#include "RSDL-master/src/rsdl.hpp"
#include "Tower.hpp"
#include "Wave.hpp"
class Missile : public Tower
{
public:
    Missile(double input_x, double input_y);
    virtual void draw(Window* game_window);
    virtual void attack(Wave* wave);
private:
};
#endif
