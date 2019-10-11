#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <ctime>
#include "Myvector.h"

const float dt = 0.01;

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

    void collide_with_wall();
    void drawballs();



void initial_conditions(Particle* particles) // создали все частицы слоями, дали начальные скорости рандомно
{
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++)
        {   
            particles[i + (j)*10].position.x = 60 * (i+1);
            particles[i + (j)*10].position.y = 60 * (j+1);// иначе чаастица в нулевой координате появится
        }
    }

    for(int i = 0; i < 100; i++)
    {
        particles[i].velocity.x = (std::rand() % 20);
        particles[i].velocity.y = (std::rand() % 20);
    }
}

bool collide(Particle* particle1, Particle* particle2)
{
    float proexionV = ((particle2->velocity.x-particle1->velocity.x) * (particle2->position.x-particle1->position.x) + (particle2->velocity.y-particle1->velocity.y) * (particle2->position.y-particle1->position.y)) / ((particle2->position.x-particle1->position.x)*(particle2->position.x-particle1->position.x) + (particle2->position.y-particle1->position.y)*(particle2->position.y-particle1->position.y));
    if (proexionV > 0)
        return false;
    if (sqrt((particle2->position.x-particle1->position.x)*(particle2->position.x-particle1->position.x) + (particle2->position.y-particle1->position.y)*(particle2->position.y-particle1->position.y)) <= 2*particle2->radius)
        return false;
    particle1->velocity.x += (particle2->position.x-particle1->position.x) * proexionV;
    particle1->velocity.y += (particle2->position.y-particle1->position.y) * proexionV;
    particle2->velocity.x += (particle2->position.x-particle1->position.x) * proexionV;
    particle2->velocity.y += (particle2->position.y-particle1->position.y) * proexionV;
    return true;
}


void collide_with_wall(Particle* particles)
{
    for(int i = 0; i < 100 ; i++)
    {

        if (particles[i].position.y > (600-particles[i].radius) || particles[i].position.y < particles[i].radius && particles[i].velocity.y < 0)
            particles[i].velocity.y = -particles[i].velocity.y;

        if (particles[i].position.x > (800-particles[i].radius) || particles[i].position.x < particles[i].radius && particles[i].velocity.x < 0)
            particles[i].velocity.x = -particles[i].velocity.x;

        particles[i].position.x += particles[i].velocity.x * dt;
        particles[i].position.y += particles[i].velocity.y * dt;

    }
}

void colide_all_particles(Particle* particles)
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
         {
             if (i != j)
             {
                 collide(&particles[i], &particles[j]);
             }
           
         }
    }

}

void DrawBall(const Particle& particles,sf::RenderWindow& window )
{

    sf::CircleShape shape(particles.r);
    shape.setPosition(particles.position.x - particles.r, particles.position.y - particles.r);
    shape.setFillColor(sf::Color(particles.R, particles.G, particles.B));
    window.draw(shape);

}

void DrawAllBalls(Particle* particles,sf::RenderWindow& window )
{
    for (int i = 0; i < 100; ++i)
    {

        DrawBall(particles[i],window);
    }

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    
    Particle* particles = new Particle[100];
    initial_conditions(particles);
    
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        DrawAllBalls(particles,window);
        collide_with_wall(particles);
        colide_all_particles(particles);
        
        window.display();
    }
    return 0;
}
