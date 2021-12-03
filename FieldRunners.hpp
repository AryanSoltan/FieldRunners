#ifndef FIELDRUNNERS
#define FIELDRUNNERS "fieldrun"

#include "RSDL-master/src/rsdl.hpp"
#include<vector>
#include "Enemy.hpp"
#include "EnemyTable.hpp"
#include "Wave.hpp"
#include "User.hpp"

class FieldRunners
{
public:
    void run_game();
    FieldRunners(Window* game_window, Wave* input_wave, User* input_user);
private:
    Window* game_window;
    Wave* wave;
    User* user;

    void run_new_event();
    void read_path_enemy();
    void draw_field();
    bool is_game_finished();
    void finish_the_game(Window* game_window);
    void draw_win_screen(Window* game_window);
    bool is_player_exit(Window* game_window);
    void draw_loose_screen(Window* game_window);
};
#endif
