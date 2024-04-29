#include "map.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <sstream>

Map::Map() {
    // Inicializar el vector de zonas desbloqueadas con 4 elementos, todos en false
    zones_unlocked.resize(4, false);
}

void Map::LoadMapSettings(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;

        // Leer la primera línea para obtener las dimensiones del mapa
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char delimiter;
            if (iss >> mapWidth >> delimiter >> mapHeight) {
                std::cout << "Ancho: " << mapWidth << ", Alto: " << mapHeight << std::endl;
                // Redimensionar el mapa según las dimensiones leídas
                map.resize(mapWidth, std::vector<char>(mapHeight));
            }
        }

        // Leer la segunda línea para obtener información sobre los Pokémon en Pueblo Paleta
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char delimiter;
            int initial_pokemon, required_pokemon;
            if (iss >> initial_pokemon >> delimiter >> required_pokemon) {
                std::cout << "Pokemons en Pueblo Paleta: " << initial_pokemon << ", Pokemons requeridos para desbloquear la siguiente zona: " << required_pokemon << std::endl;
                // Guardar esta información en alguna estructura de datos si es necesario
            }
        }

        // Leer la tercera línea para obtener información sobre los Pokémon en el Bosque
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char delimiter;
            int initial_pokemon, required_pokemon;
            if (iss >> initial_pokemon >> delimiter >> required_pokemon) {
                std::cout << "Pokemons en el Bosque: " << initial_pokemon << ", Pokemons requeridos para desbloquear la siguiente zona: " << required_pokemon << std::endl;
                // Guardar esta información en alguna estructura de datos si es necesario
            }
        }

        file.close();
    }
    else { std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl; }
}


void Map::UnlockZone(int zone) {
    if (zone >= 0 && zone < 4) { zones_unlocked[zone] = true; }
}

bool Map::IsZoneUnlocked(int zone) {
    if (zone >= 0 && zone < 4) { return zones_unlocked[zone]; }
    return false;
}

char Map::GetCharAt(int x, int y) {
    if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) { return map[x][y]; }
    return ',';
}

void Map::SetCharAt(int x, int y, char newChar) {
    map[x][y] = newChar;
}

void Map::PrintView(Player& player) {
    const int player_x = player.GetX();
    const int player_y = player.GetY();

    // Imprimir mapa
    for (int i = player_x - 12; i < player_x + 12; i++) {
        for (int j = player_y - 12; j < player_y + 12; j++) {
            std::cout << GetCharAt(i, j);
        }
        std::cout << std::endl;
    }
}

void Map::generateMap(Player& player) {
    const int player_x = player.GetX();
    const int player_y = player.GetY();

    //ancho -> columna y alto -> fila
    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            if (i == 0 || i == mapWidth - 1 || j == 0 || j == mapHeight - 1) { map[i][j] = 'X'; } //map borders
            else if (i == player_y && j == player_x) { map[i][j] = 'v'; }
            else { map[i][j] = '.'; }
        }
    }
}

int Map::getWidth() { return mapWidth; }
int Map::getHeight() { return mapHeight; }