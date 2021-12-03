#ifndef ICONS
#include "RSDL-master/src/rsdl.hpp"
#define ICONS "icons"
class GameIcon
{
public:
    Rectangle get_rectangle();
    double find_distance(double input_x, double input_y);
protected:
    double x_coordinate;
    double y_coordinate;
    int get_angle(double x_enemy, double y_enemy);
    int get_angle_triangle_circle(double x_in_triangle_circle, double y_in_triangle_circle);
    int correct_angle_area(int angle,double x_in_triangle_circle, double y_in_triangle_circle);
};
#endif
