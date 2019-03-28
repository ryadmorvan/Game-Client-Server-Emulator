#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include "TextureInterFace.h"

class Player : public TextureUI {
private:
	sf::Texture texture;
public:
	sf::Sprite sprite;
public:
	Player(std::string &&loadTexture = "Sprites/Character3.png") {
		if (!texture.loadFromFile(loadTexture)) {
			std::cout << "Load Failed" << std::endl;
			system("pause");
		}
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 30, 43));
	}



	Player(const Player &player) {
		this->texture = player.texture;
		this->sprite = player.sprite;
	}
	void operator=(const Player &player) {
		this->texture = player.texture;
		this->sprite = player.sprite;
	}

	void move(float x, float y) {
		sprite.move(sf::Vector2f(x, y));
	}
};