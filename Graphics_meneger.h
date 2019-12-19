#include <iostream>
#include <SFML/Graphics.hpp>
class Basic_object
{
    public:
    virtual void Draw(sf::RenderWindow* window){}
};


class Graphic_Manager
{
    private:
        Basic_object** objects = new Basic_object*[len];
        int len = 100;
        int pos = 0; 

    public:
    
        ~Graphic_Manager()
        {
            delete[] objects;    
        }    
        void drawAll(sf::RenderWindow* window)
        {
            for(int i = 0; i < pos ; i++)
            {
                objects[i]->Draw(window);
            }
        }

        void registrate(Basic_object* obj)
        {
            if(pos > len - 1)
            {
                this->len = this->len * 2;
                
                objects = (Basic_object**) realloc(objects, this->len * sizeof(Basic_object*));
            }
            objects[this->pos] = obj;
            this->pos += 1;
            
        }

        void unregistrate(Basic_object* obj)
        {
            for(int i = 0; i < pos - 1; i++)
                if(objects[i] == obj)
                {
                    for(int j = i; j < pos - 1; j++)
                        objects[j] = objects[j+1];
                     objects[pos - 1] = NULL;
                     return;
                }
        }

       
};
