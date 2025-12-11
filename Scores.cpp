#include "Scores.h"
#include <fstream>
#include <algorithm>
#include <iostream>

HighScores::HighScores(float width, float height)
    : titleText(font), infoText(font)
{
    windowWidth = width;
    windowHeight = height;

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

    if (!fontLoaded) 
    {
        std::cout << "Nie zaladowano czcionki" << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("NAJLEPSZE WYNIKI");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect rect = titleText.getLocalBounds();
    titleText.setOrigin({ rect.size.x / 2.0f, rect.size.y / 2.0f });
    titleText.setPosition({ width / 2.0f, 50.f });

    infoText.setFont(font);
    infoText.setString("Wcisnij ESC aby wrocic");
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color(150, 150, 150));
    infoText.setPosition({ 20.f, height - 40.f });

    loadScores();
    updateTextObjects();
}

void HighScores::loadScores()
{
    scores.clear();
    std::ifstream file(filename);
    if (file.is_open())
    {
        int s;
        while (file >> s)
        {
            scores.push_back(s);
        }
        file.close();
    }
    std::sort(scores.begin(), scores.end(), std::greater<int>());
}

void HighScores::saveScores()
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (int s : scores)
        {
            file << s << "\n";
        }
        file.close();
    }
}

void HighScores::addScore(int score)
{
    if (score <= 0) return;

    scores.push_back(score);
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    if (scores.size() > 10)
    {
        scores.resize(10);
    }

    saveScores();
    updateTextObjects();
}

void HighScores::updateTextObjects()
{
    scoreTexts.clear();

    for (size_t i = 0; i < scores.size(); i++)
    {
        sf::Text text(font);

        text.setCharacterSize(25);

        std::string content = std::to_string(i + 1) + ". " + std::to_string(scores[i]);
        text.setString(content);
        text.setFillColor(sf::Color::White);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({ bounds.size.x / 2.0f, bounds.size.y / 2.0f });
        text.setPosition({ windowWidth / 2.0f, 120.f + i * 35.f });

        scoreTexts.push_back(text);
    }
}

void HighScores::draw(sf::RenderWindow& window)
{
    window.draw(titleText);
    for (const auto& text : scoreTexts)
    {
        window.draw(text);
    }
    window.draw(infoText);
}