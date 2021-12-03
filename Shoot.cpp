#include "RSDL-master/src/rsdl.hpp"
#include "Shoot.hpp"
#include "GameIcons.hpp"

#define GATTLING_FIRE_IMAGE "./Assets/shoots/gattling_fire.png"
#define TESLA_FIRE_IMAGE "./Assets/shoots/tesla_fire.png"
#define MISSILE_FIRE_IMAGE  "./Assets/shoots/missile_fire.png"
#define GLUE_FIRE_IMAGE  "./Assets/shoots/glue_fire.png"

#define GATTLING_CODE 1
#define TESLA_CODE 3
#define GLUE_CODE 4
#define MISSILE_CODE 2
using namespace std;

Shoot::Shoot(double input_x_start, double input_y_start, int input_time_to_reach, int input_damage,int input_type,int input_radius,int input_level)
{
    x_coordinate = input_x_start;
    y_coordinate = input_y_start;
    x_start = input_x_start;
    y_start = input_y_start;
    time_to_reach = input_time_to_reach;
    damage = input_damage;
    time_pass = 0;
    type = input_type;
    radius = input_radius;
    level = input_level;
}
void Shoot::draw(Window* game_window,int angle)
{
    if(type == GATTLING_CODE)
        game_window->draw_img(GATTLING_FIRE_IMAGE,get_rectangle(),NULL_RECT,150 - angle);
    if(type == TESLA_CODE)
        game_window->draw_img(TESLA_FIRE_IMAGE,get_rectangle(),NULL_RECT,100 - angle);
    if(type == MISSILE_CODE)
        game_window->draw_img(MISSILE_FIRE_IMAGE,Rectangle(Point(x_coordinate, y_coordinate),Point(x_coordinate + 40, y_coordinate + 40)),NULL_RECT,210 - angle);
    if(type == GLUE_CODE){
        game_window->draw_img(GLUE_FIRE_IMAGE,Rectangle(Point(x_coordinate, y_coordinate),Point(x_coordinate + 40, y_coordinate + 40)),NULL_RECT,-90 - angle);
    }
}
void Shoot::update(int time)
{
    time_pass += time;
}
void Shoot::walk(int time, double destination_x, double destination_y)
{
    double x_distance = (double)destination_x - (double)x_start;
    double y_distance = (double)destination_y - (double)y_start;
    double ratio = (double)time_pass / (double)time_to_reach;
    x_distance *= ratio;
    y_distance *= ratio;
    x_coordinate = x_distance + x_start;
    y_coordinate = y_distance + y_start;
    if(time_pass >= time_to_reach)
    {
        x_coordinate = destination_x;
        y_coordinate = destination_y;
    }
    //cout << x_coordinate << " " << y_coordinate << " " << destination_x << " " << destination_y << endl;
}
double Shoot::get_x(){return x_coordinate;}
double Shoot::get_y(){return y_coordinate;}
int Shoot::get_damage(){return damage;}
int Shoot::get_radius(){return radius;}
bool Shoot::is_reach_destination()
{
    return time_to_reach <= time_pass;
}
bool Shoot::is_missile()
{
    if(type == MISSILE_CODE)
        return true;
    return false;
}
bool Shoot::is_glue()
{
    if(type == GLUE_CODE)
        return true;
    return false;
}
int Shoot::get_time_effect()
{
    if(type == GLUE_CODE)
    {
        return 2000 + 500*level;
    }
    return 0;
}
