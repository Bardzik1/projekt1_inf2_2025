#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"


class Ball
{
private:
	float x;
	float y;
	float radius;
	float vx;
	float vy;
	sf::CircleShape shape;

public:
	Ball(float start_x, float start_y, float start_radius, float start_vx, float start_vy)
	{
		x = start_x;
		y = start_y;
		radius = start_radius;
		vx = start_vx;
		vy = start_vy;

		shape.setRadius(start_radius);
		shape.setOrigin(sf::Vector2f{ start_radius,start_radius });
		shape.setPosition(sf::Vector2f{ start_x,start_y });
		shape.setFillColor(sf::Color(255, 207, 241));
	};

	void move()
	{
		x = x + vx;
		y = y + vy;
		shape.setPosition(sf::Vector2f{ x,y });

	};

	void bounceX()
	{
		vx = -vx;
	};

	void bounceY()
	{
		vy = -vy;
	};

	void collideWalls(float width, float height)
	{
		if (x - radius <= 0 || x + radius >= width)
		{
			bounceX();
		};

		if (y - radius <= 0)
		{
			bounceY();
		}
		
	};
	
	bool collidePaddle(const Paddle& pal)
	{
		float pX = pal.getX();
		float pY = pal.getY();
		float pW = pal.getW();
		float pH = pal.getH();

		if (x >= pX - pW / 2 && x <= pX + pW / 2 && y + radius >= pY - pH / 2 && y - radius < pY - pH / 2)
		{
			vy = -std::abs(vy);
			y = (pY - pH / 2) - radius;
			shape.setPosition(sf::Vector2f{ x,y });
			return true;
		}
		return false;
		
	}

	void draw(sf::RenderTarget& target)
	{
		target.draw(shape);
	};

	float getX() const { return x; }
	float getY() const { return y; }
	float getVx() const { return vx; }
	float getVy() const { return vy; }
	float getRadius() const { return radius; }
	
	sf::FloatRect getGlobalBounds() const {
		return shape.getGlobalBounds();
	};
};