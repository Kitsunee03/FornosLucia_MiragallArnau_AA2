#include "pokemon.h"

Pokemon::Pokemon(int initialX, int initialY) : x(initialX), y(initialY), moveWaitTime(0) {

}
Pokemon::Pokemon() {
	x = 0;
	y = 0;
}

void Pokemon::Move(int newX, int newY) {
    x = newX;
    y = newY;
}

void Pokemon::UpdateMoveWaitTime(int minTime, int maxTime, char** map, int mapWidth, int mapHeight) {
    moveWaitTime -= 0.1;
    if (moveWaitTime <= 0) {
        int deltaX = (rand() % 3) - 1;
        int deltaY = (rand() % 3) - 1;

        int newX = x + deltaX;
        int newY = y + deltaY;

        if (newX >= 0 && newX < mapWidth && newY >= 0 && newY < mapHeight) {
            if (map[newX][newY] == '.') {
                char originalChar = map[x][y];
                map[x][y] = '.';

                Move(newX, newY);
                map[newX][newY] = originalChar;
            }
        }

        moveWaitTime = rand() % (maxTime - minTime + 1) + minTime;
    }
}

int Pokemon::GetX() { return x; }
int Pokemon::GetY() { return y; }