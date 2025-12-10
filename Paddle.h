#pragma once
#include "SFML/Graphics.hpp"

class Paddle
{
private:
	float x;
	float y;
	float w;
	float h;
	float vx;
	sf::RectangleShape shape;

public:
	Paddle(float start_x, float start_y, float start_w, float start_h, float start_vx)
	{
		shape.setSize(sf::Vector2f{ start_w,start_h });
		shape.setOrigin(sf::Vector2f{ start_w / 2, start_h / 2 });
		shape.setPosition(sf::Vector2f{ start_x, start_y });
		shape.setFillColor(sf::Color(0, 0, 128));

		x = start_x;
		y = start_y;
		w = start_w;
		h = start_h;
		vx = start_vx;
	};

	void moveLeft()
	{
		x = x - vx;
		shape.setPosition(sf::Vector2f{ x,y });
	};

	void moveRight()
	{
		x = x + vx;
		shape.setPosition(sf::Vector2f{ x,y });
	};

	void clamp(float width)
	{
		if (x - w / 2 <= 0)
		{
			x =  w / 2;
		};

		if (x + w / 2 >= width)
		{
			x = width - w/2;
		};

	};

	void draw(sf::RenderTarget& target)
	{
		target.draw(shape);
	};

	float getX() const { return x; }
	float getY() const { return y; }
	float getW() const { return w; }
	float getH() const { return h; }

	void setPosition(float newX, float newY)
	{
		x = newX;
		y = newY;
		shape.setPosition(sf::Vector2f{ x,y });
	};

};