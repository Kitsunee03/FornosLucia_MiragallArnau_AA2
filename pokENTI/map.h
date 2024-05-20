#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <iostream>
#include <sstream>
#include "random"
#include "pokemon.h"
#include "pokeBall.h"
#include "player.h"
#include "enums.h"

class Player;

class Map {
private:
    CELL** map;
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
    
    PokeBall* pokeballList = nullptr;
    const int MAX_POKEBALLS = 0;
    int currentPokeBallsAmount = 0;
    int MAX_POKEMON_AMOUNT = 0;
public:
    Map();
    void LoadMapSettings(const std::string filename);
    
    bool IsZoneUnlocked(int zone);
    void ZoneLockUpdate(Player& player);

    char CellToChar(CELL p_cellType, char p_playerChar);
    CELL GetCellType(int x, int y);
    void SetCellTypeAt(int x, int y, CELL newCellType);

    void PrintView(Player& player);
    void generateMap(Player& player);
    std::string GetMapView(Player& p_player);
    int currentPokemonAmount = 0;

    void SpawnPokemon(int p_zone, int p_index);
    void RespawnPokemon(Pokemon& p_pokemon);
    bool AttemptCapture(Player& p_ash, Pokemon& p_pokemon);
    void ApplyDamageToPokemon(Pokemon& p_pokemon);

    void SpawnPokeball(int p_zone);
    void UpdatePokemonMovement();
    int GetCurrentRegion(int x, int y);

    Pokemon& GetPokemonInRange(Player& player);
    PokeBall GetPokeBallIntRange(Player& player);

    int getWidth();
    int getHeight();
    int getCurrentPokemonAmount();
    int getPokemonHealth();

    void setCurrentPokemonAmount(int p_currentPokemonAmount);

    ~Map();
};
#endif 