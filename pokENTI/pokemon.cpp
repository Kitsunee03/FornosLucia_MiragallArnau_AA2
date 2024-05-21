#include "pokemon.h"

Pokemon::Pokemon(int initialX, int initialY, int p_maxHealth) : x(initialX), y(initialY), 
    maxHealth(p_maxHealth), actualHealth(p_maxHealth), moveWaitTime(0) {

}
Pokemon::Pokemon() {
    moveWaitTime = .0f;
	x = -1;
	y = -1;
    actualHealth = 0;
    maxHealth = 0;
}

void Pokemon::Move(int newX, int newY) {
    x = newX;
    y = newY;
}

void Pokemon::ReduceHealth(int damage) {
    actualHealth -= damage;
    if (actualHealth < 0) { actualHealth = 0; }
}

void Pokemon::UpdateMoveWaitTime(int p_minTime, int p_maxTime, CELL**& p_map, int p_mapWidth, int p_mapHeight, int p_zone) {
    moveWaitTime -= 0.1f;
    if (moveWaitTime <= 0) {
        int xOffset = (p_zone == 2 || p_zone == 3) ? 1 : 0;
        int yOffset = (p_zone == 1 || p_zone == 3) ? 1 : 0;


        int deltaX = (rand() % 3) - 1;
        int deltaY = (rand() % 3) - 1;

        int newX = x + deltaX;
        int newY = y + deltaY;

        bool correctX = (newX < (p_mapWidth / 2) + (p_mapWidth / 2) * xOffset) && (newX >= (p_mapWidth / 2) * xOffset);
        bool correctY = (newY < (p_mapHeight / 2) + (p_mapHeight / 2) * yOffset) && (newY >= (p_mapHeight / 2) * yOffset);

        if (correctX && correctY) {
            if (p_map[newX][newY] == CELL::EMPTY) {
                p_map[x][y] = CELL::EMPTY;
                Move(newX, newY);
                p_map[x][y] = CELL::POKEMON;
            }
        }

        moveWaitTime = float(rand() % (p_maxTime - p_minTime + 1) + p_minTime);
    }
}

int Pokemon::GetX() { return x; }
int Pokemon::GetY() { return y; }

int Pokemon::GetCurrentHealth() { return actualHealth; }
int Pokemon::GetMaxHealth() { return maxHealth; }
void Pokemon::setCurrentHealth(int p_currentHealth) { actualHealth = p_currentHealth; }