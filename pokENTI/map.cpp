#include "map.h"

Map::Map() : mapWidth(0), mapHeight(0), pokemonInPuebloPaleta(0), requiredPokemonForBosque(0),
pokemonInBosque(0), pokemonRequiredForCuevaCeleste(0), pikachuPower(0), healthPokemons(0), healthMewtwo(0), minTimeMovePokemon(0), 
maxTimeMovePokemon(0), map(nullptr), zones_unlocked(new bool[4] {true, false, false, false}), MAX_POKEBALLS(1), currentPokeBallsAmount(0){}

Map::~Map() {
    delete[] mapPokeList;
    //delete[] pokeballList; //Por algún motivo este puntero corrompe la memoria en heap al llamarse
    delete[] zones_unlocked;

    for (int i = 0; i < mapWidth; ++i) { delete[] map[i]; }
    delete[] map;
}

void Map::LoadMapSettings(const std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;

        char delimiter;
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            
            iss >> mapWidth >> delimiter >> mapHeight;
            map = new CELL* [mapWidth];
            for (int i = 0; i < mapWidth; i++) { map[i] = new CELL[mapHeight]; }
        }

        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> pokemonInPuebloPaleta >> delimiter >> requiredPokemonForBosque;
        }

        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> pokemonInBosque >> delimiter >> pokemonRequiredForCuevaCeleste;
        }

        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> pikachuPower;
        }

        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> healthPokemons >> delimiter >> healthMewtwo;
        }

        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> minTimeMovePokemon >> delimiter >> maxTimeMovePokemon;
        }

        file.close();

        pokeballList = new PokeBall[MAX_POKEBALLS];
        MAX_POKEMON_AMOUNT = pokemonInBosque + pokemonInPuebloPaleta;
        mapPokeList = new Pokemon[MAX_POKEMON_AMOUNT];
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
            SetCellTypeAt(i, mapHeight / 2, CELL::EMPTY); 
        }
        zones_unlocked[1] = true; 
    }
    else if (!IsZoneUnlocked(2) && player.PokemonAmount() >= pokemonRequiredForCuevaCeleste) { 
        for (int i = mapHeight / 2 + 1; i < mapHeight -1; i++) {
            SetCellTypeAt(mapWidth / 2, i, CELL::EMPTY); 
        }
        zones_unlocked[2] = true; 
    }
}

char Map::CellToChar(CELL p_cellType, char p_playerDir) {
    char result = '?';
    switch (p_cellType)
    {
    case CELL::INVALID:
        result = ',';
        break;
    case CELL::EMPTY:
        result = '.';
        break;
    case CELL::WALL:
        result = 'X';
        break;
    case CELL::POKEMON:
        result = 'P';
        break;
    case CELL::MEWTWO:
        result = 'M';
        break;
    case CELL::POKEBALL:
        result = 'O';
        break;
    case CELL::PLAYER:
        result = p_playerDir;
        break;
    default:
        result = '?';
        break;
    }
    return result;
}

CELL Map::GetCellType(int p_x, int p_y) {
    if (p_x >= 0 && p_x < mapWidth && p_y >= 0 && p_y < mapHeight) { return map[p_x][p_y]; }
    return CELL::INVALID;
}
void Map::SetCellTypeAt(int p_x, int p_y, CELL p_newCellType) { map[p_x][p_y] = p_newCellType; }

void Map::PrintView(Player& p_player) {
    const int player_x = p_player.GetX();
    const int player_y = p_player.GetY();

    system("cls");

    std::cout << "------------------------" << std::endl;
    std::cout << "Ash pokemons -> " << p_player.PokemonAmount() << "  " << "Ash pokeBalls -> " << p_player.PokeBallAmount() << std::endl;
    std::cout << "Current Region -> " << GetCurrentRegion(p_player.GetX(), p_player.GetY()) << std::endl;

    if (GetCurrentRegion(p_player.GetX(), p_player.GetY()) == 0) {
        std::cout << "Current Region -> " <<  "Pueblo Paleta" << std::endl;
    }
    else if (GetCurrentRegion(p_player.GetX(), p_player.GetY()) == 1) {
        std::cout << "Current Region -> " << "The forest" << std::endl;
    }

    for (int i = player_x - regionSize / 2; i < player_x + regionSize / 2; i++) {
        for (int j = player_y - regionSize / 2; j < player_y + regionSize / 2; j++) {
            const char mapChar = CellToChar(GetCellType(i, j), p_player.GetDirection());
            std::cout << mapChar;
        }
        std::cout << std::endl;
    }

    if (!IsZoneUnlocked(1)) {
        std::cout << requiredPokemonForBosque - p_player.PokemonAmount()
            << " left to unlock the forest" << std::endl;
    }
    else if (!IsZoneUnlocked(2)) {
        std::cout << pokemonRequiredForCuevaCeleste - p_player.PokemonAmount()
            << " left to unlock celest cave" << std::endl;
    }

    std::cout << "------------------------";
}

