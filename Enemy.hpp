#ifndef ENEMY
#define ENEMY "enemy"

#include <vector>
#include "RSDL-master/src/rsdl.hpp"
#include "GameIcons.hpp"
#include<string>
#include "Shoot.hpp"

Point point_to_pixel(double x,double y);
class Enemy : public GameIcon
{
public:
    void walk(double time);
    bool walk_x(double time);
    bool walk_y(double time);
    void del_one_pixel();
    virtual void draw(Window* game_window) = 0;
    bool is_finish();
    int get_x();
    int get_y();
    void damage_heart(int damge);
    void add_shoot(Shoot* new_shoot);
    void update_shoots(int time);
    bool is_killed();
    bool is_finish_path();
    int get_coins_from_kill();
    int get_damage_user();
    std::vector<Shoot*> get_missiles();
    std::vector<Shoot*> get_glues();
    void delete_shoots();
    void damage_glue(int time_effect, int damage_input);
    void delete_all();
protected:
    double health;
    int velocity;
    int health_damage;
    int money_earn_from_kill;
    std::vector<Point>path;
    void draw_health_line(Window* game_window);
    int number_state;
    int start_health;
    std::vector<Shoot*>shoots;
    std::vector< std::pair<int,int > >glues_time;

    void delete_shoot(int index);
    std::string get_path_folder(std::string folder_name,int time_change_image,int number_images);
    void draw_shoots(Window* game_window);
    void update_effected_glues(int time);
    void delete_finished_glues();
};
#endif
