#ifndef POKEMON_H
#define POKEMON_H

#include "random"
#include "enums.h"

class Pokemon {
private:
    int x;
    int y;
    float moveWaitTime;
public:
    Pokemon(int initialX, int initialY);
    Pokemon();

    int GetX();
    int GetY();
    void Move(int newX, int newY);
    void UpdateMoveWaitTime(int minTime, int maxTime, CELL**& map, int mapWidth, int mapHeight);
};

#endif