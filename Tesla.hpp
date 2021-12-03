#ifndef TESLA
#define TESLA "tesla"
#include "RSDL-master/src/rsdl.hpp"
#include "Tower.hpp"
#include "Wave.hpp"

class Tesla : public Tower
{
public:
    Tesla(double input_x, double input_y);
    virtual void draw(Window* game_window);
    virtual void attack(Wave* wave);
private:
};
#endif
