#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>



struct animation_right {
	int iterator{ 0 };
	int iterator2{ 0 };
	int iterator3{ 0 };
	int iterator4{ 0 };
	void move_down(sf::Sprite &sprite) {
		iterator2 = 0;
		iterator3 = 0;
		iterator4 = 0;
		if (iterator > 3) {
			iterator = 0;
		}
		if (iterator == 0) {
			sprite.setTextureRect(sf::IntRect(0, 0, 30, 43));
		}
		if (iterator == 1) {
			sprite.setTextureRect(sf::IntRect(32, 0, 30, 43));
		}
		if (iterator == 2) {
			sprite.setTextureRect(sf::IntRect(64, 0, 30, 43));
		}
		if (iterator == 3) {
			sprite.setTextureRect(sf::IntRect(96, 0, 30, 43));
		}
		++iterator;
	}
	void move_left(sf::Sprite &sprite) {
		iterator = 0;
		iterator3 = 0;
		iterator4 = 0;
		if (iterator2 > 3) {
			iterator2 = 0;
		}
		if (iterator2 == 0) {
			sprite.setTextureRect(sf::IntRect(0, 49, 30, 43));
		}
		if (iterator2 == 1) {
			sprite.setTextureRect(sf::IntRect(32, 49, 30, 43));
		}
		if (iterator2 == 2) {
			sprite.setTextureRect(sf::IntRect(64, 49, 30, 43));
		}
		if (iterator2 == 3) {
			sprite.setTextureRect(sf::IntRect(96, 49, 30, 43));
		}
		++iterator2;
	}

	void move_right(sf::Sprite &sprite) {
		iterator = 0;
		iterator2 = 0;
		iterator4 = 0;
		if (iterator3 > 3) {
			iterator3 = 0;
		}
		if (iterator3 == 0) {
			sprite.setTextureRect(sf::IntRect(0, 98, 30, 45));
		}
		if (iterator3 == 1) {
			sprite.setTextureRect(sf::IntRect(32, 98, 30, 45));
		}
		if (iterator3 == 2) {
			sprite.setTextureRect(sf::IntRect(64, 98, 30, 45));
		}
		if (iterator3 == 3) {
			sprite.setTextureRect(sf::IntRect(96, 98, 30, 45));
		}
		++iterator3;
	}

	void move_up(sf::Sprite &sprite) {
		iterator = 0;
		iterator2 = 0;
		iterator3 = 0;
		if (iterator4 > 3) {
			iterator4 = 0;
		}
		if (iterator4 == 0) {
			sprite.setTextureRect(sf::IntRect(0, 147, 30, 45));
		}
		if (iterator4 == 1) {
			sprite.setTextureRect(sf::IntRect(32, 147, 30, 45));
		}
		if (iterator4 == 2) {
			sprite.setTextureRect(sf::IntRect(64, 147, 30, 45));
		}
		if (iterator4 == 3) {
			sprite.setTextureRect(sf::IntRect(96, 147, 30, 45));
		}
		++iterator4;
	}
};

void npc_movement(sf::Sprite &sprite, animation_right &animation) {
	int random = rand() % 100 + 1;
	if (random == 1) {
		sprite.move(sf::Vector2f(-4, 0));
		animation.move_left(sprite);
		animation.move_left(sprite);
	}
	if (random == 2) {
		sprite.move(sf::Vector2f(4, 0));
		animation.move_right(sprite);
		animation.move_right(sprite);
	}
	if (random == 3) {
		sprite.move(sf::Vector2f(0, 4));
		animation.move_down(sprite);
		animation.move_down(sprite);
	}
	if (random == 4) {
		sprite.move(sf::Vector2f(0, -4));
		animation.move_up(sprite);
		animation.move_up(sprite);
	}
}

