#ifndef PLAYER_H
#define PLAYER_H

#include "pokemon.h"
#include "pokeBall.h"

class Player {
private:
    int x, y;
    char direction;
    int pokemonAmount = 0;
    Pokemon* pokeList = nullptr;
    int pokeBallAmount = 0;
    PokeBall* pokeBallList = nullptr;
public:
    Player(int initialX, int initialY);
    ~Player();

    void Move(int dx, int dy);
    int GetX();
    int GetY();
    char GetDirection() const;
    void SetDirection(char dir);

    void AddPokemon(Pokemon p_pokemon);    
    int PokemonAmount();

    void AddPokeBall(PokeBall p_pokeBall);
    int PokeBallAmount();
};
#endif