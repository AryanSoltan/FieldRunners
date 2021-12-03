#include "Scrambler.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include "Enemy.hpp"

#define START_HEALTH 100
#define START_VELOCITY 90
#define COIN_FROM_DEATH 4
#define DAMAGE_TO_USER 2
#define SCRAMBLER_RIGHT_IMAGE "./Assets/enemies/scrambler.png"
#define SCRAMBLER_DOWN_IMAGE "./Assets/enemies/down_scrambler.png"
#define SCRAMBLER_UP_IMAGE "./Assets/enemies/up_scrambler.png"

using namespace std;

Scrambler::Scrambler(vector<Point>path_,int number_wave)
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
void Scrambler::draw(Window* game_window)
{
    if(!path.size())
        return;
    if(y_coordinate == path[0].y){
        if(x_coordinate <= path[0].x)
        {
            game_window->draw_img(SCRAMBLER_RIGHT_IMAGE,get_rectangle());
        }
        else
        {
            game_window->draw_img(SCRAMBLER_RIGHT_IMAGE,get_rectangle(),NULL_RECT,180,false,true);
        }
    }
    else
    {
        if(y_coordinate < path[0].y)
        {
            game_window->draw_img(SCRAMBLER_DOWN_IMAGE,get_rectangle());
        }
        else
        {
            game_window->draw_img(SCRAMBLER_UP_IMAGE,get_rectangle());
        }
    }
    draw_shoots(game_window);
    number_state++;
    draw_health_line(game_window);
}
