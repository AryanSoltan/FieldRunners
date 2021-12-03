#include "Tower.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include "Wave.hpp"
#include "Enemy.hpp"

#define GATTLING_RADIUS 150

using namespace std;

Enemy* Tower::find_enemy(Wave* wave)
{
    Enemy* nearest_enemy = wave->find_nearest(x_coordinate,y_coordinate);
}
void Tower::attack(Wave* wave)
{
    Enemy* attacked_enemy = find_enemy(wave);
    if(attacked_enemy == NULL)
    {
        return;
    }
    if(is_in_range(attacked_enemy)){
        attacked_enemy->damage_heart(damage_attack);
    }
}
bool Tower::is_in_range(Enemy* input_enemy)
{
    double distance = input_enemy->find_distance(x_coordinate, y_coordinate);
    if(distance <= GATTLING_RADIUS)
        return true;
    return false;
}
void Tower::update(int time_update)
{
    time_pass_last_shoot += time_update;
}
bool Tower::can_shoot(Wave* wave)
{
    if(time_pass_last_shoot < attack_per_millisecond)
    {
        return false;
    }
    Enemy* attacked_enemy = find_enemy(wave);
    if(attacked_enemy == NULL)
    {
        return false;
    }
    if(is_in_range(attacked_enemy)){
        return true;
    }
    return false;
}
int Tower::get_cost(){return cost;}
int Tower::get_cost_upgrade(){return cost_upgrade;}
bool Tower::can_upgrade(int amount_user_money)
{
    if(level == 3)
    {
        return false;
    }
    if(amount_user_money < cost_upgrade)
    {
        return false;
    }
    return true;
}
void Tower::upgrade()
{
    damage_attack += increase_after_upgrade;
    level++;
}
bool Tower::is_in_location(Point location)
{
    if(x_coordinate == location.x && y_coordinate == location.y)
        return true;
    return false;
}
void Tower::attack_by_type(int type,Wave* wave)
{
    Enemy* attacked_enemy = find_enemy(wave);
    if(attacked_enemy == NULL)
    {
        return;
    }
    if(!is_in_range(attacked_enemy))
        return;
    double x_enemy = attacked_enemy->get_x();
    double y_enemy = attacked_enemy->get_y();
    angle = get_angle(x_enemy, y_enemy);
    Shoot* new_shoot = new Shoot(x_coordinate, y_coordinate, attack_per_millisecond, damage_attack, type, radius, level);
    attacked_enemy->add_shoot(new_shoot);
    time_pass_last_shoot = 0;
}
