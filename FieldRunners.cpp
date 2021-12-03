#include<iostream>
#include "RSDL-master/src/rsdl.hpp"
#include "FieldRunners.hpp"
#include "Enemy.hpp"
#include "EnemyTable.hpp"
#include "SuperTrooper.hpp"
#include "Runner.hpp"
#include "StubbornRunner.hpp"
#include "Scrambler.hpp"
#include "Tower.hpp"
#include "User.hpp"

#define BACKGROUND_IMAGE_PATH "./Assets/background.png"
#define RUNNER_IMAGE "./Assets/enemies/runner.png"
#define WIN_CUP_IMAGE "./Assets/Icons/trophy.png"
#define DELAY_TIME 15
#define X_FIRST 120
#define Y_FIRST 160
#define X_LAST 1200
#define Y_LAST 760
#define SQUARE_LENGTH 60
#define MUSIC_PATH "./Assets/song_fieldrunners.mp3"
#define FONT_PATH "./Assets/OpenSans.ttf"

using namespace std;

FieldRunners::FieldRunners(Window* input_game_window, Wave* input_wave, User* input_user)
{
    game_window = input_game_window;
    wave = input_wave;
    user = input_user;
}
void FieldRunners::run_game()
{
    game_window->play_music(MUSIC_PATH);
    game_window->draw_img(BACKGROUND_IMAGE_PATH);
    game_window->update_screen();
    while(!is_game_finished())
    {
        run_new_event();
        delay(DELAY_TIME);
    }
    game_window->stop_music();
    finish_the_game(game_window);
    wave->delete_all();
    user->delete_all();
}
void FieldRunners::run_new_event()
{
    game_window->clear();
    wave->update(DELAY_TIME);
    user->update(game_window,wave);
    wave->delete_finished();
    draw_field();
    game_window->update_screen();
}
void FieldRunners::draw_field()
{
    game_window->draw_img(BACKGROUND_IMAGE_PATH);
    //wave->draw_path(game_window);
    wave->draw(game_window);
    user->draw(game_window);
    //game_window->draw_img(GUTTLING_FIRE_IMAGE,Rectangle(Point(200,200),Point(265,265)));
}
bool FieldRunners::is_game_finished()
{
    if(!(user->is_user_play()) || wave->is_waves_finished() || user->is_user_loose())
        return true;
    return false;
}
void FieldRunners::finish_the_game(Window* game_window)
{
    while(!is_player_exit(game_window)){
        if(user->is_user_loose())
        {
           draw_loose_screen(game_window);
        }
        else if(wave->is_waves_finished())
        {
            game_window->clear();
            draw_win_screen(game_window);
        }
        else
            break;
        game_window->update_screen();
        delay(DELAY_TIME);
    }
}
void FieldRunners::draw_win_screen(Window* game_window)
{
    game_window->clear();
    game_window->draw_img(BACKGROUND_IMAGE_PATH);
    game_window->draw_img(WIN_CUP_IMAGE, Rectangle(Point(450,300),Point(850,700)));
    game_window->show_text("You Win", Point(470,50), WHITE,FONT_PATH ,90);
}
bool FieldRunners::is_player_exit(Window* game_window)
{
    if(!game_window->has_pending_event())
    {
        return false;
    }
    Event player_command = game_window->poll_for_event();
    switch(player_command.get_type()){
        case Event::EventType::QUIT:
            return true;
    }
    return false;
}
void FieldRunners::draw_loose_screen(Window* game_window)
{
    game_window->clear();
    game_window->draw_img(BACKGROUND_IMAGE_PATH);
    game_window->show_text("You Loose", Point(430,400), WHITE, "./Assets/OpenSans.ttf",90);
}
