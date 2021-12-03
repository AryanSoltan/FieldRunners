#ifndef ENEMYTABLE
#define ENEMYTABLE "enemytable"

#include<vector>
#include "Enemy.hpp"
#include "GameIcons.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include "EnemyTable.hpp"
#include "Shoot.hpp"


class EnemyTable
{
public:
    void update(double time);
    void add(Enemy* new_enemy);
    int get_size();
    void draw(Window* game_window);
    bool is_empty();
    Enemy* find_nearest(double input_x, double input_y);
    void clear_all();
    void delete_finished_enemies();
    int get_coins_from_kill();
    int get_damage_from_enemies();
    void delete_all_shoots_reach();
    void delete_all_enemies();
private:
    std::vector<Enemy*>enemies;
    void delete_index(int index);
    void damage_missiles();
    std::vector<Shoot*> get_missiles();
    std::vector<Enemy*> find_enemies_in_radius(int input_x, int input_y, int input_radius);
    void damage_missiles_enemies(std::vector<Enemy*> input_enemies, Shoot* input_glue);
    void damage_glues();
    std::vector<Shoot*> get_glues();
    void damage_glues_enemies(std::vector<Enemy*> input_enemies, Shoot* input_glue);
};
#endif
