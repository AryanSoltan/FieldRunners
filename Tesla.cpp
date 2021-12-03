#include "RSDL-master/src/rsdl.hpp"
#include "Tesla.hpp"
#include "Wave.hpp"

using namespace std;

#define COST_TESLA 120
#define UPDATE_TESLA 100
#define DAMAGE_TESLA 700
#define ATTACK_PER_MILISECOND_TESLA 1500
#define INCREASE_UPGRADE_TESLA 1000
#define  TESLA1_IMAGE "./Assets/towers/tesla1.png"
#define TESLA2_IMAGE "./Assets/towers/tesla2.png"
#define TESLA3_IMAGE "./Assets/towers/tesla3.png"
#define TESLA_TYPE 3

Tesla::Tesla(double input_x, double input_y)
{
    x_coordinate = input_x;
    y_coordinate = input_y;
    cost = COST_TESLA;
    attack_per_millisecond = ATTACK_PER_MILISECOND_TESLA;
    cost_upgrade = UPDATE_TESLA;
    increase_after_upgrade = INCREASE_UPGRADE_TESLA;
    damage_attack = DAMAGE_TESLA;
    level = 1;
    time_pass_last_shoot = 0;
    angle = 0;
}
void Tesla::draw(Window* game_window)
{
    if(level == 1)
        game_window->draw_img(TESLA1_IMAGE,get_rectangle());
    else if(level == 2)
        game_window->draw_img(TESLA2_IMAGE,get_rectangle());
    else
        game_window->draw_img(TESLA3_IMAGE,get_rectangle());
}
void Tesla::attack(Wave* wave)
{
    attack_by_type(TESLA_TYPE,wave);
}
