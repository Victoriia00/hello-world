#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cstring>
#include "Graphics_meneger.h"

const int max = 100000;
const int number = 800 / (16 + 1);

class Text:public Basic_object
{
        public:
        sf::Text text;
        void Draw(sf::RenderWindow* window)
        {
            window->draw(text);
        }
        
        void setString(char* currenttext)
        {
            text.setString(currenttext);
        }
        void build(sf::Font* font, int font_size, int x, int y, sf::Color color = sf::Color::Green)
        {
            text.setFont(*font);
            text.setCharacterSize(font_size);
            text.setFillColor(sf::Color(color));
            text.setPosition(x, y);
        }

};


int file_len(std::ifstream* file)
{
    file->seekg(0, file->beg); 
    file->seekg(0, file->end);
    int len = file->tellg();
    file->seekg(0, file->beg);

    return len;
}
void build_text(sf::Text* text, sf::Font* font, int font_size, int x, int y, sf::Color color = sf::Color::Green)
{
   text->setFont(*font);
   text->setCharacterSize(font_size);
   text->setFillColor(sf::Color::Green);
   text->setPosition(x, y);
}
void change_Text(char* currenttext, int* flag, int* string_counter)
{
    if (*string_counter == number)
    {
        int position = 0;
        for(int i = 0; i < max; i++) 
            if(currenttext[i] == '\n')
            {
                position = i;
                break;
            }
        
        for(int i = 0; i <= *flag - position - 1; i++)
        {
            currenttext[i] = currenttext[i + position + 1];
        }
        for(int i = *flag - position; i <= *flag; i++)
            currenttext[i] = ' ';
        
        *flag = *flag - position - 1 ;
        *string_counter = *string_counter - 1;
        
    }
}

void refresh_currenttext(int* flag, int* string_counter, int* text_counter, int t_len, char* currenttext, char* buffer)
{
    for(int i = 0; i < 3; i++)
    {   
        if(*text_counter != t_len - 1)
           { 
            currenttext[*flag + 1] = buffer[*text_counter + 1]; 
            if(buffer[*text_counter + 1] == '\n')
                *string_counter += 1;
            *text_counter += 1;
            *flag += 1;
            change_Text(currenttext, flag, string_counter);
           }
    }
}



int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 800), "c++ one love");
    Text text;
    sf::Font font; 
    font.loadFromFile("arial.ttf");
    text.build(&font, 16, 0, 0, sf::Color::Green);                                   

    std::ifstream file;  
    file.open("1.txt");
    int len = file_len(&file);
    char* buffer = new char[len];
    file.read(buffer, len);
    file.close();

    int flag = -1;
    int string_counter = 0;
    int text_counter = -1;

    char *currenttext = new char [800/16 * 800/16];
    memset(currenttext, ' ', 800/ 16 * 800 / 16 );

    Graphic_Manager manager;
    manager.registrate(&text);

    sf::Event event;
    bool update = false;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
		{
		    if (event.type == sf::Event::Closed) 
                  window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                update = true;
			}
		}
        if(update)
        {
            refresh_currenttext(&flag, &string_counter, &text_counter, len, currenttext, buffer);
            text.setString(currenttext);
            update = false;
        }

        window.clear();
        manager.drawAll(&window);
        window.display();

    }

    delete[] buffer;
    delete[] currenttext;

}
