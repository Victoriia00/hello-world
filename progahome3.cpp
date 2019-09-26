#include "TXLib.h"
#include <iostream>
#include <cmath>

const float dt = 0.1;

struct Ball
{
        Ball(int r, int g, int b)
        {
            R = r;
            G = g;
            B = b;
        }

        float x;
        float y;
        float vx;
        float vy;
        int r;
        int R = 250;
        int G = 130;
        int B = 50;
};
void drawball(Ball* ball)
{
    int r0 = ball->r;
    for(int i = ball->r; i > 0; i--)
    {
        txSetFillColor(RGB(ball->R - (ball->R * i/r0), ball->G - (ball->G * i/r0), ball->B - (ball->B * i/r0)));
        txSetColor(RGB(ball->R - (ball->R * i/r0), ball->G - (ball->G * i/r0), ball->B - (ball->B * i/r0)));
        txCircle(ball->x, ball->y,i);
    }
}
void moveball(Ball* ball)
{
    if (ball->y > (600-ball->r) || ball->y < ball->r)
        ball->vy = -ball->vy;
    if (ball->x > (800-ball->r) || ball->x < ball->r)
        ball->vx = -ball->vx;

    ball->x += ball->vx * dt;
    ball->y += ball->vy * dt;
}

void controlball(Ball* ball)
{
     if (GetAsyncKeyState(VK_LEFT))
            ball->vx = ball->vx - 1;
     if (GetAsyncKeyState(VK_RIGHT))
            ball->vx = ball->vx + 1;
     if (GetAsyncKeyState(VK_UP))
            ball->vy = ball->vy - 1;
     if (GetAsyncKeyState(VK_DOWN))
            ball->vy = ball->vy + 1;
}
bool collide(Ball* ball, Ball* ball1)
{
    float proexionV = ((ball1->vx - ball->vx) * (ball1->x-ball->x) + (ball1->vy-ball->vy) * (ball1->y-ball->y)) / ((ball1->x - ball->x)*(ball1->x - ball->x) + (ball1->y-ball->y)*(ball1->y - ball->y));
    if (proexionV > 0)
        return false;
    if (sqrt(pow(ball1->x-ball->x, 2) + pow(ball1->y-ball->y, 2)) > 2*ball->r)
        return false;
    ball->vx += (ball1->x-ball->x) * proexionV;
    ball->vy += (ball1->y-ball->y) * proexionV;
    ball1->vx += (ball->x-ball1->x) * proexionV;
    ball1->vy += (ball->y-ball1->y) * proexionV;
    return true;
}
void assignment(Ball* ball, int x, int y)
{
    ball->x = x;
    ball->y = y;
    ball->vx = 15;
    ball->vy = 15;
    ball->r = 50;
}

int main()
{
    Ball ball = Ball(123,10,45);
    Ball ball1 = Ball(121,101,67);
    txCreateWindow(800, 600);
    assignment(&ball, 450, 370);
    assignment(&ball1, 300, 200);
    for(;;)
    {

        moveball(&ball);
        moveball(&ball1);
        controlball(&ball);
        if (collide(&ball, &ball1))
        {
            if ( sqrt(pow(ball.vx, 2) + pow(ball.vy, 2)) > sqrt(pow(ball1.vx, 2) + pow(ball1.vy, 2)))
            {
                ball1.r -=10;
                if ( ball1.r <= 0)
                {
                    std::cout << "You win";
                }
            } else {
                ball.r -=10;
                if ( ball.r <= 0)
                {
                    std::cout << "Game over";
                }
            }
        }
        txSetFillColor(RGB(0, 0, 0));
        txClear();

        txBegin();
        drawball(&ball);
        drawball(&ball1);

        txEnd();

        txSleep(0.01);

    }
    return 0;
}
