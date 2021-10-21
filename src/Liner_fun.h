/**
 * @file Liner_fun.h
 * @brief Struct linear function with calculations
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 01-2021
 */

#ifndef LINER_FUN
#define LINER_FUN

struct Linear_function
{
  // y = ax + b
  double a;
  double b;
};

struct Point
{
  Point(int _y, int _x)
  : y(_y)
  , x(_x){};
  int y;
  int x;
};

Linear_function calculate(Point first, Point second)
{
  Linear_function f;
  f.a = (second.y - first.y) / (double)(second.x - first.x);
  f.b = first.y - (f.a * first.x);
  return f;
}

double find_y(int x, Linear_function f)
{
  return (f.a * x + f.b);
}

#endif // LINER_FUN