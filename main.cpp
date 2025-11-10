#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include <iostream>
#include "Brick.h"
#include <vector>

int main()
{
	const float width = 640.f;
	const float height = 480.f;
	sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned>(width), static_cast<unsigned>(height) }), "Arkanoid Test");
	window.setFramerateLimit(60);

    sf::Clock deltaClock;

	Paddle pal(320.f, 440.f, 100.f, 20.f, 8.f);

	Ball pilka(320.f, 200.f, 8.f, 2.f, 1.f);

    //laby 10.11
    //tworzenie blokow
    std::vector<Brick> bloki; //bloki cegly, tablica wektorowa lepsza niz zwykla 
    //(zwykla nie dziala - nie ma konstruktora domyslnego) Brick bloki2[10] - nie mozna w ten sposob
    
    //ustalenie wlasciwosci poziomu
    const int Ilosc_Kolumn = 12;
    const int Ilosc_Wierszy = 4;
    float rozmiar_bloku_x = (width -(Ilosc_Kolumn-1)*2.f)/Ilosc_Kolumn; // uzaleznic od szerokosci ekranu
    float rozmiar_bloku_y = 20.f;

    //---procedura rysujaca bloki
    for (int y = 0; y < Ilosc_Wierszy; y++)
    {
        for (int x = 0; x < Ilosc_Kolumn; x++)
        {
            float posX = x * (rozmiar_bloku_x + 2.f); //2px na przerwe
            float posY = y * (rozmiar_bloku_y + 2.f) + 60.f;
            //algorytm ustalania koloru
            int zycie = 0;
            if (y == 0)
                zycie = 1;
            if (y >= 1)
                zycie = 2;


            bloki.emplace_back(sf::Vector2f{ posX,posY }, sf::Vector2f{ rozmiar_bloku_x, rozmiar_bloku_y }, 1);

        }
    }



    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            pal.moveLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            pal.moveRight();
        }

        pal.clamp(width);
        pilka.move();
        pilka.collideWalls(width, height);
        pilka.collidePaddle(pal);
        
        if (pilka.collidePaddle(pal))
        {
            std::cout << "HIT PADDLE\n";
        };

        if (pilka.getY() - pilka.getRadius() > height)
        {
            std::cout << "GAME LOST";
            break;
        };

        if (deltaClock.getElapsedTime().asSeconds() >= 2.f)
        {
            std::cout << "x= " << pilka.getX()
                << " y=" << pilka.getY()
                << " vx=" << pilka.getVx()
                << " vy=" << pilka.getVy()
                << std::endl;

            deltaClock.restart();
        }

        //kolizja pilki z blokami
        for (auto& blk : bloki)
        {
            if (!blk.isDestroyed() && pilka.getGlobalBounds().findIntersection(blk.getGlobalBounds()))
            {
                blk.trafienie(); // zmniejsz ilosc zyc i zmieni kolor
                pilka.bounceY();
            };

        };

        //usuwanie zniszczonych blokow
        for (int i = bloki.size() - 1; i >= 0; i--)
        {
            if (bloki[i].czyZniszczony())
            {
                bloki.erase(bloki.begin() + 1);
            };
        };


        window.clear(sf::Color(20, 20, 20));
        pal.draw(window);
        pilka.draw(window);
        //rysowanie blokow
        for (auto& blk : bloki)
        {
            blk.draw(window);
        };


        window.display();
    }

	
};





