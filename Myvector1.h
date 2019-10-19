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

// old functions
//
//

Vector2f add( Vector2f v1, Vector2f v2)
{
    Vector2f result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    return result;
}

Vector2f sub( Vector2f v1, Vector2f v2)
{
    Vector2f result;
    result.x =  v1.x - v2.x; 
    result.y = v1.y - v2.y;
    return result;
}

Vector2f mul(Vector2f v, float a)
{
    Vector2f result;
    result.x = v.x * a;
    result.y = v.y * a;
    return result;
}

Vector2f div(Vector2f v, float a)
{
    if( a == 0)
    return v;
    Vector2f result;
    result.x =  v.x / a; 
    result.y = v.y / a;
     
    return result;   
}

float len(Vector2f v)
{
    float a;
    a = sqrt( pow(v.x,2) + pow(v.y,2));
    return a;
}

float scular(Vector2f v1, Vector2f v2)
{
    float result;
    result = v1.x*v2.x + v2.y*v1.y;
    return result;
}

Vector2f normolize(Vector2f v)
{
    Vector2f result;
    result = div(v, len(v));
    return result;
}
