#include "RSDL-master/src/rsdl.hpp"
#include "Missile.hpp"

using namespace std;

#define COST_MISSILE 70
#define UPDATE_MISSILE 60
#define DAMAGE_MISSILE 75
#define ATTACK_PER_MILISECOND_MISSILE 3000
#define INCREASE_UPGRADE_MISSILE 75
#define MISSILE_TYPE 2
#define MISSILE1_IMAGE "./Assets/towers/missile1.png"
#define MISSILE2_IMAGE "./Assets/towers/missile2.png"
#define MISSILE3_IMAGE "./Assets/towers/missile3.png"

Missile::Missile(double input_x, double input_y)
{
    x_coordinate = input_x;
    y_coordinate = input_y;
    cost = COST_MISSILE;
    attack_per_millisecond = ATTACK_PER_MILISECOND_MISSILE;
    cost_upgrade = UPDATE_MISSILE;
    increase_after_upgrade = INCREASE_UPGRADE_MISSILE;
    damage_attack = DAMAGE_MISSILE;
    level = 1;
    radius = 50;
    angle = 0;
    time_pass_last_shoot = 0;
}
void Missile::draw(Window* game_window)
{
    if(level == 1)
        game_window->draw_img(MISSILE1_IMAGE,get_rectangle(),NULL_RECT,-50 - angle);
    else if(level == 2)
        game_window->draw_img(MISSILE2_IMAGE,get_rectangle(),NULL_RECT,-50 - angle);
    else
        game_window->draw_img(MISSILE3_IMAGE,get_rectangle(),NULL_RECT,-50 - angle);
}
void Missile::attack(Wave* wave)
{
    attack_by_type(MISSILE_TYPE, wave);
}
