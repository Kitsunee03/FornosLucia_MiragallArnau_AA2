#ifndef MAP_H
#define MAP_H

#include "includes.h"
#include <fstream>
#include <sstream>

class Player;

class Map {
private:
    char** map;
    int mapWidth = 0;
    int mapHeight = 0;
    bool* zones_unlocked = nullptr;
    int pokemonInPuebloPaleta = 0;
    int requiredPokemonForBosque = 0;
    int pokemonInBosque = 0;
    int pokemonRequiredForCuevaCeleste = 0;
public:
    Map();
    void LoadMapSettings(const std::string& filename);
    void UnlockZone(int zone);
    bool IsZoneUnlocked(int zone);
    char GetCharAt(int x, int y);
    void SetCharAt(int x, int y, char newChar);
    void PrintView(Player& player);
    void generateMap(Player& player);

    int getWidth();
    int getHeight();

    ~Map();
};
#endif 