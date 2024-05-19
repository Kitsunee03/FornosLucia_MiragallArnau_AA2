#include "pokemon.h"

Pokemon::Pokemon(int initialX, int initialY, int p_health) : x(initialX), y(initialY), actualHealth(p_health), moveWaitTime(0) {

}
Pokemon::Pokemon() {
    moveWaitTime = .0f;
	x = 0;
	y = 0;
    actualHealth = 0;
}

void Pokemon::Move(int newX, int newY) {
    x = newX;
    y = newY;
}

void Pokemon::ReduceHealth(int damage) {
    actualHealth -= damage;
    if (actualHealth < 0) { actualHealth = 0; }
}

void Pokemon::UpdateMoveWaitTime(int minTime, int maxTime, CELL**& map, int mapWidth, int mapHeight) {
    moveWaitTime -= 0.1f;
    if (moveWaitTime <= 0) {
        int deltaX = (rand() % 3) - 1;
        int deltaY = (rand() % 3) - 1;

        int newX = x + deltaX;
        int newY = y + deltaY;

        if (newX >= 0 && newX < mapWidth && newY >= 0 && newY < mapHeight) {
            if (map[newX][newY] == CELL::EMPTY) {
                map[x][y] = CELL::EMPTY;
                Move(newX, newY);
                map[x][y] = CELL::POKEMON;
            }
        }

        moveWaitTime = float(rand() % (maxTime - minTime + 1) + minTime);
    }
}

int Pokemon::GetX() { return x; }
int Pokemon::GetY() { return y; }

int Pokemon::GetCurrentHealth() { return actualHealth; }
void Pokemon::setCurrentHealth(int p_currentHealth) { actualHealth = p_currentHealth; }