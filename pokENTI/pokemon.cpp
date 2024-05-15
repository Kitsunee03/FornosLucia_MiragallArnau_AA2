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
        int deltaX = rand() % 3 - 1; // N�mero aleatorio en el rango [-1, 1]
        int deltaY = rand() % 3 - 1; // N�mero aleatorio en el rango [-1, 1]

        // Calcular las nuevas coordenadas
        int newX = x + deltaX;
        int newY = y + deltaY;

        // Verificar si las nuevas coordenadas est�n dentro de los l�mites del mapa
        if (newX >= 0 && newX < mapWidth && newY >= 0 && newY < mapHeight) {
            // Verificar si la nueva posici�n est� ocupada por otro objeto en el mapa
            if (map[newX][newY] == '.') {
                // Guardar el car�cter original en la posici�n actual del Pok�mon
                char originalChar = map[x][y];
                // Actualizar el mapa: colocar un '.' donde estaba el Pok�mon
                map[x][y] = '.';
                // Llama a Move con las coordenadas v�lidas
                Move(newX, newY);
                // Actualizar el mapa: colocar una 'P' en la nueva posici�n del Pok�mon
                map[newX][newY] = originalChar;
            }
        }

        // Actualizar el tiempo de espera para el pr�ximo movimiento
        moveWaitTime = rand() % (maxTime - minTime + 1) + minTime;
    }
}


int Pokemon::GetX() { return x; }
int Pokemon::GetY() { return y; }