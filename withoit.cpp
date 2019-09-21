#include "TXLib.h"
#include <iostream>

void drawball( int x, int y, int r, int R, int G, int B)
{
    int r0 = r;
    for(int i = r; i > 0; i--)
    {
        txSetFillColor(RGB(R - (R * r/r0), G - (G * r/r0), B - (B * r/r0)));
        txSetColor(RGB(R - (R * r/r0), G - (G * r/r0), B - (B * r/r0)));
        txCircle(x, y, r);
    }
}
void moveball(float* x, float* y, float* vx, float* vy, float r, float dt)
{
        if (*y > (600-r) || *y < r)
            *vy = -*vy;
        if (*x > (800-r) || *x < r)
            *vx = -*vx;
}
void coint(float* x, float* y, float* vx, float* vy, float dt)
{
        *x += *vx*dt;
        *y += *vy*dt;
}
void controlball(float* vx, float* vy)
{
     if (GetAsyncKeyState(VK_LEFT))
            *vx = *vx - 1;
     if (GetAsyncKeyState(VK_RIGHT))
            *vx = *vx + 1;
     if (GetAsyncKeyState(VK_UP))
            *vy = *vy - 1;
     if (GetAsyncKeyState(VK_DOWN))
            *vy = *vy + 1;
}
bool collide(float x, float y, float x1, float y1, float *vx, float *vy, float *vx1, float *vy1, float r, float r1)
{
    float proexionV = ((*vx1-*vx) * (x1-x) + (*vy1-*vy) * (y1-y)) / ((x1-x)*(x1-x) + (y1-y)*(y1-y));
    if (proexionV > 0)
    return false;
    if (sqrt((x1-x)*(x1-x) + (y1-y)*(y1-y)) > 2*r)
    return false;
    *vx += (x1-x) * proexionV;
    *vy += (y1-y) * proexionV;
    *vx1 += (x-x1) * proexionV;
    *vy1 += (y-y1) * proexionV;
    return true;
}
int main()
{
    txCreateWindow(800, 600);
    const float dt = 0.1;
    float x = 400;
    float y = 300;
    float vx = 15;
    float vy = 15;
    float r = 50;
    float x1 = 200;
    float y1 = 300;
    float vx1 = 15;
    float vy1 = 15;
    float r1 = 50;
    for(;;)
    {

        moveball(&x, &y, &vx, &vy, r, dt);
        moveball(&x1, &y1, &vx1, &vy1, r1, dt);
        controlball(&vx, &vy);
        coint(&x, &y, &vx, &vy, dt);
        if (collide(x, y, x1, y1, &vx, &vy, &vx1, &vy1, r, r1))
        {
            if ( sqrt(vx*vx + vy*vy) > sqrt(vx1*vx1 + vy1*vy1))
            {
                r1 -=10;
                if ( r1 <= 0)
                {
                    std::cout << "You win";
                }
            } else {
                r -=10;
                if ( r <= 0)
                {
                    std::cout << "Game over";
                }
            }
        }
        txSetFillColor(RGB(0, 0, 0));
        txClear();
        drawball(x, y, r, 250, 45, 100);
        drawball(x1, y1, r1, 59, 45, 250);
        txSleep(dt);
        txBegin();

    }
    return 0;
}
