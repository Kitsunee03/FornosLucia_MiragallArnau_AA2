#include "includes.h"

void printMap(const std::string& mapView) {
    system("cls");
    std::cout << mapView;
}

void movementInput(Player& p_ash, Map& p_map) {
    bool reprint = false;
    if (GetAsyncKeyState(VK_UP) & 0x8000 && p_map.GetCharAt(p_ash.GetX() - 1, p_ash.GetY()) == '.') {
        p_ash.SetDirection('^');
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '.');
        p_ash.Move(-1, 0);
        reprint = true;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000 && p_map.GetCharAt(p_ash.GetX() + 1, p_ash.GetY()) == '.') {
        p_ash.SetDirection('v');
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '.');
        p_ash.Move(1, 0);
        reprint = true;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && p_map.GetCharAt(p_ash.GetX(), p_ash.GetY() - 1) == '.') {
        p_ash.SetDirection('<');
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '.');
        p_ash.Move(0, -1);
        reprint = true;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && p_map.GetCharAt(p_ash.GetX(), p_ash.GetY() + 1) == '.') {
        p_ash.SetDirection('>');
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '.');
        p_ash.Move(0, 1);
        reprint = true;
    }

    if (reprint) {
        system("cls");
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), p_ash.GetDirection());
        p_map.PrintView(p_ash);
        reprint = false;
    }
}

void captureInput(Player& p_ash, Map& p_map) {
    bool reprint = false;
    PokeBall pokeBall = p_map.GetPokeBallIntRange(p_ash);
    if (pokeBall.GetX() != -1) {
        p_ash.AddPokeBall(pokeBall);
        p_map.SetCharAt(pokeBall.GetX(), pokeBall.GetY(), '.');
        p_map.SpawnPokeball(p_map.GetCurrentRegion(p_ash.GetX(), p_ash.GetY()));
        reprint = true;
    }

    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        if (p_map.GetPokemonInRange(p_ash).GetX() == -1) { return; }

        Pokemon poke = p_map.GetPokemonInRange(p_ash);
        p_ash.AddPokemon(poke);
        p_map.SetCharAt(poke.GetX(), poke.GetY(), '.');
        p_map.setCurrentPokemonAmount( p_map.getCurrentPokemonAmount() - 1 );
        p_map.SpawnPokemon(p_map.GetCurrentRegion(p_ash.GetX(), p_ash.GetY()));

        reprint = true;
    }

    if (reprint) {
        system("cls");
        p_map.ZoneLockUpdate(p_ash);
        p_map.PrintView(p_ash);
        reprint = false;
    }
}

int main() {
    srand(time(NULL));
    Map map;
    map.LoadMapSettings("config.txt");
    Player ash(2,2);

    map.generateMap(ash);
    std::string currentMapView = map.GetMapView(ash); // Obtener la vista inicial del mapa
    printMap(currentMapView); // Imprimir la vista inicial del mapa

    bool gameOver = false;
    while (!gameOver) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { gameOver = true; }

        movementInput(ash, map);
        map.UpdatePokemonMovement();
        captureInput(ash, map);        

        std::string newMapView = map.GetMapView(ash);
        if (newMapView != currentMapView) {
            currentMapView = newMapView;
            printMap(currentMapView); // Imprimir la vista actualizada del mapa
        }

        Sleep(100);
    }

    return 0;
}