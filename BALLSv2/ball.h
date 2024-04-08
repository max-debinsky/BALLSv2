#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct sBall {
	float positionX, positionY;
	float positionX_old, positionY_old;
	float accelerationX, accelerationY;

	sf::CircleShape circle;

	sBall(float radius, float _positionX, float _positionY) {
		positionX = _positionX;
		positionY = _positionY;
		accelerationX = 0;
		accelerationY = 0;
		positionX_old = _positionX;
		positionY_old = _positionY;

		circle.setOrigin(radius, radius);
		circle.setPosition(sf::Vector2f(_positionX, _positionY));
		circle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 40 + 200.0f, 255));
		circle.setRadius(radius);
	}

	void updatePosition(float deltaTime) {
		
		const float velocityX = positionX - positionX_old;
		const float velocityY = positionY - positionY_old;

		positionX_old = positionX;
		positionY_old = positionY;

		positionX = positionX + velocityX + accelerationX * (deltaTime * deltaTime);
		positionY = positionY + velocityY + accelerationY * (deltaTime * deltaTime);

		accelerationX = 0;
		accelerationY = 0;

		circle.setPosition(positionX, positionY);
	}

	void accelerate(float _accelerationX, float _accelerationY) {

		accelerationX += _accelerationX;
		accelerationY += _accelerationY;
	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(circle);
	}
};