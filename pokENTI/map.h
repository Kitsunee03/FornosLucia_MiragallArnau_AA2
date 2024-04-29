#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Player;

class Map {
private:
    std::vector<std::vector<char>> map;
    int mapWidth, mapHeight;
    std::vector<bool> zones_unlocked;
public:
    Map();
    void LoadMapSettings(const std::string& filename);
    void UnlockZone(int zone);
    bool IsZoneUnlocked(int zone);
    char GetCharAt(int x, int y);
    void SetCharAt(int x, int y, char newChar);
    void PrintView(Player& player);
    void generateMap(Player& player);

    int getWidth();
    int getHeight();
};
#endif 