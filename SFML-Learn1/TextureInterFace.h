#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

enum move_enum;

class TextureUI {
private:
	sf::Texture texture;
public:
	sf::Sprite sprite;
public:
	TextureUI(std::string loadTexture = "Sprites/Character3.png") {
		if (!texture.loadFromFile(loadTexture)) {
			std::cout << "Load Failed" << std::endl;
			system("pause");
		}
		sprite.setTexture(texture);
	}
	virtual void move(float x, float y, move_enum move) = 0;
};

