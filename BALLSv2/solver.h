#pragma once
#include <cmath>
#include "ball.h"

struct Solver {
	
	float gravity = 1000.0f;
	float ballRadius = 20.0f;
	std::vector<sBall> Balls;

	void addBall(float positionX, float positionY) {
		ballRadius = (rand() % 10 + 5.0f);
		Balls.emplace_back(ballRadius, positionX, positionY);
	}

	void removeBall() {
		if(Balls.size() > 0) Balls.pop_back();
	}

	void update(float deltaTime, int steps) {
		for (int i = 0; i < deltaTime / steps; i++) {
			applyGravity();
			applyConstraint(400.0f);
			solveCollisions();
			updatePositions(deltaTime);
		}
	}

	void updatePositions(float deltaTime) {
		for (auto& ball : Balls) {
			ball.updatePosition(deltaTime);
		}
	}

	void applyGravity() {
		for (auto& ball : Balls) {
			ball.accelerate(0.0f, gravity);
		}
	}

	void applyConstraint(float r) {
		
		const float x = 512;
		const float y = 512;

		for (auto& ball : Balls) {
			const float dstX = ball.positionX - x;
			const float dstY = ball.positionY - y;

			const float distance = sqrt(dstX * dstX + dstY * dstY);
			if (distance > (r - ball.circle.getRadius())) {
				const float n_x = dstX / distance;
				const float n_y = dstY / distance;

				ball.positionX = x + n_x * (r - ball.circle.getRadius());
				ball.positionY = y + n_y * (r - ball.circle.getRadius());
			}

		}
	}

	void solveCollisions() {
		const uint32_t ballCount = Balls.size();
		for (int i = 0; i < ballCount; i++) {
			for (int k = i + 1; k < ballCount; k++) {
				float collisionAxisX = Balls[i].positionX - Balls[k].positionX;
				float collisionAxisY = Balls[i].positionY - Balls[k].positionY;

				float distance = sqrt(collisionAxisX * collisionAxisX + collisionAxisY * collisionAxisY);
				if (distance < Balls[i].circle.getRadius() + Balls[k].circle.getRadius()) {
					float n_x = collisionAxisX / distance;
					float n_y = collisionAxisY / distance;
					float delta = Balls[i].circle.getRadius() + Balls[k].circle.getRadius() - distance;

					Balls[i].positionX += 0.5f * delta * n_x;
					Balls[i].positionY += 0.5f * delta * n_y;

					Balls[k].positionX -= 0.5f * delta * n_x;
					Balls[k].positionY -= 0.5f * delta * n_y;
				}
			}
		}

	}
};


