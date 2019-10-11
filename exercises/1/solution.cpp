
class Point
{
private:
    int x, y;
    int square(int number)
    {
        return number * number;
    }

public:
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int getDistance(Point p2)
    {
        return sqrt(square(p2.x - this->x) + square(p2.y - this->y));
    }
};
