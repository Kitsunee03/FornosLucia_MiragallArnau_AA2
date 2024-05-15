#include "player.h"

Player::Player(int initialX, int initialY) : x(initialX), y(initialY), direction('v') {
    pokemonAmount = 0;
    pokeList = new Pokemon[pokemonAmount];
    pokeBallAmount = 0;
    pokeBallList = new PokeBall[pokeBallAmount];
}

Player::~Player() {
    delete[] pokeList;
    delete[] pokeBallList;
}

void Player::Move(int p_x, int p_y) {
    x += p_x;
    y += p_y;
}

int Player::GetX() { return x; }
int Player::GetY() { return y; }
int Player::PokemonAmount() { return pokemonAmount; }
int Player::PokeBallAmount() { return pokeBallAmount; }

char Player::GetDirection() { return direction; }
void Player::SetDirection(char dir) { direction = dir; }

void Player::AddPokemon(Pokemon p_pokemon) { pokeList[pokemonAmount++] = p_pokemon; }
void Player::AddPokeBall(PokeBall p_pokeBall) { pokeBallList[pokeBallAmount++] = p_pokeBall; }