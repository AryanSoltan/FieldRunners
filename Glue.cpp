#include "RSDL-master/src/rsdl.hpp"
#include "Glue.hpp"
#include "Wave.hpp"

using namespace std;

#define COST_GLUE 60
#define UPDATE_GLUE 45
#define DAMAGE_GLUE 40
#define ATTACK_PER_MILISECOND_GLUE 2500
#define INCREASE_UPGRADE_GLUE 10
#define GLUE1_IMAGE "./Assets/towers/glue1.png"
#define GLUE2_IMAGE "./Assets/towers/glue2.png"
#define GLUE3_IMAGE "./Assets/towers/glue3.png"

#define GLUE_TYPE 4

Glue::Glue(double input_x, double input_y)
{
    x_coordinate = input_x;
    y_coordinate = input_y;
    cost = COST_GLUE;
    attack_per_millisecond = ATTACK_PER_MILISECOND_GLUE;
    cost_upgrade = UPDATE_GLUE;
    increase_after_upgrade = INCREASE_UPGRADE_GLUE;
    damage_attack = DAMAGE_GLUE;
    level = 1;
    radius = 30;
    time_pass_last_shoot = 0;
    angle = 0;
}
void Glue::draw(Window* game_window)
{
    if(level == 1)
        game_window->draw_img(GLUE1_IMAGE,get_rectangle(),NULL_RECT,-50 - angle);
    else if(level == 2)
        game_window->draw_img(GLUE2_IMAGE,get_rectangle(),NULL_RECT,-50 - angle);
    else
        game_window->draw_img(GLUE3_IMAGE,get_rectangle(),NULL_RECT,-50 - angle);
}
void Glue::attack(Wave* wave)
{
    attack_by_type(GLUE_TYPE, wave);
}
