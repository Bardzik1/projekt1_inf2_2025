#include "GO.h"
#include <iostream>

GameOverScreen::GameOverScreen(float width, float height)
    : titleText(font), scoreText(font), infoText(font)
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
            std::cout << "Sciezka zaladowanej czcionki: " << path << std::endl;
            fontLoaded = true;
            break;
        }
    }
    if (!fontLoaded) {
        std::cout << "Nie zaladowano czcionki" << std::endl;

    }

    background.setSize({ width, height });
    background.setFillColor(sf::Color(0, 0, 0, 150));

    titleText.setFont(font);
    titleText.setString("KONIEC GRY");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Red);
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setOrigin({ bounds.size.x / 2.0f, bounds.size.y / 2.0f });
    titleText.setPosition({ width / 2.0f, height / 3.0f });

    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({ width / 2.0f, height / 2.0f });

    infoText.setFont(font);
    infoText.setString("Wcisnij ENTER aby wrocic do menu");
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color(200, 200, 200));

    bounds = infoText.getLocalBounds();
    infoText.setOrigin({ bounds.size.x / 2.0f, bounds.size.y / 2.0f });
    infoText.setPosition({ width / 2.0f, height * 0.7f });
}

void GameOverScreen::setScore(int score)
{
    scoreText.setString("Twoj wynik: " + std::to_string(score));

    sf::FloatRect bounds = scoreText.getLocalBounds();
    scoreText.setOrigin({ bounds.size.x / 2.0f, bounds.size.y / 2.0f });
}

void GameOverScreen::draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(titleText);
    window.draw(scoreText);
    window.draw(infoText);
}