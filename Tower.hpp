#ifndef TOWER
#define TOWER "tower"
#include "GameIcons.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include "Wave.hpp"
#include "Enemy.hpp"

class Tower : public GameIcon
{
public:
    virtual void draw(Window* game_window) = 0;
    virtual void attack(Wave* wave);
    bool is_in_range(Enemy* input_enemy);
    void update(int time_update);
    bool can_shoot(Wave* wave);
    int get_cost();
    int get_cost_upgrade();
    void upgrade();
    bool can_upgrade(int amount_user_money);
    bool is_in_location(Point location);
protected:
    int cost;
    int attack_per_millisecond;
    int cost_upgrade;
    int increase_after_upgrade;
    int damage_attack;
    int level;
    int time_pass_last_shoot;
    int angle;
    int radius;
    Enemy* find_enemy(Wave* wave);
    void attack_by_type(int type,Wave* wave);
};
#endif
