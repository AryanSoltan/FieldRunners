#include "Enemy.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include "GameIcons.hpp"
#include<string>
#include "Shoot.hpp"

#define MILLI_TO_SECOND 1/1000
#define HAS_PASS 1
#define NOT_PASS 0
#define X_FIRST 120
#define Y_FIRST 160
#define X_LAST 1200
#define Y_LAST 760
#define SQUARE_LENGTH 60
#define IMAGE_FORMAT ".png"

using namespace std;

void Enemy::walk(double time)
{
    if(path[0].x != x_coordinate)
    {
        if(walk_x(time) == HAS_PASS)
        {
            x_coordinate = path[0].x;
            del_one_pixel();
        }
    }
    else
    {
        if(walk_y(time) == HAS_PASS)
        {
            y_coordinate = path[0].y;
            del_one_pixel();
        }
    }
}
bool Enemy::walk_x(double time)
{
    bool has_pass = 0;
    if(x_coordinate < path[0].x)
    {
        x_coordinate += (double)velocity * (double)MILLI_TO_SECOND * time;
        //cout << coordinate.x << " " <<  velocity * (double)MILLI_TO_SECOND * time << endl;
        if(x_coordinate >= path[0].x)
            has_pass = 1;
    }
    else
    {
        x_coordinate -= velocity * (double)MILLI_TO_SECOND * time;
        if(x_coordinate <= path[0].x)
            has_pass = 1;
    }
    if(has_pass)
    {
        return HAS_PASS;
    }
    return NOT_PASS;
}
bool Enemy::walk_y(double time)
{
    bool has_pass = 0;
    if(y_coordinate < path[0].y)
    {
        y_coordinate += velocity * (double)MILLI_TO_SECOND * time;
        if(y_coordinate >= path[0].y)
            has_pass = 1;
    }
    else
    {
        y_coordinate -= velocity * (double)MILLI_TO_SECOND * time;
        if(y_coordinate <= path[0].y)
            has_pass = 1;
    }
    if(has_pass)
    {
        return HAS_PASS;
    }
    return NOT_PASS;
}
void Enemy::del_one_pixel()
{
    for(int i = 0 ; i < (int)path.size() - 1; i++)
    {
        path[i] = path[i+1];
    }
    path.pop_back();
}
bool Enemy::is_finish()
{
    if(path.size() == 0 || health <= 0)
        return true;
    return false;
}
void Enemy::draw_health_line(Window* game_window)
{
    double ratio = (double)health/(double)start_health;
    double double_green_x = ratio * (double) 60 + x_coordinate;
    int green_x = (int)double_green_x;
    Rectangle health_line_green(Point(x_coordinate,y_coordinate-12),Point(green_x,y_coordinate -5));
    Rectangle health_line_red(Point(green_x,y_coordinate - 12), Point(x_coordinate + 60,y_coordinate -5));
    game_window->fill_rect(health_line_green,RGB(0,190,0));
    game_window->fill_rect(health_line_red,RGB(190,0,0));
}
string Enemy::get_path_folder(string folder_name,int time_change_image,int number_images)
{
    string path_folder = folder_name;
    int image_number = ((number_state % time_change_image) / (time_change_image/number_images));
    image_number++;
    path_folder.push_back(char(image_number + '0'));
    path_folder += IMAGE_FORMAT;
    return path_folder;
}
int Enemy::get_x()
{
    return x_coordinate;
}
int Enemy::get_y()
{
    return y_coordinate;
}
void Enemy::damage_heart(int damage)
{
    health -= damage;
}
void Enemy::add_shoot(Shoot* new_shoot)
{
    shoots.push_back(new_shoot);
}
void Enemy::delete_shoot(int index)
{
    delete shoots[index];
}
void Enemy::update_shoots(int time)
{
    update_effected_glues(time);
    for(int i = 0; i < shoots.size(); i++)
    {
        shoots[i]->update(time);
        shoots[i]->walk(time, x_coordinate, y_coordinate);
        int angle_shoot = get_angle(shoots[i]->get_x(), shoots[i]->get_y());
        if(shoots[i]->is_reach_destination())
        {
            if(!shoots[i]->is_missile() && !shoots[i]->is_glue())
                damage_heart(shoots[i]->get_damage());
        }
    }
}
void Enemy::draw_shoots(Window* game_window)
{
    for(int i = 0; i < shoots.size(); i++)
    {
        int angle_shoot = get_angle(shoots[i]->get_x(), shoots[i]->get_y());
        shoots[i]->draw(game_window,angle_shoot);
    }
}
bool Enemy::is_killed()
{
    return health<=0;
}
bool Enemy::is_finish_path()
{
    if(path.size() == 0)
        return true;
    return false;
}
int Enemy::get_coins_from_kill(){return money_earn_from_kill;}
int Enemy::get_damage_user(){return health_damage;}
vector<Shoot*> Enemy::get_missiles()
{
    vector<Shoot*>answer;
    for(int i = 0; i < shoots.size(); i++)
    {
        if(shoots[i]->is_missile() && shoots[i]->is_reach_destination())
        {
            answer.push_back(shoots[i]);
        }
    }
    return answer;
}
void Enemy::delete_shoots()
{
    vector<Shoot*>remain_shoots;
    for(int i = 0; i < shoots.size(); i++)
    {
        if(shoots[i]->is_reach_destination())
        {
            delete_shoot(i);
        }
        else
            remain_shoots.push_back(shoots[i]);
    }
    shoots.clear();
    for(int i = 0; i < remain_shoots.size(); i++)
    {
        shoots.push_back(remain_shoots[i]);
    }
}
vector<Shoot*> Enemy::get_glues()
{
    vector<Shoot*>answer;
    for(int i = 0; i < shoots.size(); i++)
    {
        if(shoots[i]->is_glue() && shoots[i]->is_reach_destination())
        {
            answer.push_back(shoots[i]);
        }
    }
    return answer;
}
void Enemy::damage_glue(int time_effect,int damage_input)
{
    glues_time.push_back(make_pair(time_effect, damage_input));
    double ratio = (double)damage_input / (double) 100;
    velocity = ratio * (double)velocity;
}
void Enemy::delete_finished_glues()
{
    vector<pair<int,int> > remain_glues;
    for(int i = 0; i < glues_time.size(); i++)
    {
        if(glues_time[i].first <= 0)
        {
            double ratio = (double)100 / (double)glues_time[i].second;
            velocity = (double)velocity * ratio;
        }
        else
        {
            remain_glues.push_back(glues_time[i]);
        }
    }
    glues_time.clear();
    for(int i = 0; i < remain_glues.size(); i++)
    {
        glues_time.push_back(remain_glues[i]);
    }
}
void Enemy::update_effected_glues(int time)
{
    for(int i = 0; i < glues_time.size(); i++)
    {
        glues_time[i].first -= time;
    }
    delete_finished_glues();
}
void Enemy::delete_all()
{
    for(int i = 0; i < shoots.size(); i++)
    {
        delete shoots[i];
    }
}
