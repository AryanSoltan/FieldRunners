#ifndef SHOOT
#define SHOOT "shoot"

#include "GameIcons.hpp"
#include "RSDL-master/src/rsdl.hpp"

class Shoot : public GameIcon
{
public:
    Shoot(double input_x_start, double input_y_start, int input_time_to_reach, int input_damage, int input_type, int input_radius, int input_level);
    void walk(int time, double destination_x, double destination_y);
    void update(int time);
    void draw(Window* game_window,int angle);
    int get_damage();
    double get_x();
    double get_y();
    bool is_reach_destination();
    int get_radius();
    bool is_missile();
    bool is_glue();
    int get_time_effect();
private:
    int time_pass;
    int time_to_reach;
    double x_start;
    double y_start;
    int radius;
    int damage;
    int type;
    int level;
};
#endif
