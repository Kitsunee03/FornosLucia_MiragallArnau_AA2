#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int x, y;
    char direction;
public:
    Player(int initialX, int initialY);

    void Move(int dx, int dy);
    int GetX();
    int GetY();
    char GetDirection();
    void SetDirection(char dir);
};
#endif