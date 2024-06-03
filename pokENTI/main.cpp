#include "includes.h"
#include "enums.h"

SCENE currentScene;
ACTIONS currentAction;
const int FPS = 8;
bool gameOver = false;
bool victory = false;

void uiCombatMenu(ACTIONS p_actions, Map& p_map, Player& p_ash) {
    system("cls");
    std::cout << "      ___         __                     ____        __" << std::endl;
    std::cout << "     /   |  _____/ /_     _   _______   / __ \\____  / /_____  ____ ___  ____  ____" << std::endl;
    std::cout << "    / /| | / ___/ __ \\   | | / / ___/  / /_/ / __ \\/ //_/ _ \\/ __ `__ \\/ __ \\/ __ \\" << std::endl;
    std::cout << "   / ___ |(__  ) / / /   | |/ (__  )  / ____/ /_/ / ,< /  __/ / / / / / /_/ / / / /" << std::endl;
    std::cout << "  /_/  |_/____/_/ /_/    |___/____/  /_/    \\____/_/|_|\\___/_/ /_/ /_/\\____/_/ /_/" << std::endl;

    std::cout << "\n\n" << std::endl;

    if (p_map.GetPokemonInRange(p_ash).GetMaxHealth() == p_map.getPokemonMaxHealth()) {
        std::cout << "                                        Wild Entimon" << std::endl;
        std::cout << "                                           hp " << p_map.GetPokemonInRange(p_ash).GetCurrentHealth() << "/" << p_map.getPokemonMaxHealth() << std::endl;
    }
    else {
        std::cout << "                                        MEWTWO" << std::endl;
        std::cout << "                                           hp " << p_map.GetPokemonInRange(p_ash).GetCurrentHealth() << "/" << p_map.getMewtwoMaxHealth() << std::endl;
    }

    std::cout << "\n\n\n\n\n                                       VS\n\n\n" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "                       PIKACHU\n\n\n" << std::endl;

    switch (p_actions)
    {
    case ACTIONS::FIGHT:
        std::cout << "                                --> Fight <--\n" << std::endl;
        std::cout << "                                   Capture ("<< p_ash.PokeBallAmount() <<")\n" << std::endl;
        std::cout << "                                     Run" << std::endl;
        break;
    case ACTIONS::CAPTURE:
        std::cout << "                                    Fight\n" << std::endl;
        std::cout << "                               --> Capture (" << p_ash.PokeBallAmount() << "!) <--\n" << std::endl;
        std::cout << "                                     Run" << std::endl;
        break;
    case ACTIONS::RUN:
        std::cout << "                                    Fight\n" << std::endl;
        std::cout << "                                   Capture (" << p_ash.PokeBallAmount() << ")\n" << std::endl;
        std::cout << "                                 --> Run <--" << std::endl;
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
        uiCombatMenu(currentAction, p_map, p_ash);
    }

    if (reprint) {
        p_map.ZoneLockUpdate(p_ash);
        p_map.PrintView(p_ash);
        reprint = false;
    }
}

void mainTitleText(bool p_firstTimeLoading) {
    const float timeBetweenLines = 3000 / 17;
    std::cout << "      ....      ..                       ..            ..      .                        s       ." << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "    +^\"\"888h. ~\"888h               < .z@8\"`         x88f` `..x88. .>                   :8      @88>" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "   8X.  ?8888X  8888f         u.    !@88E         :8888   xf`*8888%     u.    u.      .88      %8P" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "  '888x  8888X  8888~   ...ue888b   '888E   u    :8888f .888  `\"`     x@88k u@88c.   :888ooo    ." << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "  '88888 8888X   \"88x:  888R Y888r   888E u@8NL  88888' X8888. >\"8x  ^\"8888\"\"8888\" -*8888888  .@88u" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "   `8888 8888X  X88x.   888R I888>   888E`\"88*\"  88888  ?88888< 888>   8888  888R    8888    \''888E`" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "     `*` 8888X '88888X  888R I888>   888E .dN.   88888   \"88888 \"8%    8888  888R    8888      888E" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "    ~`...8888X  \"88888  888R I888>   888E~8888   88888 '  `8888>       8888  888R    8888      888E" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "     x8888888X.   `%8\" u8888cJ888    888E '888&  `8888> %  X88!        8888  888R   .8888Lu=   888E" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "    '%\"*8888888h.   \"   \"*888*P\"     888E  9888.  `888X  `~\"\"`   :    \"*88*\" 8888\"  ^%888*     888&" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "    ~    888888888!`      'Y\"      '\"888*\" 4888\"    \"88k.      .~       \"\"   'Y\"      'Y\"      R888\"" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "         X888^\"\"\"                     \"\"    \"\"        `\"\"*==~~`                                 \"\"" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "         `88f" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "          88'" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "          88" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "          \"\"" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "|-----------------------------------------------------------------------------------------------------|" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
}
void gameOverText(bool p_firstTimeLoading) {
    const float timeBetweenLines = 500;
    std::cout << "\n\t      ,-=-.       ______     _" << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    if (victory) {
        std::cout << "\t     /  +  \\     />----->  _|M|_" << std::endl;
        if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
        std::cout << "\t     | ~~~ |    // -/- /  |_ E _|" << std::endl;
        if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
        std::cout << "\t     |R.I.P|   //  /  /     |W|" << std::endl;
    }
    else {
        std::cout << "\t     /  +  \\     />----->  _|A|_" << std::endl;
        if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
        std::cout << "\t     | ~~~ |    // -/- /  |_ S _|" << std::endl;
        if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
        std::cout << "\t     |R.I.P|   //  /  /     |H|" << std::endl;
    }
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "\t\\vV,,|_____|V,//_____/VvV,v,|_|/,,vhjwv/," << std::endl;
    if (p_firstTimeLoading) { Sleep(timeBetweenLines); }
    std::cout << "    -------------------------------------------------" << std::endl;

    if (victory) { std::cout << "  You caught Mewtwo, lived a long life, and died, congrats!!\n\n" << std::endl; }
    else { std::cout << "      Your guts were smashed and eaten by Mewtwo...\n\n" << std::endl; }
}

