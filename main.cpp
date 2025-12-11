#include "Game.h"
#include "Menu.h"
#include "Scores.h"
#include "GO.h"
#include <optional>
#include <iostream>

enum class GameStat { Menu, Playing, GameOver, Scores, Exiting };

int main()
{
    const float width = 640.f;
    const float height = 480.f;

    sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned>(width), static_cast<unsigned>(height) }), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(width, height);
    Game game;
    HighScores highScores(width, height);
    GameOverScreen gameOverScreen(width, height);

    GameStat currentState = GameStat::Menu;
    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();

        while (const std::optional ev = window.pollEvent())
        {
            if (ev->is<sf::Event::Closed>())
                window.close();

            if (const auto* key = ev->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                {
                    if (currentState == GameStat::Playing)
                    {
                        highScores.addScore(game.getScore());
                        currentState = GameStat::Menu;
                    }
                    else if (currentState == GameStat::GameOver || currentState == GameStat::Scores)
                    {
                        currentState = GameStat::Menu;
                    }
                }

                else if (currentState == GameStat::GameOver)
                {
                    if (key->scancode == sf::Keyboard::Scancode::Enter)
                    {
                        currentState = GameStat::Menu;
                    }
                }

                else if (currentState == GameStat::Menu)
                {
                    if (key->scancode == sf::Keyboard::Scancode::Up)
                        menu.przesunG();
                    else if (key->scancode == sf::Keyboard::Scancode::Down)
                        menu.przesunD();
                    else if (key->scancode == sf::Keyboard::Scancode::Enter)
                    {
                        int idx = menu.getSelectedItem();

                        if (idx == 0)
                        {
                            game.reset();
                            currentState = GameStat::Playing;
                        }
                        else if (idx == 1)
                        {
                            if (game.loadGame()) currentState = GameStat::Playing;
                        }
                        else if (idx == 2)
                        {
                            currentState = GameStat::Scores;
                        }
                        else if (idx == 3)
                        {
                            window.close();
                        }
                    }
                }
            }
        }

        if (currentState == GameStat::Playing)
        {
            game.update();

            if (game.isGameOver())
            {
                highScores.addScore(game.getScore());
                gameOverScreen.setScore(game.getScore());
                currentState = GameStat::GameOver;
            }
        }

        window.clear();

        if (currentState == GameStat::Menu)
        {
            menu.draw(window);
        }
        else if (currentState == GameStat::Playing)
        {
            game.render(window);
        }
        else if (currentState == GameStat::Scores)
        {
            highScores.draw(window);
        }
        else if (currentState == GameStat::GameOver)
        {
            game.render(window);
            gameOverScreen.draw(window);
        }

        if (window.isOpen())
            window.display();
    }

    return 0;
}