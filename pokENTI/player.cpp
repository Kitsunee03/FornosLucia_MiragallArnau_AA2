#include "player.h"

Player::Player(int initialX, int initialY) : x(initialX), y(initialY), direction('v') {}

void Player::Move(int p_x, int p_y) {
    x += p_x;
    y += p_y;
}

int Player::GetX() { return x; }
int Player::GetY() { return y; }

char Player::GetDirection() { return direction; }
void Player::SetDirection(char dir) { direction = dir; }