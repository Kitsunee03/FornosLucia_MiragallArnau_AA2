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
    moveWaitTime--;
    if (moveWaitTime <= 0) {
        // Generar nuevos desplazamientos aleatorios en el rango [-1, 1] para las coordenadas X y Y
        int deltaX = rand() % 3 - 1; // Número aleatorio en el rango [-1, 1]
        int deltaY = rand() % 3 - 1; // Número aleatorio en el rango [-1, 1]

        // Calcular las nuevas coordenadas
        int newX = x + deltaX;
        int newY = y + deltaY;

        // Verificar si las nuevas coordenadas están dentro de los límites del mapa
        if (newX >= 0 && newX < mapWidth && newY >= 0 && newY < mapHeight) {
            // Verificar si la nueva posición está ocupada por otro objeto en el mapa
            if (map[newX][newY] == '.') {
                // Guardar el carácter original en la posición actual del Pokémon
                char originalChar = map[x][y];
                // Actualizar el mapa: colocar un '.' donde estaba el Pokémon
                map[x][y] = '.';
                // Llama a Move con las coordenadas válidas
                Move(newX, newY);
                // Actualizar el mapa: colocar una 'P' en la nueva posición del Pokémon
                map[newX][newY] = originalChar;
            }
        }

        // Actualizar el tiempo de espera para el próximo movimiento
        moveWaitTime = rand() % (maxTime - minTime + 1) + minTime;
    }
}


int Pokemon::GetX() { return x; }
int Pokemon::GetY() { return y; }