void Map::generateMap(Player& p_player) {
    const int player_x = p_player.GetX();
    const int player_y = p_player.GetY();
    const int mewtwoX = 10;
    const int mewtwoY = 10;

    const int quadrantWidth = mapWidth / 2;
    const int quadrantHeight = mapHeight / 2;

    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            if (i == 0 || i == mapWidth - 1 || i == quadrantWidth ||
                j == 0 || j == mapHeight - 1 || j == quadrantHeight) {
                map[i][j] = CELL::WALL;
            }
            else if (i == player_y && j == player_x) { map[i][j] = CELL::PLAYER; }
            else { map[i][j] = CELL::EMPTY; }
        }
    }

    mewTwo = Pokemon(mewtwoX, mewtwoY, healthMewtwo);
    SetCellTypeAt(mewtwoX, mewtwoY, CELL::MEWTWO);

    for (int i = 0; i < pokemonInPuebloPaleta + pokemonInBosque; i++) {
        if (i < pokemonInPuebloPaleta) { SpawnPokemon(0, i); }
        else { SpawnPokemon(1, i); }
    }

    SpawnPokeball(0);
    SpawnPokeball(1);
}

std::string Map::GetMapView(Player& p_player) {
    const int player_x = p_player.GetX();
    const int player_y = p_player.GetY();
    const int p_regionSize = regionSize;

    std::string mapView = "";
    for (int i = player_x - p_regionSize / 2; i < player_x + p_regionSize / 2; i++) {
        for (int j = player_y - p_regionSize / 2; j < player_y + p_regionSize / 2; j++) {
            if (i >= 0 && i < mapWidth && j >= 0 && j < mapHeight) { 
                mapView += CellToChar(GetCellType(i, j), p_player.GetDirection());
            }
        }
    }
    return mapView;
}

void Map::SpawnPokemon(int p_zone, int p_index) {
    if (currentPokemonAmount >= MAX_POKEMON_AMOUNT) { return; }
    currentPokemonAmount++;

    int xOffset = (p_zone == 2 || p_zone == 3) ? 1 : 0;
    int yOffset = (p_zone == 1 || p_zone == 3) ? 1 : 0;

    bool hasSpawned = false;
    int xPos = 0;
    int yPos = 0;
    while (!hasSpawned) {
        xPos = rand() % (mapWidth / 2) + (mapWidth / 2) * xOffset;
        yPos = rand() % (mapHeight / 2) + (mapHeight / 2) * yOffset;

        if (GetCellType(xPos, yPos) == CELL::EMPTY) {
            mapPokeList[p_index] = Pokemon(xPos, yPos, healthPokemons);
            SetCellTypeAt(xPos, yPos, CELL::POKEMON);
            hasSpawned = true;
        }
    }
}

void Map::RespawnPokemon(Pokemon& p_pokemon) {
    int xOffset = (p_pokemon.GetX() >= mapWidth / 2) ? 1 : 0;
    int yOffset = (p_pokemon.GetY() >= mapHeight / 2) ? 1 : 0;

    //find pokemon on pokemon array to update pos
    int index = 0;
    for (; index < currentPokemonAmount; index++){
        if (mapPokeList[index].GetX() == p_pokemon.GetX() && mapPokeList[index].GetY() == p_pokemon.GetY()) { break; }
    }

    bool hasBeenMoved = false;
    int xPos = 0, yPos = 0;
    while (!hasBeenMoved) {
        xPos = rand() % (mapWidth / 2) + (mapWidth / 2) * xOffset;
        yPos = rand() % (mapHeight / 2) + (mapHeight / 2) * yOffset;

        if (GetCellType(xPos, yPos) == CELL::EMPTY) {
            map[mapPokeList[index].GetX()][mapPokeList[index].GetY()] = CELL::EMPTY;
            mapPokeList[index].Move(xPos, yPos);
            map[mapPokeList[index].GetX()][mapPokeList[index].GetY()] = CELL::POKEMON;
            hasBeenMoved = true;
        }
    }

    mapPokeList[index].setCurrentHealth(healthPokemons);
}


