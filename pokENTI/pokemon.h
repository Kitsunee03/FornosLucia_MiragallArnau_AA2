#ifndef POKEMON_H
#define POKEMON_H

class Pokemon {
private:
    int x;
    int y;
public:
    Pokemon(int initialX, int initialY);
    Pokemon();

    int GetX();
    int GetY();
};

#endif