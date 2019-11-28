#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "file.cpp"


class application
{
public:
    char* maintext;
    char* currenttext;
    void execute();//запуск программы
    Graphic_Manager* graphic_manager = new Graphic_Manager;
};

void ReadFile(std::string filename, application* hackertyper)
{
    std::ifstream file;
    file.open(filename);

    file.seekg(0, file.beg);   
    file.seekg(0, file.end);
    int len = file.tellg();
    file.seekg(0, file.beg);
    
    hackertyper->maintext = new char[len];
    hackertyper->currenttext = new char[len];
    memset( hackertyper->currenttext, ' ', len );
    file.read(hackertyper->maintext, len);
    file.close();

}

class Text:public Basic_object
{
        public:
        sf::Text text;
        Text()
        {
            
        }
        void Draw(sf::RenderWindow* window)
        {
            window->draw(text);
        }

        Text(sf::Font font, int fontSize, int pos_x, int pos_y )
        {
            text.setFont(font);
            text.setCharacterSize(fontSize);
            text.setOutlineColor(sf::Color::Green);
            text.setFillColor(sf::Color::Green);
            text.setPosition(pos_x, pos_y);
        }

        void setString(char* currenttext)
        {
            text.setString(currenttext);
        }
};

/*
void Draw_currenttext(sf::RenderWindow* window, std::string way_to_font, std::string currenttext)
{
    sf::Font font;
    font.loadFromFile(way_to_font);

    sf::Text text(currenttext, font, 19);

    text.setOutlineColor(sf::Color::Green);
    text.setFillColor(sf::Color::Green);

    text.setPosition(0, 0);
    window->draw(text);

}*/

void rotate(sf::View* view, float Velocity)
{
    view->move(0, Velocity);//перемещение по х и по у
}

void Change_currenttext(int* counter, int* flag, char* maintext, char* currenttext, int* string_counter)
{

    if (*flag == 1)
    {
        for (int i = 0; i < 5; i++)//при каждом нажатии проверяет по 5 символов, длина блока 5
        {
            if ((maintext)[i + *(counter)*5] == '\0')
            {
                *flag = 5;
                break;
            } else if ((maintext)[i + *(counter)*5] == '\n')
            {
                *string_counter += 1;
            }
            else
            {
                currenttext[i + (*counter)*5] = (maintext)[i + (*counter)*5];
                //std::cout << currenttext[i + (*counter)*5] << std::endl;
            }
        }

        (*counter)++;//увеличивает колличество написанных сиволов

    }
    fflush(0);//мнгновенно отображает все изменения на экране
}


void application::execute()
{
 
    sf::RenderWindow window(sf::VideoMode(800, 800), "c++ one love");
    sf::View view( sf::FloatRect(0,0,800,800)); //ramka
    
    int counter = 0;
    int string_counter = 0;
    int flag = 1;

    float Velocity = 8.5;

    sf::Font font;
    font.loadFromFile("arial.ttf");

    Text text(font, 20, 0, 0);
    graphic_manager->registrate(&text);
    
    text.setString(currenttext);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (20 * string_counter > 400 + view.getCenter().y)
                {
                    view.move(0, 20);
                }
                
                
                Change_currenttext(&counter, &flag, maintext, currenttext, &string_counter);
                
                text.setString(currenttext);
                
                

            }
        }

        window.clear();
        
     
        graphic_manager->drawAll(&window);
        window.setView(view);//устанавливает текущее положение рамки
        window.display();
    }
}


int main()
{

    application haker_typer;
    ReadFile("file.cpp", &haker_typer);
    haker_typer.execute();

    return 0;
}
