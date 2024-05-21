#ifndef POKEMON_H
#define POKEMON_H

#include "random"
#include "enums.h"

class Pokemon {
private:
    int x;
    int y;
    int actualHealth;
    int maxHealth;
    float moveWaitTime;
public:
    Pokemon(int initialX, int initialY, int p_health);
    Pokemon();

    int GetX();
    int GetY();
    int GetCurrentHealth();
    int GetMaxHealth();
    void ReduceHealth(int damage);
    void setCurrentHealth(int p_currentHealth);
    void Move(int newX, int newY);
    void UpdateMoveWaitTime(int minTime, int maxTime, CELL**& map, int mapWidth, int mapHeight, int p_zone);
};

#endif