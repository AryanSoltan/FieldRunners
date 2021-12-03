#ifndef RUNNER
#define RUNNER "runner"
#include "Enemy.hpp"
#include "GameIcons.hpp"
class Runner : public Enemy
{
public:
    Runner(std::vector<Point>path_,int wave);
    virtual void draw(Window* game);
private:
    void draw_right(Window* game_window);
    void draw_down(Window* game_window);
    void draw_up(Window* game_window);
    void draw_left(Window* game_window);
};
#endif
