#include "Player.h"
#include <cmath>

Player::Player(double startX, double startY, double startAngle)
        : x(startX), y(startY), angle(startAngle) {}

void Player::moveForward(double distance) {
    x += cos(angle) * distance;
    y += sin(angle) * distance;
}

void Player::moveBackward(double distance) {
    x -= cos(angle) * distance;
    y -= sin(angle) * distance;
}

void Player::turnLeft(double angleDelta) {
    angle -= angleDelta;
}

void Player::turnRight(double angleDelta) {
    angle += angleDelta;
}
