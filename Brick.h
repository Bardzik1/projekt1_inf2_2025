#pragma once
#include "SFML/Graphics.hpp"
#include <array> 

class Brick : public sf::RectangleShape {
private:
	int hitPoints; 
	bool Destroyed; 
	static const std::array<sf::Color, 4> colorLUT; 


public:
	Brick(sf::Vector2f start_pos, sf::Vector2f size, int HP);
	void aktualizujkolor();
	void trafienie();
	void draw(sf::RenderTarget &window);
	bool checkDestroy() const { return Destroyed; }
	sf::FloatRect getGlobalBounds() const { return sf::RectangleShape::getGlobalBounds(); }
	int getHP() const { return hitPoints; }
};

Brick::Brick(sf::Vector2f start_pos, sf::Vector2f size, int HP)
{
	hitPoints = HP;
	if (HP > 3)
	{
		HP = 3;
	}
	else if (HP < 0)
	{
		HP = 0;
	}
	Destroyed = false; 
	this->setPosition(start_pos);
	this->setSize(size);
	this->setOutlineThickness(2.f);
	this->setOutlineColor(sf::Color::White);
	aktualizujkolor();

};

const std::array<sf::Color, 4> Brick::colorLUT = {
	sf::Color::Transparent,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Red
};

void Brick::trafienie()
{
	if (Destroyed == true)
	{
		return;
	} 
	hitPoints--;
	aktualizujkolor();
	if (hitPoints <= 0)
	{
		Destroyed = true;
	}; 
};

void Brick::aktualizujkolor()
{
	if (hitPoints >= 0 && hitPoints <= 3)
		this->setFillColor(colorLUT[hitPoints]);
};

void Brick::draw(sf::RenderTarget& window)
{
	if (Destroyed == false)
	{
		window.draw(*this);
	};
};


