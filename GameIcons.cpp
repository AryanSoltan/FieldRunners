#include "GameIcons.hpp"
#include "RSDL-master/src/rsdl.hpp"
using namespace std;

#define CORNER_X 90
#define CORNER_Y 130
#define LENGTH_SQUERE 60
#define SQUERE_LENGTH_DRAW 65
#define PI 3.141596

Rectangle GameIcon::get_rectangle()
{
    return Rectangle(Point(x_coordinate,y_coordinate),Point(x_coordinate + SQUERE_LENGTH_DRAW, y_coordinate + SQUERE_LENGTH_DRAW));
}
double GameIcon::find_distance(double input_x, double input_y)
{
    double distance_x = x_coordinate - input_x;
    double distance_y = y_coordinate - input_y;
    double answer = sqrt(distance_x * distance_x + distance_y * distance_y);
    return answer;
}
int GameIcon::correct_angle_area(int angle,double x_in_triangle_circle, double y_in_triangle_circle)
{
    if(x_in_triangle_circle < 0)
    {
        if(y_in_triangle_circle < 0)
            angle = 180 + angle;
        else
            angle = 180 - angle;
    }
    else
    {
        if(y_in_triangle_circle < 0)
            angle = -angle;
    }
    return angle;
}
int GameIcon::get_angle_triangle_circle(double x_in_triangle_circle, double y_in_triangle_circle)
{
    double abs_input_y = y_in_triangle_circle;
    if(y_in_triangle_circle < 0)
        abs_input_y *= -1;
    double y_power_three = abs_input_y * abs_input_y * abs_input_y;
    double arcsin_y = abs_input_y + ((1/(double)6) * y_power_three);
    double angle_double = 180 * (arcsin_y / (double) PI);
    int new_angle = int(angle_double);
    new_angle = correct_angle_area(new_angle,x_in_triangle_circle, y_in_triangle_circle);
    return new_angle;
}
int GameIcon::get_angle(double x_enemy, double y_enemy)
{
    double x_distance = x_enemy - x_coordinate;
    double y_distance = y_coordinate - y_enemy;
    if(x_distance == 0 && y_distance == 0)
        return 0;
    double chord = sqrt(x_distance * x_distance + y_distance * y_distance);
    double x_in_triangle_circle = x_distance / chord;
    double y_in_triangle_circle = y_distance / chord;
    int angle = get_angle_triangle_circle(x_in_triangle_circle, y_in_triangle_circle);
    return angle;
}
