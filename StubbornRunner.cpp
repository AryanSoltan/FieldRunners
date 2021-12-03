#include "StubbornRunner.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include "Enemy.hpp"

#define START_HEALTH 400
#define START_VELOCITY 30
#define COIN_FROM_DEATH 10
#define DAMAGE_TO_USER 4
#define STUBBORN_RUNNER_IMAGE "./Assets/enemies/stubborn-runner.png"

#define STUBBORN_RUNNER_DOWN_FOLDER "./Assets/enemies/stubborn-runner-down/"
#define STUBBORN_TIME_CHANGE_IMAGE_DOWN 80
#define STUBBORN_NUMBER_IMAGES_DOWN 5

#define STUBBORN_RUNNER_RIGHT_FOLDER "./Assets/enemies/stubborn-runner-right/"
#define STUBBORN_TIME_CHANGE_IMAGE_RIGHT 90
#define STUBBORN_NUMBER_IMAGES_RIGHT 9

#define STUBBORN_TIME_CHANGE_IMAGE_UP 80
#define STUBBORN_NUMBER_IMAGES_UP 4
#define STUBBORN_RUNNER_UP_FOLDER "./Assets/enemies/stubborn-runner-up/"

using namespace std;

StubbornRunner::StubbornRunner(vector<Point>path_,int number_wave)
{
    health = ((double)0.9 + (double)0.1 * (double)number_wave) * (double)START_HEALTH;
    velocity = START_VELOCITY;
    health_damage = ((double)number_wave*0.1+0.9)*(double)DAMAGE_TO_USER;
    money_earn_from_kill = COIN_FROM_DEATH;
    x_coordinate = path_[0].x;
    y_coordinate = path_[0].y;
    number_state = 1;
    path = path_;
    for(int i = 0; i < (int)path.size()-1; i++)
    {
        path[i] = path[i+1];
    }
    path.pop_back();
    start_health = START_HEALTH;
}
void StubbornRunner::draw(Window* game_window)
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
void StubbornRunner::draw_right(Window* game_window)
{
    int change_image_right = (int)((double)STUBBORN_TIME_CHANGE_IMAGE_RIGHT * (START_VELOCITY / (double)velocity));
    string path_folder = get_path_folder(STUBBORN_RUNNER_RIGHT_FOLDER,change_image_right,STUBBORN_NUMBER_IMAGES_RIGHT);
    game_window->draw_img(path_folder,get_rectangle());
}
void StubbornRunner::draw_left(Window* game_window)
{
    int change_image_right = (double)STUBBORN_TIME_CHANGE_IMAGE_RIGHT * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(STUBBORN_RUNNER_RIGHT_FOLDER,change_image_right,STUBBORN_NUMBER_IMAGES_RIGHT);
    game_window->draw_img(path_folder,get_rectangle(),NULL_RECT,180,false,true);
}
void StubbornRunner::draw_down(Window* game_window)
{
    int change_image_down = (double)STUBBORN_TIME_CHANGE_IMAGE_DOWN * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(STUBBORN_RUNNER_DOWN_FOLDER,change_image_down,STUBBORN_NUMBER_IMAGES_DOWN);
    game_window->draw_img(path_folder,get_rectangle());
}
void StubbornRunner::draw_up(Window* game_window)
{
    int change_image_up = (double)STUBBORN_TIME_CHANGE_IMAGE_UP * (START_VELOCITY / (double)velocity);
    string path_folder = get_path_folder(STUBBORN_RUNNER_UP_FOLDER,change_image_up,STUBBORN_NUMBER_IMAGES_UP);
    game_window->draw_img(path_folder,get_rectangle());
}
