#include "pokeBall.h"

PokeBall::PokeBall(int initialX, int initialY) : x(initialX), y(initialY) {

}
PokeBall::PokeBall() {
	x = 0;
	y = 0;
}

int PokeBall::GetX() { return x; }
int PokeBall::GetY() { return y; }