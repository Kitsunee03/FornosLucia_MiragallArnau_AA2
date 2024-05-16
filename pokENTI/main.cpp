#include "includes.h"
#include "enums.h"

void movementInput(Player& p_ash, Map& p_map) {
    bool reprint = false;
    if (GetAsyncKeyState(VK_UP) & 0x8000 && p_map.GetCellType(p_ash.GetX() - 1, p_ash.GetY()) == CELL::EMPTY) {
        p_ash.SetDirection('^');
        p_map.SetCellTypeAt(p_ash.GetX(), p_ash.GetY(), CELL::EMPTY);
        p_ash.Move(-1, 0);
        reprint = true;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000 && p_map.GetCellType(p_ash.GetX() + 1, p_ash.GetY()) == CELL::EMPTY) {
        p_ash.SetDirection('v');
        p_map.SetCellTypeAt(p_ash.GetX(), p_ash.GetY(), CELL::EMPTY);
        p_ash.Move(1, 0);
        reprint = true;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && p_map.GetCellType(p_ash.GetX(), p_ash.GetY() - 1) == CELL::EMPTY) {
        p_ash.SetDirection('<');
        p_map.SetCellTypeAt(p_ash.GetX(), p_ash.GetY(), CELL::EMPTY);
        p_ash.Move(0, -1);
        reprint = true;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && p_map.GetCellType(p_ash.GetX(), p_ash.GetY() + 1) == CELL::EMPTY) {
        p_ash.SetDirection('>');
        p_map.SetCellTypeAt(p_ash.GetX(), p_ash.GetY(), CELL::EMPTY);
        p_ash.Move(0, 1);
        reprint = true;
    }

    if (reprint) {
        p_map.SetCellTypeAt(p_ash.GetX(), p_ash.GetY(), CELL::PLAYER);
        p_map.PrintView(p_ash);
        reprint = false;
    }
}

void captureInput(Player& p_ash, Map& p_map) {
    bool reprint = false;
    PokeBall pokeBall = p_map.GetPokeBallIntRange(p_ash);
    if (pokeBall.GetX() != -1) {
        p_ash.AddPokeBall(pokeBall);
        p_map.SetCellTypeAt(pokeBall.GetX(), pokeBall.GetY(), CELL::EMPTY);
        p_map.SpawnPokeball(p_map.GetCurrentRegion(p_ash.GetX(), p_ash.GetY()));
        reprint = true;
    }

    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        if (p_map.GetPokemonInRange(p_ash).GetX() == -1) { return; }

        Pokemon poke = p_map.GetPokemonInRange(p_ash);
        p_ash.AddPokemon(poke);
        p_map.RespawnPokemon(poke);
        reprint = true;
    }

    if (reprint) {
        p_map.ZoneLockUpdate(p_ash);
        p_map.PrintView(p_ash);
        reprint = false;
    }
}

void mainTitleText() {
    std::cout << "      ....      ..                       ..            ..      .                        s       .      " << std::endl;
    std::cout << "    +^\"\"888h. ~\"888h               < .z@8\"`         x88f` `..x88. .>                   :8      @88>    " << std::endl;
    std::cout << "   8X.  ?8888X  8888f         u.    !@88E         :8888   xf`*8888%     u.    u.      .88      %8P     " << std::endl;
    std::cout << "  '888x  8888X  8888~   ...ue888b   '888E   u    :8888f .888  `\"`     x@88k u@88c.   :888ooo    .      " << std::endl;
    std::cout << "  '88888 8888X   \"88x:  888R Y888r   888E u@8NL  88888' X8888. >\"8x  ^\"8888\"\"8888\" -*8888888  .@88u    " << std::endl;
    std::cout << "   `8888 8888X  X88x.   888R I888>   888E`\"88*\"  88888  ?88888< 888>   8888  888R    8888    \''888E`   " << std::endl;
    std::cout << "     `*` 8888X '88888X  888R I888>   888E .dN.   88888   \"88888 \"8%    8888  888R    8888      888E    " << std::endl;
    std::cout << "    ~`...8888X  \"88888  888R I888>   888E~8888   88888 '  `8888>       8888  888R    8888      888E    " << std::endl;
    std::cout << "     x8888888X.   `%8\" u8888cJ888    888E '888&  `8888> %  X88!        8888  888R   .8888Lu=   888E    " << std::endl;
    std::cout << "    '%\"*8888888h.   \"   \"*888*P\"     888E  9888.  `888X  `~\"\"`   :    \"*88*\" 8888\"  ^%888*     888&    " << std::endl;
    std::cout << "    ~    888888888!`      'Y\"      '\"888*\" 4888\"    \"88k.      .~       \"\"   'Y\"      'Y\"      R888\"   " << std::endl;
    std::cout << "         X888^\"\"\"                     \"\"    \"\"        `\"\"*==~~`                                 \"\"     " << std::endl;
    std::cout << "         `88f                                                                                          " << std::endl;
    std::cout << "          88'                                                                                          " << std::endl;
    std::cout << "          88                                                                                           " << std::endl;
    std::cout << "          \"\"                                                                                           " << std::endl;
    std::cout << "|-----------------------------------------------------------------------------------------------------|" << std::endl;
}
void mainTitleMenu(bool p_option) {
    system("cls");
    mainTitleText();
    switch (p_option)
    {
    case false:
        std::cout << "                                          --> Start Game <--\n" << std::endl;
        std::cout << "                                                 Exit" << std::endl;
        break;
    case true:
        std::cout << "                                              Start Game\n" << std::endl;
        std::cout << "                                             --> Exit <--" << std::endl;
        break;
    }
}

int main() {
    srand(time(NULL));

    SCENE currentScene = SCENE::MAIN_MENU;
    Map map;
    map.LoadMapSettings("config.txt");
    Player ash(2, 2);

    map.generateMap(ash);

    const int player_x = ash.GetX();
    const int player_y = ash.GetY();

    std::string currentMapView = map.GetMapView(ash);
    std::string newMapView = "nothing yet";

    bool mainMenuOption = false;
    mainTitleMenu(mainMenuOption);

    bool gameOver = false;
    while (!gameOver) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { gameOver = true; }

        switch (currentScene)
        {
        case SCENE::MAIN_MENU:
            if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_RETURN) & 0x8000) {
                if (mainMenuOption) { gameOver = true; }
                else { 
                    currentScene = SCENE::MAP; 
                    map.PrintView(ash);
                }
            }
            else if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
                mainMenuOption = !mainMenuOption;
                mainTitleMenu(mainMenuOption);
            }
            break;
        case SCENE::MAP:
            movementInput(ash, map);
            captureInput(ash, map);
            map.UpdatePokemonMovement();
   
            newMapView = map.GetMapView(ash);
            if (newMapView != currentMapView) {
                currentMapView = newMapView;
                map.PrintView(ash);
            }

            break;
        case SCENE::COMBAT:
            break;
        case SCENE::END_MENU:
            break;
        default:
            break;
        }

        Sleep(100);
    }

    return 0;
}