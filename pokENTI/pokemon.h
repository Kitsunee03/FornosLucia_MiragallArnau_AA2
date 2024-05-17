#ifndef POKEMON_H
#define POKEMON_H

#include "random"
#include "enums.h"

class Pokemon {
private:
    int x;
    int y;
    int actualHealth;
    float moveWaitTime;
public:
    Pokemon(int initialX, int initialY);
    Pokemon();

    int GetX();
    int GetY();
    int GetCurrentHealth();
    void setCurrentHealth(int p_currentHealth);
    void Move(int newX, int newY);
    void UpdateMoveWaitTime(int minTime, int maxTime, CELL**& map, int mapWidth, int mapHeight);
};

#endif