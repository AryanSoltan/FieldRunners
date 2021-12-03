#ifndef SCRAMBLER
#define SCRAMBLER "scrambler"

#include "Enemy.hpp"
#include "GameIcons.hpp"
#include<vector>
class Scrambler : public Enemy
{
public:
    Scrambler(std::vector<Point>path_,int number_wave);
    virtual void draw(Window* game);
private:
};
#endif
