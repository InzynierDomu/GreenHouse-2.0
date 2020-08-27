struct Linear_function
{
  //y = ax + b
  double a;
  double b; 
};

struct Point
{
  Point(int _y, int _x):y(_y), x(_x){};
  int y;
  int x;
};

Linear_function calculate(Point first, Point second)
{
  Linear_function f;
  f.a = (second.y - first.y)/(double)(second.x - first.x);
  f.b = first.y - (f.a * first.x);
  return f;
}

double find_y(int x, Linear_function f)
{
  return(f.a * x + f.b);
}