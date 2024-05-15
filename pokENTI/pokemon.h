#ifndef POKEMON_H
#define POKEMON_H

#include "random"

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
    void UpdateMoveWaitTime(int minTime, int maxTime, char** map, int mapWidth, int mapHeight);
};

#endif