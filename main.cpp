#include "Game.h"
#include "Menu.h"
#include <optional>  

enum class GameStat { Menu, Playing, Scores, Exiting };

int main()
{
    const float width = 640.f;
    const float height = 480.f;

    sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned>(width), static_cast<unsigned>(height) }), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(width, height);
    Game game;  

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
                    currentState = GameStat::Menu;
                    
                }

                if (currentState == GameStat::Menu)
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
                            if (game.loadGame())
                            {
                                currentState = GameStat::Playing;
                            }
                        }

                        else if (idx == 2)
                        {
                                currentState = GameStat::Scores;
                        }

                        else if (idx == 3)
                        {
                                currentState = GameStat::Exiting;
                               
                        }
                    } 
                }
            }
        }

  
        if (currentState == GameStat::Playing)
        {
            game.update();  
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
   
        }

        else if (currentState == GameStat::Exiting)
        {
            window.close();
        }

        window.display();
    }

    return 0;
}