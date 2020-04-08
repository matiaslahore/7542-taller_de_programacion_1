#ifndef __MODIFIERLIST_H__
#define __MODIFIERLIST_H__

#include <vector>
#include <map>
#include "Modifier.h"

#define MODIFIER_SIZE 25
#define MODIFIER_STEP 5

class ModifierList {
private:
    std::vector<std::string> types;
    std::map<int, Modifier> modifiers;
    std::map<int, int> distance;
    int N = 1;
    std::string parse(const std::string &str, size_t &pos, const char delim);

public:
    ModifierList();
    explicit ModifierList(std::string str);
    ~ModifierList();
    std::string serialize();
    std::vector<Modifier> getModifiers();
    bool isOnBoost(int posX, int posY);
    void append(int x, int y, std::string type, direction dir);
    void updateDistance();
    void eraseModifier(int i);

    bool isOnModif(int &posX, int &posY, const std::string &type);

    bool isOnHealth(int posX, int posY);

    bool isOnStones(int posX, int posY);

    bool isOnOil(int posX, int posY);

    bool isOnMud(int posX, int posY);
};

#endif
