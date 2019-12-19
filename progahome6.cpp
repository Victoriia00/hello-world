#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <ctime>
#include "Myvector1.h"
#include "Graphics_meneger.h"

const float dt = 0.01;

class Particle: public Basic_object
{
    public:
    	Vector2f position;
    	Vector2f velocity;

    	void draw(sf::RenderWindow& window);

    	float radius = 5;
   	float mass = 1;
    	int R = 150;
    	int G = 10;
    	int B = 200;
	
	void draw(sf::RenderWindow* window)
        {
            sf::CircleShape shape(this->r);
        
            for(int i = this->r;i > 0; i = i - 2)
            {
                int current_Red = this->red - this->red*0.85*i/this->r;
                int current_Green = this->green - this->green*0.85*i/this->r;
                int current_Blue = this->blue - this->blue*0.85*i/this->r;

                shape.setRadius(i);
                shape.setFillColor(sf::Color(currentRed, currentGreen, currentBlue));
                shape.setPosition(this->Q.x - i, this->Q.y - i);
                window->draw(shape);
            }

        }

};


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



void collide_with_wall(Particle* particles)
{
    for(int i = 0; i < 100 ; i++)
    {

        if (particles[i].position.y > (800-particles[i].radius) || particles[i].position.y < particles[i].radius && particles[i].velocity.y < 0)
            particles[i].velocity.y = -particles[i].velocity.y;

        if (particles[i].position.x > (800-particles[i].radius) || particles[i].position.x < particles[i].radius && particles[i].velocity.x < 0)
            particles[i].velocity.x = -particles[i].velocity.x;

        particles[i].position.x += particles[i].velocity.x * dt;
        particles[i].position.y += particles[i].velocity.y * dt;

    }
}


bool checkCollision(Particle particle1, Particle particle2)
{
    if ( (particle1.position.x-particle2.position.x)*(particle1.position.x-particle2.position.x) + (particle1.position.y-particle2.position.y)*(particle1.position.y-particle2.position.y) <= (particle1.radius+particle2.radius)*(particle1.radius+particle2.radius))
        return true;
    else
        return false;
}

void collide(Particle* particle1, Particle* particle2)
{
    if (checkCollision(*particle1, *particle2))
     {
        Vector2f centre_mass = particle2->position - particle1->position;
        Vector2f V1proection = normolize(centre_mass) * ((scular(particle1->velocity, centre_mass)) / centre_mass.len() );
        Vector2f V2proection = normolize(centre_mass) * ((scular(particle2->velocity, centre_mass)) / centre_mass.len() );

        particle1->velocity = particle1->velocity - V1proection;
        particle1->velocity = particle1->velocity + V2proection;

        particle2->velocity = particle2->velocity - V2proection;
        particle2->velocity = particle2->velocity + V1proection;

        if (centre_mass.len() < (particle1->radius +particle2->radius)) 
            {
                particle2->position = particle2->position + normolize(centre_mass) * ((particle1->radius + particle2->radius - centre_mass.len()) / 2);
                particle1->position = particle1->position - normolize(centre_mass) * ((particle1->radius + particle2->radius - centre_mass.len()) / 2);
            }
    }
 
	

}

void colide_all_particles(Particle* particles)
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
         {
             if (i < j)
             {
                 collide(&particles[i], &particles[j]);
             }
           
         }
    }

}
/*
void Particle::draw(sf::RenderWindow& window )
{

    sf::CircleShape shape(radius);
    shape.setPosition(position.x - radius, position.y - radius);
    shape.setFillColor(sf::Color(R, G, B));
    window.draw(shape);

}

void DrawAllBalls(Particle* particles,sf::RenderWindow& window )
{
    for (int i = 0; i < 100; ++i)
    {

        particles[i].draw(window);
    }

}
*/
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    
    Particle* particles = new Particle[100];
    initial_conditions(particles);
    
    Graphic_Manager manager;

    for(int i = 0; i < 100; i++)
        manager.registrate(&particles[i]);
    
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        manager.drawAll(&window);
        collide_with_wall(particles);
        colide_all_particles(particles);
        //std::cout << particles[98].position.x << std::endl;
        window.display();
    }
    delete[] particles;
    return 0;
}
