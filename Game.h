#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <optional>
#include <string>
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

    sf::Font font;
    sf::Text scoreText;

    Paddle pal;
    Ball pilka;
    std::vector<Brick> bloki;

    int score = 0;
    bool gameOver = false;

public:
    Game()
        :
        scoreText(font),
        pal(320.f, 440.f, 100.f, 20.f, 8.f),
        pilka(320.f, 350.f, 8.f, 2.f, 1.f)
    {
        const char* fontPaths[] = {
            "fonts/arial.ttf",
            "../fonts/arial.ttf",
            "../../fonts/arial.ttf",
            "arial.ttf",
            "C:/Windows/Fonts/arial.ttf"
        };

        bool fontLoaded = false;
        for (const char* path : fontPaths) {
            if (font.openFromFile(path)) {
                fontLoaded = true;
                break;
            }
        }
        if (!fontLoaded) std::cout << "[WARNING] Game: Nie udalo sie wczytac czcionki!\n";

        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition({ 20.f, 10.f });
        scoreText.setString("Wynik: 0");

        reset();
    }

    void reset()
    {
        score = 0;
        gameOver = false;
        scoreText.setString("Wynik: 0");

        const int Ilosc_Kolumn = 6;
        const int Ilosc_Wierszy = 7;

        float rozmiar_bloku_x = (width - (Ilosc_Kolumn - 1) * 2.f) / Ilosc_Kolumn;
        float rozmiar_bloku_y = 25.f;

        bloki.clear();

        for (int y = 0; y < Ilosc_Wierszy; y++)
        {
            for (int x = 0; x < Ilosc_Kolumn; x++)
            {
                float posX = x * (rozmiar_bloku_x + 2.f);
                float posY = y * (rozmiar_bloku_y + 2.f) + 60.f;

                int zycie = 0;
                if (y <= 2) zycie = 3;
                else if (y > 2 && y <= 4) zycie = 2;
                else if (y > 4) zycie = 1;

                bloki.emplace_back(sf::Vector2f{ posX, posY }, sf::Vector2f{ rozmiar_bloku_x, rozmiar_bloku_y }, zycie);
            }
        }
    }

    void update()
    {
        if (gameOver) return;

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

        pilka.collidePaddle(pal);

        if (pilka.getY() - pilka.getRadius() > height)
        {
            gameOver = true;
        }

        if (deltaClock.getElapsedTime().asSeconds() >= 2.f)
        {
            deltaClock.restart();
        }

        for (auto& blk : bloki)
        {
            if (blk.checkDestroy()) continue;

            if (const auto intersection = pilka.getGlobalBounds().findIntersection(blk.getGlobalBounds()))
            {
                if (intersection->size.x > intersection->size.y)
                {
                    pilka.bounceY();
                    if (pilka.getY() < blk.getGlobalBounds().position.y + blk.getGlobalBounds().size.y / 2.f)
                        pilka.setPosition(pilka.getX(), blk.getGlobalBounds().position.y - pilka.getRadius() - 0.1f, pilka.getVx(), pilka.getVy());
                    else
                        pilka.setPosition(pilka.getX(), blk.getGlobalBounds().position.y + blk.getGlobalBounds().size.y + pilka.getRadius() + 0.1f, pilka.getVx(), pilka.getVy());
                }
                else
                {
                    pilka.bounceX();
                }

                blk.trafienie();
                score += 10;
                scoreText.setString("Wynik: " + std::to_string(score));
            }
        }
    }

    void render(sf::RenderTarget& target)
    {
        for (auto& blk : bloki)
            blk.draw(target);

        pal.draw(target);
        pilka.draw(target);
        target.draw(scoreText);
    }

    void saveGame()
    {
        GameState gs;
        gs.capture(pal, pilka, bloki, score);
        gs.saveToFile("savegame.txt");
    }

    bool loadGame()
    {
        GameState gs;
        if (gs.loadFromFile("savegame.txt"))
        {
            gs.apply(pal, pilka, bloki, score);
            gameOver = false;
            scoreText.setString("Wynik: " + std::to_string(score));
            return true;
        }
        return false;
    }

    int getScore() const { return score; }
    bool isGameOver() const { return gameOver; }
};