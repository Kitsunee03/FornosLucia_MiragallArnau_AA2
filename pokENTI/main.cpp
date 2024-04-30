#include "includes.h"

void playerMovement(Player& p_ash, Map& p_map) {
    if (GetAsyncKeyState(VK_UP) & 0x8000 && p_map.GetCharAt(p_ash.GetX() - 1, p_ash.GetY()) != 'X') {
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '.');
        p_ash.Move(-1, 0);
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '^');

        p_ash.SetDirection('U');
        system("cls");
        p_map.PrintView(p_ash);
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000 && p_map.GetCharAt(p_ash.GetX() + 1, p_ash.GetY()) != 'X') {
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '.');
        p_ash.Move(1, 0);
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), 'v');

        p_ash.SetDirection('D');
        system("cls");
        p_map.PrintView(p_ash);
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && p_map.GetCharAt(p_ash.GetX(), p_ash.GetY() - 1) != 'X') {
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '.');
        p_ash.Move(0, -1);
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '<');
        p_ash.SetDirection('L');
        system("cls");
        p_map.PrintView(p_ash);
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && p_map.GetCharAt(p_ash.GetX(), p_ash.GetY() + 1) != 'X') {
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '.');
        p_ash.Move(0, 1);
        p_map.SetCharAt(p_ash.GetX(), p_ash.GetY(), '>');
        p_ash.SetDirection('R');
        system("cls");
        p_map.PrintView(p_ash);
    }
}

int main() {
    Map map;

    // Cargar el mapa desde el archivo de configuración
    map.LoadMapSettings("config.txt");
    Player ash(2,2);

    // Mostrar la vista del jugador
    map.generateMap(ash);
    map.PrintView(ash);

    while (true) {
        playerMovement(ash, map);
        Sleep(100);
    }

    return 0;
}