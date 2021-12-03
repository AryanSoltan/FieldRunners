#include "Wave.hpp"
#include "Enemy.hpp"
#include "SuperTrooper.hpp"
#include "Runner.hpp"
#include "StubbornRunner.hpp"
#include "Scrambler.hpp"
#include "EnemyTable.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include<sstream>
#include<string>
#include <time.h>
#include<vector>

using namespace std;

#define STATE_WAIT_FOR_NEW_WAVE 0
#define WAVE_GO_ON 1
#define HAVE_NO_VALUE 0
#define RUNNER_TYPE 0
#define STUBBORNRUNNER_TYPE 1
#define SUPERTROOPER_TYPE 2
#define SCRAMBLER_TYPE 3
#define Y_FIRST 160
#define PASS_TIME 15
#define TIME_BETWENN_WAVE 3000
#define TIME_BETWEEN_SEND 500
#define NUMBER_DIFFRENT_ENEMY 4
#define SQUERE_DISTANCE 60
#define X_FIRST 120
#define SQUARE_LENGTH 60
#define IMAGE_PATH "./Assets/Icons/walk_path.png"
#define DELIMITER '\n'


Point point_to_pixel(double x,double y)
{
    double x_corner = (x)*SQUARE_LENGTH + X_FIRST;
    double y_corner = (y)*SQUARE_LENGTH + Y_FIRST;
    return Point(x_corner,y_corner);
}
void Wave::update(int time)
{
    if(state == STATE_WAIT_FOR_NEW_WAVE)
    {
        update_wait(time);
    }
    if(state == WAVE_GO_ON)
    {
        update_wave_now(time);
    }
}
void Wave::update_wait(int time)
{
    time_pass_last_wave += time;
    if(time_pass_last_wave >= TIME_BETWENN_WAVE)
    {
        int time_run= time_pass_last_wave - TIME_BETWENN_WAVE;
        go_to_new_wave();
        update_wave_now(time_run);
    }
}
void Wave::go_to_new_wave()
{
    number_wave ++;
    state = WAVE_GO_ON;
    time_wave_run = 0;
    for(int i = 0; i < number_each_enemy.size(); i++)
    {
        number_each_enemy[i] = 0;
    }
    enemies.clear_all();
}
void Wave::update_wave_now(int time)
{
    enemies.update(time);
    enemies.delete_all_shoots_reach();
    if(time_wave_run == 0)
    {
        if(number_wave == 1)
            read_path_enemy();
        read_number_each();
    }
    time_wave_run += time;
    if(can_send_enemy())
    {
        add_random_enemy();
    }
    if(enemies.is_empty() == 1 && !get_enemy_line_remain())
    {
        go_to_wait();
    }
}
void Wave::go_to_wait()
{
    state = STATE_WAIT_FOR_NEW_WAVE;
    time_pass_last_wave = 0;
}
void Wave::read_number_each()
{
    for(int i = 0 ; i < number_each_enemy.size(); i++)
    {
        cin >> number_each_enemy[i];
    }
}
Wave::Wave(int input_number_wave)
{
    number_wave = input_number_wave;
    state = WAVE_GO_ON;
    time_pass_last_wave = HAVE_NO_VALUE;
    time_wave_run = 0;
    for(int i = 0; i < NUMBER_DIFFRENT_ENEMY; i++)
    {
        number_each_enemy.push_back(0);
    }
}
void Wave::draw(Window* game_window)
{
    enemies.draw(game_window);
    draw_level(game_window);
    draw_path(game_window);
}
int Wave::get_enemy_line_remain()
{
    int number_all_enemies = 0;
    for(int i = 0; i < number_each_enemy.size(); i++)
    {
        //cout << number_each_enemy[i] << endl;
        number_all_enemies += (number_each_enemy[i] != 0);
    }
    return number_all_enemies;
}
bool Wave::can_send_enemy()
{
    if(!get_enemy_line_remain())
        return false;
    if(time_wave_run % TIME_BETWEEN_SEND < PASS_TIME)
        return true;
    return false;
}
void Wave::add_random_enemy()
{
    int number_remain = get_enemy_line_remain();
    int seed = time(0);
    srand(seed);
    int random_enemy_type = (rand() % number_remain) ;
    get_remain_enemy(random_enemy_type);
}
void Wave::get_remain_enemy(int index_enemy)
{
    int counter = 0;
    for(int i = 0 ; i < number_each_enemy.size(); i++)
    {
        if(number_each_enemy[i] && counter == index_enemy)
        {
            number_each_enemy[i]--;
            add_enemy(i);
            return;
        }
        if(number_each_enemy[i])
            counter++;
    }
}
void Wave::add_enemy(int index)
{
    Enemy* answer;
    if(index == RUNNER_TYPE)
        answer = new Runner(path,number_wave);
    if(index == STUBBORNRUNNER_TYPE)
        answer = new StubbornRunner(path,number_wave);
    if(index == SUPERTROOPER_TYPE)
        answer = new SuperTrooper(path,number_wave);
    if(index == SCRAMBLER_TYPE)
        answer = new Scrambler(path,number_wave);
    enemies.add(answer);
}
void Wave::read_path_enemy()
{
    string line_wave;
    getline(cin,line_wave,DELIMITER);
    stringstream line_stream;
    line_stream << line_wave;
    int row_enemy,column_enemy;
    while(line_stream >> row_enemy)
    {
        line_stream >> column_enemy;
        path.push_back(point_to_pixel((double)row_enemy,(double)column_enemy));
    }
}
Enemy* Wave::find_nearest(double input_x,double input_y)
{
    return enemies.find_nearest(input_x, input_y);
}
string int_to_string(int input_number)
{
    stringstream stream_change_str_int;
    stream_change_str_int << input_number;
    string answer = stream_change_str_int.str();
    return answer;
}
void Wave::draw_level(Window* game_window)
{
    string level_now = "Level ";
    string number_wave_str = int_to_string(number_wave);
    level_now.append(number_wave_str);
    game_window->show_text(level_now, Point(600,50), WHITE, "./Assets/OpenSans.ttf",30);
}
bool Wave::is_waves_finished()
{
    //cout << state << " " << time_pass_last_wave << endl;
    if(cin.eof() && enemies.is_empty())
    {
        return true;
    }
    return false;
}
int Wave::get_damage_to_user()
{
    int damage_to_user = enemies.get_damage_from_enemies();
    return damage_to_user;
}
int Wave::get_coins_user()
{
    int coins_to_user = enemies.get_coins_from_kill();
    return coins_to_user;
}
void Wave::delete_finished()
{
    enemies.delete_finished_enemies();
}
void Wave::draw_path(Window* game_window)
{
    for(int i = 0; i < (int)path.size() - 1; i++)
    {
        int change_x = 0;
        int change_y = 0;
        if(path[i].x < path[i+1].x)
            change_x = 1;
        else if(path[i].x > path[i+1].x)
            change_x = -1;
        else if(path[i].y < path[i+1].y)
            change_y = 1;
        else
            change_y = -1;
        Point now = path[i];
        while(now.x != path[i+1].x || now.y != path[i+1].y)
        {
            game_window->fill_circle(Point(now.x + 30,now.y + 40),3, RGB(0,102,0));
            now.x += change_x * SQUERE_DISTANCE;
            now.y += change_y * SQUERE_DISTANCE;
        }
    }
}
void Wave::delete_all()
{
    enemies.delete_all_enemies();
}
bool Wave::is_in_path(int input_x, int input_y)
{
    for(int i = 0; i < (int)path.size() - 1; i++)
    {
        int change_x = 0;
        int change_y = 0;
        if(path[i].x < path[i+1].x)
            change_x = 1;
        else if(path[i].x > path[i+1].x)
            change_x = -1;
        else if(path[i].y < path[i+1].y)
            change_y = 1;
        else
            change_y = -1;
        Point now = path[i];
        while(now.x != path[i+1].x || now.y != path[i+1].y)
        {
            now.x += change_x * SQUARE_LENGTH;
            now.y += change_y * SQUARE_LENGTH;
            if(now.x == input_x && now.y == input_y)
            {
                return true;
            }
        }
    }
    return false;
}
