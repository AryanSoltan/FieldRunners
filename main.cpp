#include<iostream>
#include "RSDL-master/src/rsdl.hpp"
#include "FieldRunners.hpp"
#include "Wave.hpp"
#include "User.hpp"

#define START_HEALTH 20
#define START_COIN 200

int main()
{
    Window* game_window = new Window(1365,1024,"FieldRunners");
    Wave* wave = new Wave(1);
    User* user = new User(START_COIN, START_HEALTH);
    FieldRunners field_runners(game_window,wave,user);
    field_runners.run_game();
    delete game_window;
    delete user;
    delete wave;
}
