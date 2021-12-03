#ifndef GLUE
#define GLUE "glue"
#include "RSDL-master/src/rsdl.hpp"
#include "Wave.hpp"
#include "Tower.hpp"
class Glue : public Tower
{
public:
    Glue(double input_x, double input_y);
    virtual void draw(Window* game_window);
    virtual void attack(Wave* wave);
private:
};
#endif
