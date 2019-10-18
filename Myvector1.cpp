#include <iostream>
#include <cstdlib>
#include <cmath>

struct Vector2f
{
    float x = 0;
    float y = 0;

    Vector2f operator*(float a)
    {
        return Vector2f(this->x * a, this->y * a);
    }

    Vector2f operator/(float a)
    {
        if (a == 0)           
            return *this;

        return Vector2f(this->x / a, this->y / a);
    }

    Vector2f operator+(Vector2f v1)
    {
        return Vector2f(this->x + v1.x, this->y + v1.y);
    }

    Vector2f operator-(Vector2f v1)
    {
        return Vector2f(this->x - v1.x, this->y - v1.y);
    }

    float len()
    {
        return(sqrt(this->x * this->x + this->y * this->y));
    }

    float scular(Vector2f v2)
    {
        return(this->x * v2.x + this->y * v2.y);
    }

    Vector2f normalize()
    {
        return *this / this->len();
    }

    Vector2f(float x, float y);
    Vector2f();
} ;

Vector2f::Vector2f(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2f::Vector2f()
{
}
