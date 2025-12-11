#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class HighScores
{
private:
    sf::Font font;

    std::vector<int> scores;
    std::vector<sf::Text> scoreTexts;
    sf::Text titleText;
    sf::Text infoText;

    float windowWidth;
    float windowHeight;
    const std::string filename = "wyniki.txt";

    void loadScores();
    void saveScores();
    void updateTextObjects();

public:
    HighScores(float width, float height);

    void addScore(int score);
    void draw(sf::RenderWindow& window);
};