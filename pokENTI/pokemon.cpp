#include "pokemon.h"

Pokemon::Pokemon(int initialX, int initialY) : x(initialX), y(initialY) {

}
Pokemon::Pokemon() {
	x = 0;
	y = 0;
}

int Pokemon::GetX() { return x; }
int Pokemon::GetY() { return y; }