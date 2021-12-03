#include "SuperTrooper.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include "Enemy.hpp"

#define START_HEALTH 500
#define START_VELOCITY 25
#define COIN_FROM_DEATH 8
#define DAMAGE_TO_USER 4

#define HEAVY_RUNNER_DOWN_FOLDER "./Assets/enemies/heavy-runner-down/"
#define HEAVY_TIME_CHANGE_IMAGE_DOWN 90
#define HEAVY_NUMBER_IMAGES_DOWN 3

#define HEAVY_RUNNER_RIGHT_FOLDER "./Assets/enemies/heavy-runner-right/"
#define HEAVY_TIME_CHANGE_IMAGE_RIGHT 80
#define HEAVY_NUMBER_IMAGES_RIGHT 5

#define HEAVY_TIME_CHANGE_IMAGE_UP 80
#define HEAVY_NUMBER_IMAGES_UP 5
#define HEAVY_RUNNER_UP_FOLDER "./Assets/enemies/heavy-runner-up/"

using namespace std;

SuperTrooper::SuperTrooper(vector<Point>path_,int number_wave)
{
    health = ((double)0.9 + (double)0.1 * (double)number_wave) * (double)START_HEALTH;
    velocity = START_VELOCITY;
    health_damage = ((double)number_wave*0.1+0.9)*(double)DAMAGE_TO_USER;
    money_earn_from_kill = COIN_FROM_DEATH;
    x_coordinate = path_[0].x;
    y_coordinate = path_[0].y;
    path = path_;
    number_state = 1;
    for(int i = 0; i < (int)path.size()-1; i++)
    {
        path[i] = path[i+1];
    }
    path.pop_back();
    start_health = START_HEALTH;
}
void SuperTrooper::draw(Window* game_window)
{
    if(!path.size())
        return;
    if(y_coordinate == path[0].y){
        if(x_coordinate <= path[0].x)
        {
            draw_right(game_window);
        }
        else
        {
            draw_left(game_window);
        }
    }
    else
    {
        if(y_coordinate < path[0].y)
        {
           draw_down(game_window);
        }
        else
        {
            draw_up(game_window);
        }
    }
    draw_shoots(game_window);
    number_state++;
    draw_health_line(game_window);
}
void SuperTrooper::draw_right(Window* game_window)
{
    int change_image_right = (double)HEAVY_TIME_CHANGE_IMAGE_RIGHT * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(HEAVY_RUNNER_RIGHT_FOLDER,change_image_right,HEAVY_NUMBER_IMAGES_RIGHT);
    game_window->draw_img(path_folder,get_rectangle());
}
void SuperTrooper::draw_left(Window* game_window)
{
    int change_image_right = (double)HEAVY_TIME_CHANGE_IMAGE_RIGHT * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(HEAVY_RUNNER_RIGHT_FOLDER,change_image_right,HEAVY_NUMBER_IMAGES_RIGHT);
    game_window->draw_img(path_folder,get_rectangle(),NULL_RECT,180,false,true);
}
void SuperTrooper::draw_down(Window* game_window)
{
    int change_image_down = (double)HEAVY_TIME_CHANGE_IMAGE_DOWN * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(HEAVY_RUNNER_DOWN_FOLDER,change_image_down,HEAVY_NUMBER_IMAGES_DOWN);
    game_window->draw_img(path_folder,get_rectangle());
}
void SuperTrooper::draw_up(Window* game_window)
{
    int change_image_up = (double)HEAVY_TIME_CHANGE_IMAGE_UP * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(HEAVY_RUNNER_UP_FOLDER,change_image_up,HEAVY_NUMBER_IMAGES_UP);
    game_window->draw_img(path_folder,get_rectangle());
}
