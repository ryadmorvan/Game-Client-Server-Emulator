#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include "TextureInterFace.h"
#include "Movements.h"

enum move_enum {
	LEFT_A, RIGHT_A, UP_A, DOWN_A
};
class Player : public TextureUI {
private:
	animation_right animation;
	sf::Texture texture;
	float x{ 0 }, y{ 0 };
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
	
	float get_x() {
		return x;
	}
	float get_y() {
		return y;
	}

	Player(const Player &player) {
		this->texture = player.texture;
		this->sprite = player.sprite;
	}
	void operator=(const Player &player) {
		this->texture = player.texture;
		this->sprite = player.sprite;
	}

	void move(float x_cord, float y_cord, move_enum move) {
		sprite.move(sf::Vector2f(x_cord, y_cord));
		switch (move) {
		case LEFT_A: {
			animation.move_left(sprite);
			break;
			}
		case RIGHT_A: {
			animation.move_right(sprite);
			break;
			}
		case UP_A: {
			animation.move_up(sprite);
			break;
			}
		case DOWN_A: {
			animation.move_down(sprite);
			break;
			}
		}

		x += x_cord;
		y += y_cord;
	}
};