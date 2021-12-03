#ifndef SUPERTROOPER
#define SUPERTROOPER "supertrooper"

#include "Enemy.hpp"
#include "GameIcons.hpp"
#include<vector>
class SuperTrooper : public Enemy
{
public:
    SuperTrooper(std::vector<Point>path_,int number_wave);
    virtual void draw(Window* game);
private:
    void draw_right(Window* game_window);
    void draw_down(Window* game_window);
    void draw_up(Window* game_window);
    void draw_left(Window* game_window);
};
#endif
