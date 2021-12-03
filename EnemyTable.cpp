#include "EnemyTable.hpp"
#include "Enemy.hpp"
#include<vector>
#include "RSDL-master/src/rsdl.hpp"
#include "Shoot.hpp"

#define SCRAMBLER_IMAGE "./Assets/enemies/scrambler.png"

using namespace std;

void EnemyTable::add(Enemy* new_enemy)
{
    enemies.push_back(new_enemy);
}
void EnemyTable::clear_all()
{
    enemies.clear();
}
bool EnemyTable::is_empty()
{
    if(enemies.size() == 0)
        return true;
    else
        return false;
}
void EnemyTable::update(double time)
{
    for(int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->walk(time);
        enemies[i]->update_shoots(time);
    }
    damage_missiles();
    damage_glues();
}
int EnemyTable::get_size()
{
    return enemies.size();
}
void EnemyTable::draw(Window* game_window)
{
    for(int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->draw(game_window);
    }
}
void EnemyTable::delete_index(int index)
{
    Enemy* must_delete = enemies[index];
    for(int i = index ; i < enemies.size(); i++)
    {
        enemies[i] = enemies[i+1];
    }
    must_delete->delete_all();
    delete must_delete;
    enemies.pop_back();
}
void EnemyTable::delete_finished_enemies()
{
    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies[i]->is_finish())
            delete_index(i);
    }
}
Enemy* EnemyTable::find_nearest(double input_x, double input_y)
{
    if(enemies.size() == 0)
        return NULL;
    Enemy* answer;
    double minimum_distance = 0;
    for(int i = 0; i < enemies.size(); i++)
    {
        double distance_now = enemies[i]->find_distance(input_x, input_y);
        if(i == 0 || distance_now < minimum_distance)
        {
            minimum_distance = distance_now;
            answer = enemies[i];
        }
    }
    return answer;
}
int EnemyTable::get_coins_from_kill()
{
    int coins_from_kills = 0;
    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies[i]->is_killed())
        {
            coins_from_kills += enemies[i]->get_coins_from_kill();
        }
    }
    return coins_from_kills;
}
int EnemyTable::get_damage_from_enemies()
{
    int damage_enemies = 0;
    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies[i]->is_finish_path())
        {
            damage_enemies += enemies[i]->get_damage_user();
        }
    }
    return damage_enemies;
}
void EnemyTable::damage_missiles()
{
    vector<Shoot*> all_missiles = get_missiles();
    for(int i = 0; i < all_missiles.size(); i++)
    {
        vector<Enemy*>must_damage_enemies = find_enemies_in_radius(all_missiles[i]->get_x(), all_missiles[i]->get_y(), all_missiles[i]->get_radius());
        //cout << all_missiles[i]->get_radius() << endl;
        damage_missiles_enemies(must_damage_enemies, all_missiles[i]);
    }
}
vector<Shoot*>EnemyTable::get_missiles()
{
    vector<Shoot*>answer;
    for(int i = 0; i < enemies.size(); i++)
    {
        vector<Shoot*>missiles_enemy = enemies[i]->get_missiles();
        for(int j = 0; j < missiles_enemy.size(); j++)
        {
            answer.push_back(missiles_enemy[j]);
        }
    }
    return answer;
}
vector<Enemy*> EnemyTable::find_enemies_in_radius(int input_x, int input_y, int input_radius)
{
    //cout << input_radius << endl;
    vector<Enemy*> answer;
    for(int i = 0; i < enemies.size(); i++)
    {
        double distance = enemies[i]->find_distance(input_x, input_y);
        if(distance <= input_radius)
        {
            answer.push_back(enemies[i]);
        }
    }
    return answer;
}
void EnemyTable::damage_missiles_enemies(vector<Enemy*> input_enemies, Shoot* input_missile)
{
    for(int i = 0; i < input_enemies.size(); i++)
    {
        input_enemies[i]->damage_heart(input_missile->get_damage());
    }
}
void EnemyTable::delete_all_shoots_reach()
{
    for(int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->delete_shoots();
    }
}
void EnemyTable::damage_glues()
{
    vector<Shoot*>all_glues = get_glues();
    for(int i = 0; i < all_glues.size(); i++)
    {
        vector<Enemy*>must_damage_enemies = find_enemies_in_radius(all_glues[i]->get_x(), all_glues[i]->get_y(), all_glues[i]->get_radius());
        damage_glues_enemies(must_damage_enemies, all_glues[i]);
    }
}
vector<Shoot*> EnemyTable::get_glues()
{
    vector<Shoot*>answer;
    for(int i = 0; i < enemies.size(); i++)
    {
        vector<Shoot*>glues_enemy = enemies[i]->get_glues();
        for(int j = 0; j < glues_enemy.size(); j++)
        {
            answer.push_back(glues_enemy[j]);
        }
    }
    return answer;
}
void EnemyTable::damage_glues_enemies(vector<Enemy*> input_enemies, Shoot* input_glue)
{
    for(int i = 0; i < input_enemies.size(); i++)
    {
        input_enemies[i]->damage_glue(input_glue->get_time_effect(),input_glue->get_damage());
    }
}
void EnemyTable::delete_all_enemies()
{
    for(int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->delete_all();
        delete enemies[i];
    }
    enemies.clear();
}