void mainTitleMenu(bool p_option, bool p_firstTimeLoading) {
    system("cls");
    mainTitleText(p_firstTimeLoading);
    
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
void gameOverMenu(bool p_option, bool p_firstTimeLoading) {
    system("cls");
    gameOverText(p_firstTimeLoading);

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

void combatOptions(Player& p_ash, Map& p_map) {
    Pokemon& poke = p_map.GetPokemonInRange(p_ash);
    switch (currentAction) {
    case ACTIONS::FIGHT:
        p_map.ApplyDamageToPokemon(poke);

        if (poke.GetCurrentHealth() <= 0 && poke.GetMaxHealth() == p_map.getMewtwoMaxHealth()) {
            currentScene = SCENE::END_MENU;              //mewtwo dead
            gameOverMenu(false, true);
        }
        else if (poke.GetCurrentHealth() <= 0) {
            p_map.RespawnPokemon(poke);
            currentScene = SCENE::MAP;
            p_map.ZoneLockUpdate(p_ash);
            p_map.PrintView(p_ash);
        }
        else { uiCombatMenu(currentAction, p_map, p_ash); }
        break;
    case ACTIONS::CAPTURE:
        if (p_map.AttemptCapture(p_ash, poke)) {

            if (poke.GetMaxHealth() == p_map.getMewtwoMaxHealth()) {
                victory = true;                         //mewtwo captured
                currentScene = SCENE::END_MENU; 
                gameOverMenu(false, true);
            }
            else {
                p_ash.AddPokemon(poke);
                p_map.RespawnPokemon(poke);
                currentScene = SCENE::MAP;
                p_map.ZoneLockUpdate(p_ash);
                p_map.PrintView(p_ash);
            }
        }
        else { uiCombatMenu(currentAction, p_map, p_ash); }
        break;
    case ACTIONS::RUN:
        if (poke.GetMaxHealth() == p_map.getMewtwoMaxHealth()) { //you can't run from mewtwo, death
            currentScene = SCENE::END_MENU;
            gameOverMenu(false, true);
        }
        else {
            currentScene = SCENE::MAP;
            p_map.PrintView(p_ash);
        }
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

    std::string currentMapView = map.GetMapView(ash);
    std::string newMapView = "nothing yet";

    bool mainMenuOption = false;
    mainTitleMenu(mainMenuOption, true);

    while (!gameOver) {
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
                mainTitleMenu(mainMenuOption, false);
            }
            break;
        case SCENE::MAP:
            movementInput(ash, map);
            captureInput(ash, map);

            //Testing helpers
            if (GetAsyncKeyState(VK_CONTROL) & 0x8000) { ash.AddPokemon(Pokemon(1, 1, 100)); map.PrintView(ash); map.ZoneLockUpdate(ash);
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                currentScene = SCENE::END_MENU;
                gameOverMenu(false, true);
            }

            map.UpdatePokemonMovement();

            newMapView = map.GetMapView(ash);
            if (newMapView != currentMapView) {
                currentMapView = newMapView;
                map.PrintView(ash);
            }

            break;
        case SCENE::COMBAT:
            //if mewtwo and no pokeballs, die
            if (ash.PokeBallAmount() <= 0 && map.GetPokemonInRange(ash).GetMaxHealth() == map.getMewtwoMaxHealth()) {
                currentScene = SCENE::END_MENU;
                gameOverMenu(false, true);
            }

            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                if (currentAction == ACTIONS::RUN) { currentAction = ACTIONS::CAPTURE; }
                else if (currentAction == ACTIONS::FIGHT) { currentAction = ACTIONS::RUN; }
                else { currentAction = ACTIONS::FIGHT; }
                uiCombatMenu(currentAction, map, ash);
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                if (currentAction == ACTIONS::FIGHT) { currentAction = ACTIONS::CAPTURE; }
                else if (currentAction == ACTIONS::CAPTURE) { currentAction = ACTIONS::RUN; }
                else { currentAction = ACTIONS::FIGHT; }
                uiCombatMenu(currentAction, map, ash);
            }
            else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                combatOptions(ash, map);
            }
            break;
        case SCENE::END_MENU:
            if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_RETURN) & 0x8000) {
                if (mainMenuOption) { gameOver = true; }
                else {
                    ash = Player(2, 2);
                    map.resetMap(ash);

                    currentMapView = map.GetMapView(ash);
                    newMapView = "nothing yet";

                    currentScene = SCENE::MAP;
                    map.PrintView(ash);
                }
            }
            else if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
                mainMenuOption = !mainMenuOption;
                gameOverMenu(mainMenuOption, false);
            }

            break;
        default:
            break;
        }

        Sleep(1000 / FPS);
    }

    ash.freeMemory();
    map.freeMemory();
    return 0;
}