#include "includes.h"
#include "enums.h"

SCENE currentScene;
ACTIONS currentAction;

void uiCombatMenu(ACTIONS p_actions, Map& p_map) {
    system("cls");
    std::cout << "  " <<"    ___         __                     ____        __" << std::endl;
    std::cout << "  " <<"   /   |  _____/ /_     _   _______   / __ \\____  / /_____  ____ ___  ____  ____" << std::endl;
    std::cout << "  " <<"  / /| | / ___/ __ \\   | | / / ___/  / /_/ / __ \\/ //_/ _ \\/ __ `__ \\/ __ \\/ __ \\" << std::endl;
    std::cout << "  " <<" / ___ |(__  ) / / /   | |/ (__  )  / ____/ /_/ / ,< /  __/ / / / / / /_/ / / / /" << std::endl;
    std::cout << "  " <<"/_/  |_/____/_/ /_/    |___/____/  /_/    \\____/_/|_|\\___/_/ /_/ /_/\\____/_/ /_/" << std::endl;
    
    std::cout << "\n\n" << std::endl;
    std::cout << "                                    POKEMON" << "    Health: " << "/" << p_map.getPokemonHealth() << std::endl;
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;

    switch (p_actions)
    {
    case ACTIONS::FIGHT:
        std::cout << "                                --> Fight <--\n" << std::endl;
        std::cout << "                                   Capture\n" << std::endl;
        std::cout << "                                     Run" << std::endl;
        break;
    case ACTIONS::CAPTURE:
        std::cout << "                                    Fight\n" << std::endl;
        std::cout << "                                --> Capture <--\n" << std::endl;
        std::cout << "                                     Run" << std::endl;
        break;
    case ACTIONS::RUN:
        std::cout << "                                    Fight\n" << std::endl;
        std::cout << "                                    Capture\n" << std::endl;
        std::cout << "                                  --> Run <--" << std::endl;
        break;
    }
}

void combatOptions(Player& p_ash, Map& p_map) {
    Pokemon poke = p_map.GetPokemonInRange(p_ash);
    switch (currentAction) {
    case ACTIONS::FIGHT:
        // PORQUE NO DA LA VIDA DEL POKEMON
        std::cout << poke.GetCurrentHealth();
        //p_map.ApplyDamageToPokemon(p_map.GetPokemonInRange(p_ash));
        break;
    case ACTIONS::CAPTURE:
        if (p_map.AttemptCapture(p_ash, poke)){
            p_ash.AddPokemon(poke);
            p_map.RespawnPokemon(poke);
            currentScene = SCENE::MAP;
            p_map.PrintView(p_ash);
        }
        break;
    case ACTIONS::RUN:
        currentScene = SCENE::MAP;
        p_map.PrintView(p_ash);
        break;
    }
}

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
        currentScene = SCENE::COMBAT;
        uiCombatMenu(currentAction, p_map);
    }

    if (reprint) {
        p_map.ZoneLockUpdate(p_ash);
        p_map.PrintView(p_ash);
        reprint = false;
    }
}

void mainTitleText() {
    std::cout << "      ....      ..                       ..            ..      .                        s       ." << std::endl;
    std::cout << "    +^\"\"888h. ~\"888h               < .z@8\"`         x88f` `..x88. .>                   :8      @88>" << std::endl;
    std::cout << "   8X.  ?8888X  8888f         u.    !@88E         :8888   xf`*8888%     u.    u.      .88      %8P" << std::endl;
    std::cout << "  '888x  8888X  8888~   ...ue888b   '888E   u    :8888f .888  `\"`     x@88k u@88c.   :888ooo    ." << std::endl;
    std::cout << "  '88888 8888X   \"88x:  888R Y888r   888E u@8NL  88888' X8888. >\"8x  ^\"8888\"\"8888\" -*8888888  .@88u" << std::endl;
    std::cout << "   `8888 8888X  X88x.   888R I888>   888E`\"88*\"  88888  ?88888< 888>   8888  888R    8888    \''888E`" << std::endl;
    std::cout << "     `*` 8888X '88888X  888R I888>   888E .dN.   88888   \"88888 \"8%    8888  888R    8888      888E" << std::endl;
    std::cout << "    ~`...8888X  \"88888  888R I888>   888E~8888   88888 '  `8888>       8888  888R    8888      888E" << std::endl;
    std::cout << "     x8888888X.   `%8\" u8888cJ888    888E '888&  `8888> %  X88!        8888  888R   .8888Lu=   888E" << std::endl;
    std::cout << "    '%\"*8888888h.   \"   \"*888*P\"     888E  9888.  `888X  `~\"\"`   :    \"*88*\" 8888\"  ^%888*     888&" << std::endl;
    std::cout << "    ~    888888888!`      'Y\"      '\"888*\" 4888\"    \"88k.      .~       \"\"   'Y\"      'Y\"      R888\"" << std::endl;
    std::cout << "         X888^\"\"\"                     \"\"    \"\"        `\"\"*==~~`                                 \"\"" << std::endl;
    std::cout << "         `88f" << std::endl;
    std::cout << "          88'" << std::endl;
    std::cout << "          88" << std::endl;
    std::cout << "          \"\"" << std::endl;
    std::cout << "|-----------------------------------------------------------------------------------------------------|" << std::endl;
}
void gameOverText() {
    std::cout << "\n\t      ,-=-.       ______     _" << std::endl;
    std::cout << "\t     /  +  \\     />----->  _|A|_" << std::endl;
    std::cout << "\t     | ~~~ |    // -/- /  |_ S _|" << std::endl;
    std::cout << "\t     |R.I.P|   //  /  /     |H|" << std::endl;
    std::cout << "\t\\vV,,|_____|V,//_____/VvV,v,|_|/,,vhjwv/," << std::endl;
    std::cout << "    -------------------------------------------------\n\n" << std::endl;
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
void gameOverMenu(bool p_option) {
    system("cls");
    gameOverText();
    switch (p_option)
    {
    case false:
        std::cout << "                   --> Play again <--\n" << std::endl;
        std::cout << "                          Exit" << std::endl;
        break;
    case true:
        std::cout << "                       Play again\n" << std::endl;
        std::cout << "                      --> Exit <--" << std::endl;
        break;
    }
}

int main() {
    srand(time(NULL));

    currentScene = SCENE::MAIN_MENU;
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
            if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
                if (currentAction == ACTIONS::FIGHT) { currentAction = ACTIONS::CAPTURE; }
                else if (currentAction == ACTIONS::CAPTURE) { currentAction = ACTIONS::RUN; }
                else if (currentAction == ACTIONS::RUN) { currentAction = ACTIONS::FIGHT; }
                uiCombatMenu(currentAction, map);
            }
            else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                combatOptions(ash, map);
            }
            break;
        case SCENE::END_MENU:
            if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_RETURN) & 0x8000) {
                if (mainMenuOption) { gameOver = true; }
                else {
                    currentScene = SCENE::MAP;
                    map.PrintView(ash);
                }
            }
            else if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
                mainMenuOption = !mainMenuOption;
                gameOverMenu(mainMenuOption);
            }

            break;
        default:
            break;
        }

        Sleep(100);
    }

    return 0;
}