bool Map::AttemptCapture(Player& p_ash, Pokemon& p_pokemon) {
    if (p_ash.PokeBallAmount() <= 0) { return false; }

    p_ash.UsePokeBall();

    float maxHealth = static_cast<float>(healthPokemons);
    float currentHealth = static_cast<float>(p_pokemon.GetCurrentHealth());
    float healthRatio = currentHealth / maxHealth;

    float baseProbability = 0.1f;
    float maxProbability = 0.9f;

    float captureProbability = baseProbability + (maxProbability - baseProbability) * (1.0f - healthRatio);

    float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    if (randomValue < captureProbability) { return true; }

    return false;
}

void Map::ApplyDamageToPokemon(Pokemon& p_pokemon) {
    p_pokemon.ReduceHealth(pikachuPower);
}


void Map::UpdatePokemonMovement() {
    for (int i = 0; i < currentPokemonAmount; i++) {
        int pokemonX = mapPokeList[i].GetX();
        int pokemonY = mapPokeList[i].GetY();
        int zone = GetCurrentRegion(pokemonX, pokemonY);

        if (IsZoneUnlocked(zone)) {
            mapPokeList[i].UpdateMoveWaitTime(minTimeMovePokemon, maxTimeMovePokemon, map, mapWidth, mapHeight);
        }
    }
}

void Map::SpawnPokeball(int p_zone) {
    int xOffset = (p_zone == 2 || p_zone == 3) ? 1 : 0;
    int yOffset = (p_zone == 1 || p_zone == 3) ? 1 : 0;

    bool hasSpawned = false;
    int xPos = 0;
    int yPos = 0;
    while (!hasSpawned) {
        xPos = rand() % (mapWidth / 2) + (mapWidth / 2) * xOffset;
        yPos = rand() % (mapHeight / 2) + (mapHeight / 2) * yOffset;

        if (GetCellType(xPos, yPos) == CELL::EMPTY) {
            pokeballList[currentPokeBallsAmount++] = PokeBall(xPos, yPos);
            SetCellTypeAt(xPos,yPos, CELL::POKEBALL);
            hasSpawned = true;
        }
    }
}

int Map::GetCurrentRegion(int p_x, int p_y) {
    if (p_x < mapWidth / 2) {
        if (p_y < mapHeight / 2) { return 0; }
        return 1;
    }
    else if (p_y < mapHeight / 2) { return 3; }
    return 2;
}


Pokemon& Map::GetPokemonInRange(Player& p_player) {
    for (int i = p_player.GetX() - 1; i < p_player.GetX() + 2; i++) {
        for (int j = p_player.GetY() - 1; j < p_player.GetY() + 2; j++) {

            if (mewTwo.GetX() == i && mewTwo.GetY() == j) { return mewTwo; }

            if (i > -1 && i<mapWidth && j>-1 && j < mapHeight && map[i][j] == CELL::POKEMON) {
                for (int k = 0; k < currentPokemonAmount; k++)
                {
                    if (mapPokeList[k].GetX() == i && mapPokeList[k].GetY() == j) { return mapPokeList[k]; }

                }
            }
        }
    }


    static Pokemon emptyPokemon(-1, -1, 0);
    return emptyPokemon;
}

PokeBall Map::GetPokeBallIntRange(Player& p_player) {
    for (int i = p_player.GetX() - 1; i <= p_player.GetX() + 1; i++) {
        for (int j = p_player.GetY() - 1; j <= p_player.GetY() + 1; j++) {
            if (i >= 0 && i < mapWidth && j >= 0 && j < mapHeight && map[i][j] == CELL::POKEBALL) {
                return PokeBall(i, j);
            }
        }
    }

    return PokeBall(-1, -1);
}

int Map::getWidth() { return mapWidth; }
int Map::getHeight() { return mapHeight; }
int Map::getCurrentPokemonAmount() { return currentPokemonAmount; }
int Map::getPokemonMaxHealth() { return healthPokemons; }
int Map::getMewtwoMaxHealth() { return healthMewtwo; }

void Map::setCurrentPokemonAmount(int p_currentPokemonAmount) { currentPokemonAmount = p_currentPokemonAmount; }