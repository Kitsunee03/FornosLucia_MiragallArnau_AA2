#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <iostream>
#include <sstream>
#include "random"
#include "pokemon.h"
#include "pokeBall.h"
#include "player.h"

class Player;

class Map {
private:
    char** map;
    int mapWidth = 0;
    int mapHeight = 0;
    int regionSize = 25;
    bool* zones_unlocked = nullptr;
    int pokemonInPuebloPaleta = 0;
    int requiredPokemonForBosque = 0;
    int pokemonInBosque = 0;
    int pokemonRequiredForCuevaCeleste = 0;
    int pikachuPower = 0;
    int healthPokemons = 0;
    int healthMewtwo = 0;
    int minTimeMovePokemon = 0;
    int maxTimeMovePokemon = 0;
    Pokemon* mapPokeList = nullptr;
    int currentPokemonAmount = 0;
    PokeBall* pokeballList = nullptr;
    const int MAX_POKEBALLS = 0;
    int currentPokeBallsAmount = 0;
public:
    Map();
    void LoadMapSettings(const std::string filename);

    bool IsZoneUnlocked(int zone);
    void ZoneLockUpdate(Player& player);

    char GetCharAt(int x, int y);
    void SetCharAt(int x, int y, char newChar);

    void PrintView(Player& player);
    void generateMap(Player& player);

    void SpawnPokemon(int p_zone);
    void SpawnPokeball(int p_zone);
    int GetCurrentRegion(Player& player);

    Pokemon GetPokemonInRange(Player& player);
    PokeBall GetPokeBallIntRange(Player& player);

    int getWidth();
    int getHeight();

    ~Map();
};
#endif 