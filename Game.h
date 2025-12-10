#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

class Game
{
private:
    sf::Clock deltaClock;

    const float width = 640.f;
    const float height = 480.f;

    Paddle pal;
    Ball pilka;
    std::vector<Brick> bloki;

public:
    Game()
        :
        pal(320.f, 440.f, 100.f, 20.f, 8.f),
        pilka(320.f, 350.f, 8.f, 2.f, 1.f)
    {

        reset();
    }

    void reset()
    {
        const int Ilosc_Kolumn = 6;
        const int Ilosc_Wierszy = 7;

        float rozmiar_bloku_x =
            (width - (Ilosc_Kolumn - 1) * 2.f) / Ilosc_Kolumn;

        float rozmiar_bloku_y = 25.f;

        for (int y = 0; y < Ilosc_Wierszy; y++)
        {
            for (int x = 0; x < Ilosc_Kolumn; x++)
            {
                float posX = x * (rozmiar_bloku_x + 2.f);
                float posY = y * (rozmiar_bloku_y + 2.f) + 60.f;

                int zycie = 0;
                if (y <= 2)
                    zycie = 3;
                if (y > 2 && y <= 4)
                    zycie = 2;
                if (y > 4)
                    zycie = 1;

                bloki.emplace_back(sf::Vector2f{ posX, posY }, sf::Vector2f{ rozmiar_bloku_x, rozmiar_bloku_y }, zycie);

            }
        }
    }


    void update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
            pal.moveLeft();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
            pal.moveRight();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::F5))
        {
            saveGame();
            sf::sleep(sf::milliseconds(200));
        }

        pal.clamp(width);

        pilka.move();
        pilka.collideWalls(width, height);

        if (pilka.collidePaddle(pal))
            std::cout << "HIT PADDLE\n";

        if (pilka.getY() - pilka.getRadius() > height)
        {
            std::cout << "GAME LOST\n";
        }

        if (deltaClock.getElapsedTime().asSeconds() >= 2.f)
        {
            std::cout << "x=" << pilka.getX()
                << " y=" << pilka.getY()
                << " vx=" << pilka.getVx()
                << " vy=" << pilka.getVy() << "\n";

            deltaClock.restart();
        }

        for (auto& blk : bloki)
        {
            if (!blk.checkDestroy() &&
                pilka.getGlobalBounds().findIntersection(blk.getGlobalBounds()))
            {
                blk.trafienie();
                pilka.bounceY();
                std::cout << "HIT BRICK!\n";
            }
        }
    }

    void render(sf::RenderTarget& target)
    {

        for (auto& blk : bloki)
            blk.draw(target);

        pal.draw(target);
        pilka.draw(target);


    }

    void saveGame()
    {
        GameState gs;
        gs.capture(pal, pilka, bloki);
        gs.saveToFile("savegame.txt");
    }

    bool loadGame()
    {
        GameState gs;
        if (gs.loadFromFile("savegame.txt"))
        {
            gs.apply(pal, pilka, bloki);
            return true;
        }
        return false;
    }

};