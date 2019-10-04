#include <iostream>

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "myvector.h"








struct Particle
{
    Vector2f position;
    Vector2f velocity;

    float radius = 1;
    float mass = 1;
    int R = 150;
    int G = 10;
    int B = 200;

};

struct centre_mass
{
    centre_mass(float vel_x, float vel_y)
    {
        velx = vel_x;
        vely = vel_y;
    }
    float velx;
    float vely;
};

struct data
{
    float dt = 0.01;
    Particle* particles = new Particle[100];
    void initial_conditions();
    bool collide(float x, float y, float x1, float y1, float *vx, float *vy, float *vx1, float *vy1, float r, float r1);
    void collide_with_wall();
    void drawballs();
};


void data::initial_conditions() // создали все частицы слоями, дали начальные скорости рандомно
{
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            particles[i + (j)*10].position.x =10 * (i+1);
            particles[i + (j)*10].position.y = 10 * (j+1);// иначе чаастица в нулевой координате появится
        }
    }

    for(int i = 0; i < 100; i++)
    {
        particles[i].velocity.x = (std::rand() % 8)/3;
        particles[i].velocity.y = (std::rand() % 8)/3;
    }
}

bool data::collide(float x, float y, float x1, float y1, float *vx, float *vy, float *vx1, float *vy1, float r, float r1)
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




void data::collide_with_wall()
{
    for(int i = 0; i < 100 ; i++)
    {
        if (particles[i].position.y > (600-particles[i].radius) || particles[i].position.y < particles[i].radius)
            particles[i].velocity.y = -particles[i].velocity.y;
        if (particles[i].position.x > (800-particles[i].radius) || particles[i].position.x < particles[i].radius)
            particles[i].velocity.x = -particles[i].velocity.x;

        particles[i].position.x += particles[i].velocity.x * dt;
        particles[i].position.y += particles[i].velocity.y * dt;
    }
}

int main()
{

    data my_data;
    my_data.initial_conditions();
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < 100; i++)
        {
            sf::CircleShape shape(1.f);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(my_data.particles[i].position.x, my_data.particles[i].position.y);
            window.draw(shape);
            my_data.collide_with_wall();
        }
        /*
        for (int i = 0; i < 100; i++)
        {
            for (int j = i+1; j<100; i++)
            {
                float x = my_data.particles[i].position.x;
                float y = my_data.particles[i].position.y;
                float x1 = my_data.particles[j].position.x;
                float y1 = my_data.particles[j].position.y;
                float vx = my_data.particles[i].velocity.x;
                float vy = my_data.particles[i].velocity.y;
                float vx1 = my_data.particles[j].velocity.x;
                float vy1 = my_data.particles[j].velocity.y;
                float r, r1 = my_data.particles[j].radius;
                my_data.collide(x,y,x1,y1,&vx,&vy,&vx1,&vy1,r,r1);
            }
        }
        */


        window.display();
    }
    return 0;
}
