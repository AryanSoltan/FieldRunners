#ifndef WAVE
#define WAVE "wave"

#include "Enemy.hpp"
#include "EnemyTable.hpp"
#include "RSDL-master/src/rsdl.hpp"

std::string int_to_string(int input_number);
Point point_to_pixel(double x,double y);

class Wave
{
public:
    Wave(int input_number_wave);
    void update(int time);
    void draw(Window* game_window);
    Enemy* find_nearest(double input_x,double input_y);
    bool is_waves_finished();
    int get_coins_user();
    void delete_finished();
    int get_damage_to_user();
    void draw_path(Window* game_window);
    void delete_all();
    bool is_in_path(int input_x, int input_y);
private:
    int state;
    int number_wave;
    int time_wave_run;
    int time_pass_last_wave;
    std::vector<int>number_each_enemy;
    std::vector<Point> path;
    EnemyTable enemies;

    void get_remain_enemy(int index_enemy);
    void add_enemy(int index);
    void add_random_enemy();
    int get_enemy_line_remain();
    bool can_send_enemy();
    void go_to_new_wave();
    void read_path_enemy();
    void update_wave_now(int time);
    void go_to_wait();
    void draw_level(Window* game_window);
    void update_wait(int time);
    void read_number_each();
};
#endif
