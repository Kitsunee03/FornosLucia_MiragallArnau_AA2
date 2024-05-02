#include "map.h"

Map::Map() : mapWidth(0), mapHeight(0), pokemonInPuebloPaleta(0), requiredPokemonForBosque(0),
pokemonInBosque(0), pokemonRequiredForCuevaCeleste(0), map(nullptr), zones_unlocked(new bool[4] {true, false, false, false}) {}

Map::~Map() {
    if (map != nullptr) {
        for (int i = 0; i < mapWidth; ++i) { delete[] map[i]; }
        delete[] map;
    }

    delete[] zones_unlocked;
}

void Map::LoadMapSettings(const std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;

        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char delimiter;
            iss >> mapWidth >> delimiter >> mapHeight;
            map = new char* [mapWidth];
            for (int i = 0; i < mapWidth; i++) { map[i] = new char[mapHeight]; }
        }

        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char delimiter;
            iss >> pokemonInPuebloPaleta >> delimiter >> requiredPokemonForBosque;
        }

        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char delimiter;
            iss >> pokemonInBosque >> delimiter >> pokemonRequiredForCuevaCeleste;
        }
        file.close();

        mapPokeList = new Pokemon[pokemonInPuebloPaleta + pokemonInBosque];
    }
    else { std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl; }
}

bool Map::IsZoneUnlocked(int p_zone) {
    if (p_zone >= 0 && p_zone < 4) { return zones_unlocked[p_zone]; }
    return false;
}
void Map::ZoneLockUpdate(Player& player) {
    if (!IsZoneUnlocked(1) && player.PokemonAmount() >= requiredPokemonForBosque) { 
        for (int i = 1; i < mapWidth / 2; i++) {
            SetCharAt(i, mapHeight / 2, '.'); 
        }
        zones_unlocked[1] = true; 
    }
    else if (!IsZoneUnlocked(2) && player.PokemonAmount() >= pokemonRequiredForCuevaCeleste) { 
        for (int i = mapHeight / 2 + 1; i < mapHeight -1; i++) {
            SetCharAt(mapWidth / 2, i, '.'); 
        }
        zones_unlocked[2] = true; 
    }
}

char Map::GetCharAt(int p_x, int p_y) {
    if (p_x >= 0 && p_x < mapWidth && p_y >= 0 && p_y < mapHeight) { return map[p_x][p_y]; }
    return ',';
}
void Map::SetCharAt(int p_x, int p_y, char p_newChar) { map[p_x][p_y] = p_newChar; }

void Map::PrintView(Player& p_player) {
    const int player_x = p_player.GetX();
    const int player_y = p_player.GetY();

    for (int i = player_x - regionSize / 2; i < player_x + regionSize / 2; i++) {
        for (int j = player_y - regionSize / 2; j < player_y + regionSize / 2; j++) { std::cout << GetCharAt(i, j); }
        std::cout << std::endl;
    }

    std::cout << "------------------------" << std::endl;
    std::cout << "Width -> " << mapWidth << " Height -> " << mapHeight << std::endl;

    if (GetCurrentRegion(p_player) == 0) {
        std::cout << "Pokemons at Pueblo Paleta -> " << pokemonInPuebloPaleta << std::endl;
    }
    else if (GetCurrentRegion(p_player) == 1) {
        std::cout << "Pokemons at the forest -> " << pokemonInBosque << std::endl;
    }

    if (!IsZoneUnlocked(1)) {
        std::cout << requiredPokemonForBosque - p_player.PokemonAmount()
            << " left to unlock the forest" << std::endl;
    }
    else if (!IsZoneUnlocked(2)) {
        std::cout << pokemonRequiredForCuevaCeleste - p_player.PokemonAmount()
            << " left to unlock celest cave" << std::endl;
    }

    std::cout << "Ash pokemons -> " << p_player.PokemonAmount() << "\t" << std::endl;
    std::cout << "------------------------";
}

void Map::generateMap(Player& p_player) {
    const int player_x = p_player.GetX();
    const int player_y = p_player.GetY();

    const int quadrantWidth = mapWidth / 2;
    const int quadrantHeight = mapHeight / 2;

    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            if (i == 0 || i == mapWidth - 1 || i == quadrantWidth ||
                j == 0 || j == mapHeight - 1 || j == quadrantHeight) {
                map[i][j] = 'X';
            }
            else if (i == player_y && j == player_x) { map[i][j] = 'v'; }
            else { map[i][j] = '.'; }
        }
    }

    for (int i = 0; i < pokemonInPuebloPaleta; i++) { SpawnPokemon(0); }
    for (int i = 0; i < pokemonInBosque; i++) { SpawnPokemon(1); }
}
void Map::SpawnPokemon(int p_zone) {
    int xOffset = (p_zone == 2 || p_zone == 3) ? 1 : 0;
    int yOffset = (p_zone == 1 || p_zone == 3) ? 1 : 0;

    bool hasSpawned = false;
    int xPos = 0;
    int yPos = 0;
    while (!hasSpawned) {
        xPos = rand() % (mapWidth / 2) + (mapWidth / 2) * xOffset;
        yPos = rand() % (mapHeight / 2) + (mapHeight / 2) * yOffset;

        if (GetCharAt(xPos, yPos) == '.') {
            mapPokeList[currentPokemonAmount++] = Pokemon(xPos, yPos);
            SetCharAt(xPos, yPos, 'P');
            hasSpawned = true;
        }
    }
}

int Map::GetCurrentRegion(Player& p_player) {
    int x = p_player.GetX();
    int y = p_player.GetY();

    if (x < mapWidth / 2) {
        if (y < mapHeight / 2) { return 0; }
        return 1;
    }
    else if (y < mapHeight / 2) { return 3; }
    return 2;
}

Pokemon Map::GetPokemonInRange(Player& p_player) {
    for (int i = p_player.GetX() - 1; i < p_player.GetX() + 2; i++) {
        for (int j = p_player.GetY() - 1; j < p_player.GetY() + 2; j++) {
            if (i > -1 && i<mapWidth && j>-1 && j < mapHeight && map[i][j] == 'P') {
                for (int k = 0; k < currentPokemonAmount; k++)
                {
                    if (mapPokeList[k].GetX() == i && mapPokeList[k].GetY() == j) { return mapPokeList[k]; }
                }
            }
        }
    }

    return Pokemon(-1, -1);
}

int Map::getWidth() { return mapWidth; }
int Map::getHeight() { return mapHeight; }