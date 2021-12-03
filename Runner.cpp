#include "Runner.hpp"
#include "SuperTrooper.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include "Enemy.hpp"
#include<string>

#define START_HEALTH 250
#define START_VELOCITY 50
#define DAMAGE_TO_USER 1
#define COIN_FROM_DEATH 6

#define RUNNER_DOWN_FOLDER "./Assets/enemies/runner_down/"
#define TIME_CHANGE_IMAGE_DOWN 50
#define NUMBER_IMAGES_DOWN 5

#define RUNNER_RIGHT_FOLDER "./Assets/enemies/runner_right/"
#define TIME_CHANGE_IMAGE_RIGHT 50
#define NUMBER_IMAGES_RIGHT 5

#define TIME_CHANGE_IMAGE_UP 40
#define NUMBER_IMAGES_UP 4
#define RUNNER_UP_FOLDER "./Assets/enemies/runner_up/"

using namespace std;

Runner::Runner(vector<Point>path_,int number_wave)
{
    number_state = 1;
    health = ((double)0.9 + (double)0.1 * (double)number_wave) * (double)START_HEALTH;
    velocity = START_VELOCITY;
    health_damage = ((double)number_wave*0.1+0.9)*(double)DAMAGE_TO_USER;
    money_earn_from_kill = COIN_FROM_DEATH;
    x_coordinate = path_[0].x;
    y_coordinate = path_[0].y;
    path = path_;
    for(int i = 0; i < (int)path.size()-1; i++)
    {
        path[i] = path[i+1];
    }
    path.pop_back();
    start_health = START_HEALTH;
}
void Runner::draw(Window* game_window)
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
void Runner::draw_right(Window* game_window)
{
    int change_image_right = (int)((double)TIME_CHANGE_IMAGE_RIGHT * (START_VELOCITY / (double)velocity));
    string path_folder = get_path_folder(RUNNER_RIGHT_FOLDER,change_image_right,NUMBER_IMAGES_RIGHT);
    game_window->draw_img(path_folder,get_rectangle());
}
void Runner::draw_up(Window* game_window)
{
    int change_image_up = (double)TIME_CHANGE_IMAGE_UP * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(RUNNER_UP_FOLDER,change_image_up,NUMBER_IMAGES_UP);
    game_window->draw_img(path_folder,get_rectangle());
}
void Runner::draw_down(Window* game_window)
{
    int change_image_down = (double)TIME_CHANGE_IMAGE_DOWN * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(RUNNER_DOWN_FOLDER,change_image_down,NUMBER_IMAGES_DOWN);
    game_window->draw_img(path_folder,get_rectangle());
}
void Runner::draw_left(Window* game_window)
{
    int change_image_right = (double)TIME_CHANGE_IMAGE_RIGHT * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(RUNNER_RIGHT_FOLDER,change_image_right,NUMBER_IMAGES_RIGHT);
    game_window->draw_img(path_folder,get_rectangle(),NULL_RECT,180,false,true);
}
