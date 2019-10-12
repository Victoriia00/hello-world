#include <iostream>
#include <cstdlib>
#include <cmath>

struct Vector2f
{
    float x = 0;
    float y = 0;
};

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
    result.y = v1.y + v2.y;
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
    Vector2f result;
    result.x =  v.x / a; 
    result.y = v.y / a;
    if( a == 0)
        return v; 
    return result;   
}

float len(Vector2f v)
{
    float a;
    a = sqrt( pow(v.x,2) - pow(v.y,2));
    return a;
}

float scular(Vector2f v1, Vector2f v2)
{
    float result;
    result = pow(v1.x,2) + pow(v2.x,2);
    return result;
}

Vector2f normolize(Vector2f v)
{
    float len = sqrt( pow(v.x,2) - pow(v.y,2));
    float v1 = v.x / len;
    float v2 = v.y / len;
    Vector2f v3;
    v3.x = v1;
    v3.y = v2;
    return v3;
}
