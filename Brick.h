#pragma once
#include <SFML/Graphics.hpp>
#include <array> //prosta tablica stalego rozmiaru

class Brick : public sf::RectangleShape {
private:
	int hitPoints; //0-3
	bool isDestroyed; //jesli zniszczony = true
	//sf::RectangleShape brick; nie jest potrzebne, nie programujemy w ten sposób
	static const std::array<sf::Color, 4> colorLUT; //tablica look-up table


public:
	Brick(sf::Vector2f start_Pos, sf::Vector2f size, int HP);
	void aktualizujkolor();
	void trafienie();
	void draw(sf::RenderTarget &window);
	bool czyZniszczony() { return isDestroyed; }
};

Brick::Brick(sf::Vector2f start_Pos, sf::Vector2f size, int HP)
{
	hitPoints = HP; //warunek do HP zeby nie bylo wieksze od 3
	isDestroyed = false; //nie jest zniszczony
	this->setFillColor(sf::Color::Yellow);
	this->setOutlineColor(sf::Color::White);
	//wrzucic pozniej w klase tak jak mam reszte .h
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
	if (isDestroyed == true)
		return; //zakonczenie funkcji
	hitPoints--;
	aktualizujkolor();
	if (hitPoints <= 0)
		isDestroyed = true; //jest zniszczony
};

void Brick::aktualizujkolor()
{
	if(hitPoints>=0 && hitPoints<3)
		this->setFillColor(colorLUT[hitPoints]);
}

void Brick::draw(sf::RenderTarget& window)
{
	window.draw(*this);
}