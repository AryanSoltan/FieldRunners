#include "RSDL-master/src/rsdl.hpp"
#include "Gattling.hpp"

using namespace std;

#define COST_GATTLING 55
#define UPDATE_GATTLING 40
#define DAMAGE_GATTLING 35
#define ATTACK_PER_MILISECOND_GATTLING 1000
#define INCREASE_UPGRADE_GATTLING 35
#define  GATTLING1_IMAGE "./Assets/towers/gattling1.png"
#define  GATTLING2_IMAGE "./Assets/towers/gattling2.png"
#define  GATTLING3_IMAGE "./Assets/towers/gattling3.png"
#define GATTLING_TYPE 1

Gattling::Gattling(double input_x, double input_y)
{
    x_coordinate = input_x;
    y_coordinate = input_y;
    cost = COST_GATTLING;
    attack_per_millisecond = ATTACK_PER_MILISECOND_GATTLING;
    cost_upgrade = UPDATE_GATTLING;
    increase_after_upgrade = INCREASE_UPGRADE_GATTLING;
    damage_attack = DAMAGE_GATTLING;
    level = 1;
    time_pass_last_shoot = 0;
    angle = 0;
    radius = 0;
}
void Gattling::draw(Window* game_window)
{
    if(level == 1)
        game_window->draw_img(GATTLING1_IMAGE,get_rectangle(),NULL_RECT,-50 - angle);
    else if(level == 2)
        game_window->draw_img(GATTLING2_IMAGE,get_rectangle(),NULL_RECT,-50 - angle);
    else
        game_window->draw_img(GATTLING3_IMAGE,get_rectangle(),NULL_RECT,-50 - angle);
}
void Gattling::attack(Wave* wave)
{
    attack_by_type(GATTLING_TYPE,wave);
}
