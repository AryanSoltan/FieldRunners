#include "User.hpp"
#include "Tower.hpp"
#include<vector>
#include "RSDL-master/src/rsdl.hpp"
#include "Wave.hpp"
#include "Gattling.hpp"
#include "Glue.hpp"
#include "Tesla.hpp"
#include "Missile.hpp"

#define CORNER_X 122
#define CORNER_Y 170
#define LENGTH_SQUERE 60
#define SQUERE_LENGTH_DRAW 65
#define DELAY_FRAME 15
#define COINS_ADRESS "./Assets/Icons/coins.png"
#define HEART_ADRESS "./Assets/Icons/heart.png"

using namespace std;

Point User::convert_pixel_to_table(Point input_point)
{
    int x_table = (input_point.x - CORNER_X) / LENGTH_SQUERE;
    int y_table = (input_point.y - CORNER_Y) / LENGTH_SQUERE;
    return Point(x_table,y_table);
}
User::User(int input_coin, int input_health)
{
    health = input_health;
    amount_coin = input_coin;
    is_playing_game = true;
}
void User::update(Window* game_window,Wave* wave)
{
    update_towers(wave);
    run_command_player(game_window,wave);
    health -= wave->get_damage_to_user();
    amount_coin += wave->get_coins_user();
}
void User::run_command_player(Window* game_window, Wave* wave)
{
    if(!game_window->has_pending_event())
    {
        return;
    }
    Event player_command = game_window->poll_for_event();
    switch(player_command.get_type()){
        case Event::EventType::QUIT:
            is_playing_game = false;
        case Event::EventType::KEY_PRESS:
            handle_press_key_user(game_window, player_command, wave);
    }
}
void User::handle_press_key_user(Window* game_window,Event player_command,Wave* wave)
{
    char pressed_key = player_command.get_pressed_key();
    Point mouse_location  = get_current_mouse_position();
    Point in_table  = convert_pixel_to_table(mouse_location);
    Point new_location = point_to_pixel(in_table.x, in_table.y);
    if(is_add_tower_command(pressed_key))
        add_tower_in_location(game_window, new_location, pressed_key, wave);
    else if(pressed_key == 'u')
        upgrade_tower_in_location(new_location);
}
void User::add_tower_in_location(Window* game_window, Point new_location, char pressed_key,Wave* wave)
{
    Tower* new_tower;
    if(pressed_key == 'g')
    {
        new_tower = new Gattling((double)new_location.x, (double)new_location.y);
    }
    if(pressed_key == 'm')
    {
        new_tower = new Missile((double)new_location.x, (double)new_location.y);
    }
    if(pressed_key == 't')
    {
        new_tower = new Tesla((double)new_location.x, (double)new_location.y);
    }
    if(pressed_key == 'l')
    {
        new_tower = new Glue((double)new_location.x, (double)new_location.y);
    }
    if(amount_coin < new_tower->get_cost() || !can_add_tower_location(new_location.x , new_location.y, wave))
    {
        delete new_tower;
    }
    else
    {
        towers.push_back(new_tower);
        amount_coin -= new_tower->get_cost();
    }
}
void User::draw(Window* game_window)
{
    for(int i = 0; i < towers.size(); i++)
    {
        towers[i]->draw(game_window);
    }
    draw_coins(game_window);
    draw_health(game_window);
    //draw_error_in_path(game_window);

}
bool User::is_user_play()
{
    return is_playing_game;
}
void User::update_towers(Wave* wave)
{
    for(int i = 0; i < towers.size(); i++)
    {
        towers[i]->update(DELAY_FRAME);
        if(towers[i]->can_shoot(wave)){
            towers[i]->attack(wave);
        }
    }
}
void User::draw_coins(Window* game_window)
{
    game_window->draw_img(COINS_ADRESS,Rectangle(Point(100,50),Point(165,115)));
    game_window->show_text(int_to_string(amount_coin),Point(170,60),WHITE,"./Assets/OpenSans.ttf",30);
}
void User::draw_health(Window* game_window)
{
    game_window->draw_img(HEART_ADRESS,Rectangle(Point(230,50),Point(295,115)));
    game_window->show_text(int_to_string(health),Point(300,60),WHITE,"./Assets/OpenSans.ttf",30);
}
bool User::is_user_loose()
{
    if(health <= 0)
    {
        return true;
    }
    return false;
}
bool User::is_add_tower_command(char pressed_key)
{
    if(pressed_key == 'g' || pressed_key == 't' || pressed_key == 'l' || pressed_key == 'm')
        return true;
    return false;
}
void User::upgrade_tower_in_location(Point location)
{
    Tower* input_tower = find_tower_in_location(location);
    if(input_tower == NULL)
        return;
    if(input_tower->can_upgrade(amount_coin))
    {
        input_tower->upgrade();
        amount_coin -= input_tower->get_cost_upgrade();
    }
}
Tower* User::find_tower_in_location(Point location)
{
    for(int i = 0; i < towers.size(); i++)
    {
        if(towers[i]->is_in_location(location))
            return towers[i];
    }
    return NULL;
}
void User::delete_all()
{
    for(int i = 0; i < towers.size(); i++)
    {
        delete towers[i];
    }
    towers.clear();
}
bool User::can_add_tower_location(int input_x, int input_y, Wave* wave)
{
    for(int i = 0; i < towers.size(); i++)
    {
        if(towers[i]->is_in_location(Point(input_x, input_y)))
            return false;
    }
    if(wave->is_in_path(input_x, input_y))
        return false;
    return true;
}
/*void User::draw_error_in_path(Window* game_window)
{
    cout << "************" << endl;
    Rectangle error_rectangle(Point(900,100),Point(1200,160));
    game_window->fill_rect(error_rectangle,BLACK);
}
*/
