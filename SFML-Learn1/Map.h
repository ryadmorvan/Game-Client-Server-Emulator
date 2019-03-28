#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include "TextureInterFace.h"


class Map : public TextureUI {
public:
	Map(std::string &&loadTexture) : TextureUI(loadTexture) {
	}
	virtual void move(float x, float y) override {
		sprite.move(sf::Vector2f(x, y));
	}
};