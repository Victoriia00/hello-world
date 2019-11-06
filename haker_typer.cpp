#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>


class application
{
public:

    std::string maintext;
    std::string currenttext;
    void execute();//запуск программы
};

void ReadFile(std::string filename, application* hackertyper)
{
    std::ifstream DATABASE(filename);
    while (!DATABASE.eof())
    {
        std::string str;
        std::getline(DATABASE, str);
        hackertyper->maintext += str;
        hackertyper->maintext += "\n";
    }

}

void Draw_currenttext(sf::RenderWindow* window, std::string way_to_font, std::string currenttext)
{
    sf::Font font;
    font.loadFromFile(way_to_font);

    sf::Text text(currenttext, font, 19);

    text.setOutlineColor(sf::Color::Green);
    text.setFillColor(sf::Color::Green);

    text.setPosition(0, 0);
    window->draw(text);

}

void rotate(sf::View* view, float Velocity)
{
    view->move(0, Velocity);//перемещение по х и по у
}

void Change_currenttext(int* counter, int* flag, std::string* maintext, std::string* currenttext)
{

    if (*flag == 1)
    {
        for (int i = 0; i < 5; i++)//при каждом нажатии проверяет по 5 символов, длина блока 5
        {
            if ((*maintext)[i + *(counter)*5] == *"\0")
            {
                *flag = 5;
                break;
            }
            else
            {
                *currenttext += (*maintext)[i + (*counter)*5];
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
    int flag = 1;
    float Velocity = 8.5;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    rotate(&view, -Velocity);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    rotate(&view, Velocity);
                }
                else
                {
                    Change_currenttext(&counter, &flag, &maintext, &currenttext);
                }

            }
        }

        window.clear();

        Draw_currenttext(&window, "arial.ttf", currenttext);

        window.setView(view);//устанавливает текущее положение рамки
        window.display();
    }
}


int main()
{

    application haker_typer;
    ReadFile("main.cpp", &haker_typer);
    haker_typer.execute();

    return 0;
}




