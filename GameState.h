#pragma once
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

struct BlockData
{
	float x, y;
	int hp;
};

class GameState
{
private:
	sf::Vector2f paddlePosition;
	sf::Vector2f ballPosition;
	sf::Vector2f ballVelocity;
	std::vector<BlockData> blocks;
public:
	void capture(const Paddle& pal, const Ball& pilka, const std::vector<Brick>& bloki)
	{
		paddlePosition = { pal.getX(), pal.getY() };
		ballPosition = { pilka.getX(), pilka.getY() };
		ballVelocity = { pilka.getVx(), pilka.getVy() };

		blocks.clear();
		for (const auto& brick : bloki)
		{
			// Zapisujemy tylko te bloki, które nie są zniszczone
			if (!brick.checkDestroy())
			{
				// Brick dziedziczy po RectangleShape, więc ma getPosition()
				blocks.push_back({ brick.getPosition().x, brick.getPosition().y, brick.getHP()});
			}
		}
	}

	bool saveToFile(const std::string& filename)
	{
		std::ofstream file(filename);
		if (!file.is_open()) return false;

		file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";

		file << "BALL " <<ballPosition.x << " " << ballPosition.y << " "
            << ballVelocity.x << " " << ballVelocity.y << "\n";

        // Format: BLOCKS_COUNT n
        file << "BLOCKS_COUNT " << blocks.size() << "\n";

        // Lista bloków
        for (const auto& b : blocks)
        {
            file << b.x << " " << b.y << " " << b.hp << "\n";
        }

        file.close();
        std::cout << "[SYSTEM] Gra zapisana pomyslnie!\n";
        return true;
    }

    // ZADANIE 3: Odczyt z pliku
    bool loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cout << "[BLAD] Nie znaleziono pliku zapisu!\n";
            return false;
        }

        std::string label;

        // Wczytaj Paletkę
        if (!(file >> label >> paddlePosition.x >> paddlePosition.y)) return false;

        // Wczytaj Piłkę
        if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y)) return false;

        // Wczytaj Bloki
        int count;
        if (!(file >> label >> count)) return false;

        blocks.clear();
        for (int i = 0; i < count; i++)
        {
            float bx, by;
            int bhp;
            file >> bx >> by >> bhp;
            blocks.push_back({ bx, by, bhp });
        }

        file.close();
        std::cout << "[SYSTEM] Gra wczytana!\n";
        return true;
    }

    // ZADANIE 3: Aplikowanie stanu do gry
    void apply(Paddle& pal, Ball& pilka, std::vector<Brick>& blokiRef)
    {
        // 1. Przywróć paletkę
        pal.setPosition(paddlePosition.x, paddlePosition.y);

        // 2. Przywróć piłkę
        pilka.setPosition(ballPosition.x, ballPosition.y, ballVelocity.x, ballVelocity.y);

        // 3. Odtwórz bloki
        blokiRef.clear();

        // Obliczamy rozmiar bloku tak jak w Game.h (lub hardcodujemy jeśli stały)
        // W Game.h: width=640, col=6. (640 - (5*2))/6 ≈ 105.f
        float rozmiar_bloku_x = (640.f - (6 - 1) * 2.f) / 6;
        float rozmiar_bloku_y = 25.f;
        sf::Vector2f size{ rozmiar_bloku_x, rozmiar_bloku_y };

        for (const auto& data : blocks)
        {
            // Tworzymy nowy blok w miejscu wczytanym z pliku
            blokiRef.emplace_back(sf::Vector2f{ data.x, data.y }, size, data.hp);
        };
    }

};