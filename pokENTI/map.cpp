#include "map.h"
#include "random"

Map::Map() {
    mapWidth = 0;
    mapHeight = 0;
    zones_unlocked = new bool[4];
    pokemonInPuebloPaleta = 0;
    requiredPokemonForBosque = 0;
    pokemonInBosque = 0;
    pokemonRequiredForCuevaCeleste = 0;

    // Asignación de memoria para el mapa
    map = new char* [mapWidth];
    for (int i = 0; i < mapWidth; ++i) { map[i] = new char[mapHeight]; }
}

Map::~Map() {
    // Map cleaning
    for (int i = 0; i < mapWidth; ++i) { delete[] map[i]; }
    delete[] map;

    // Zones cleaning
    delete[] zones_unlocked;
}

void Map::LoadMapSettings(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;

        // Dimensiones del mapa
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char delimiter;
            iss >> mapWidth >> delimiter >> mapHeight;
            map = new char* [mapWidth];
            for (int i = 0; i < mapWidth; i++) { map[i] = new char[mapHeight]; }
        }

        // Pokémon en Pueblo Paleta
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char delimiter;
            iss >> pokemonInPuebloPaleta >> delimiter >> requiredPokemonForBosque;
        }

        // Pokémon en el Bosque
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char delimiter;
            iss >> pokemonInBosque >> delimiter >> pokemonRequiredForCuevaCeleste;
        }
        file.close();
    }
    else { std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl; }
}

void Map::UnlockZone(int zone) {
    if (zone >= 0 && zone < 4) { zones_unlocked[zone] = true; }
}

bool Map::IsZoneUnlocked(int p_zone) {
    if (p_zone >= 0 && p_zone < 4) { return zones_unlocked[p_zone]; }
    return false;
}

char Map::GetCharAt(int x, int y) {
    if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) { return map[x][y]; }
    return ',';
}

void Map::SetCharAt(int x, int y, char newChar) { map[x][y] = newChar; }

void Map::PrintView(Player& player) {
    const int player_x = player.GetX();
    const int player_y = player.GetY();

    std::cout << "Ancho: " << mapWidth << ", Alto: " << mapHeight << std::endl;
    std::cout << "Pokemons en Pueblo Paleta: " << pokemonInPuebloPaleta
        << ", Pokemons requeridos para desbloquear la siguiente zona: " << requiredPokemonForBosque << std::endl;
    std::cout << "Pokemons en el Bosque: " << pokemonInBosque
        << ", Pokemons requeridos para desbloquear la siguiente zona: " << pokemonRequiredForCuevaCeleste << std::endl;

    // Imprimir mapa
    for (int i = player_x - regionSize; i < player_x + regionSize; i++) {
        for (int j = player_y - regionSize; j < player_y + regionSize; j++) { std::cout << GetCharAt(i, j); }
        std::cout << std::endl;
    }
}

void Map::generateMap(Player& player) {
    const int player_x = player.GetX();
    const int player_y = player.GetY();

    const int quadrantWidth = mapWidth / 2;
    const int quadrantHeight = mapHeight / 2;

    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) { // Map borders
            if (i == 0 || i == mapWidth - 1 || i == quadrantWidth ||
                j == 0 || j == mapHeight - 1 || j == quadrantHeight) {
                map[i][j] = 'X';
            }
            else if (i == player_y && j == player_x) { map[i][j] = 'v'; }
            else { map[i][j] = '.'; }
        }
    }

    SpawnPokemon(0);
}

void Map::SpawnPokemon(int p_zone) {
    if (!IsZoneUnlocked(p_zone)) { return; }

    int xOffset = 0;
    int yOffset = 0;
    switch (p_zone)
    {
    default: break;
    case 1: {
        xOffset = 1;
        yOffset = 0;
        break;
    }
    case 2: {
        xOffset = 0;
        yOffset = 1;
        break;
    }
    case 3: {
        xOffset = 1;
        yOffset = 1;
        break;
    }
    }

    bool hasSpawned = false;
    int xPos = 0;
    int yPos = 0;
    while (!hasSpawned) {
        xPos = rand() % regionSize + (regionSize * xOffset);
        yPos = rand() % regionSize + (regionSize * yOffset);

        if (GetCharAt(xPos, yPos) == '.') {
            SetCharAt(xPos, yPos, 'P');
            hasSpawned = true;
        }
    }
}

int Map::getWidth() { return mapWidth; }
int Map::getHeight() { return mapHeight; }