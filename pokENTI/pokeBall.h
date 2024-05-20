#ifndef POKEBALL_H
#define POKEBALL_H

class PokeBall {
private:
    int x;
    int y;
public:
    PokeBall(int initialX, int initialY);
    PokeBall();

    int GetX();
    int GetY();
};

#endif