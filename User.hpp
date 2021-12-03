#ifndef USER
#define USER "user"

#include <vector>
#include "User.hpp"
#include "RSDL-master/src/rsdl.hpp"
#include "Tower.hpp"

class User
{
public:
    void update(Window* game_window,Wave* wave);
    User(int input_coin, int input_health);
    bool is_user_play();
    void draw(Window* game_window);
    bool is_user_loose();
    void delete_all();
private:
    std::vector<Tower*>towers;
    int health;
    int amount_coin;
    bool is_playing_game;

    void add_tower_user(Window* game_window, Event player_command, Wave* wave);
    void run_command_player(Window* game_window, Wave* wave);
    Point convert_pixel_to_table(Point input_point);
    void add_tower_in_location(Window* game_window, Point location_tower, char pressed_key, Wave* wave);
    void update_towers(Wave* wave);
    void draw_coins(Window* game_window);
    void draw_health(Window* game_window);
    void draw_error_in_path(Window* game_window);
    void upgrade_tower_in_location(Point location);
    bool is_add_tower_command(char pressed_key);
    void handle_press_key_user(Window* game_winodw,Event player_command, Wave* wave);
    Tower* find_tower_in_location(Point location);
    bool can_add_tower_location(int input_x, int input_y, Wave* wave);
};
 #endif
