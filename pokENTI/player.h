#ifndef PLAYER_H
#define PLAYER_H

#include "pokemon.h"

class Player {
private:
    int x, y;
    char direction;
    int pokemonAmount = 0;
    Pokemon* pokeList = nullptr;
public:
    Player(int initialX, int initialY);

    void Move(int dx, int dy);
    int GetX();
    int GetY();
    char GetDirection();
    void SetDirection(char dir);

    void AddPokemon(Pokemon p_pokemon);
    int PokemonAmount();
};
#endif