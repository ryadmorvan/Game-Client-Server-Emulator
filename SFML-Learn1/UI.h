#pragma once
#include "TextureInterFace.h"


static struct Animation {
	int iterator{ 0 };
	void move_down(sf::Sprite &sprite) {
		++iterator;
		if (iterator > 2) {
			iterator = 0;
		}
		if (iterator == 0) {
			sprite.setTextureRect(sf::IntRect(0, 0, 596, 595));
		}
		if (iterator == 1) {
			sprite.setTextureRect(sf::IntRect(596, 0, 596, 595));
		}
		if (iterator == 2) {
			sprite.setTextureRect(sf::IntRect(1192, 0, 596, 595));
		}
	}
	void move_up(sf::Sprite &sprite) {
		--iterator;
		if (iterator < 0) {
			iterator = 2;
		}
		if (iterator == 0) {
			sprite.setTextureRect(sf::IntRect(0, 0, 596, 595));
		}
		if (iterator == 1) {
			sprite.setTextureRect(sf::IntRect(596, 0, 596, 595));
		}
		if (iterator == 2) {
			sprite.setTextureRect(sf::IntRect(1192, 0, 596, 595));
		}
	}

	int getIterator() {
		return iterator;
	}
};


class GameInterface : public TextureUI {
public:
	Animation animation;
public:
	GameInterface(std::string Loadtexture) : TextureUI(Loadtexture) {
		sprite.setTextureRect(sf::IntRect(0, 0, 596, 595));
	}
	virtual void move(float x, float y, move_enum move) override {
		sprite.move(sf::Vector2f(x, y));
	}
	void move_up() {
		animation.move_up(sprite);
	}
	void move_down() {
		animation.move_down(sprite);
	}
};