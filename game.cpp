#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "input.h"

// holds characters' stats
std::vector<charSkills> g_characters;

void startGame()
{
    std::string playerName;
    charSkills player = createCharacter(playerName);
    deleteCharacters();
}

charSkills createCharacter(bool player)
{
    charSkills newCharacter = new skill[SKILLS_COUNT + 1];
    newCharacter[ID] = g_characters.size();
    g_characters.push_back(newCharacter);

    // if (player)
        // createPlayer(newCharacter);
    // else
        // createMonster(newCharacter);

    return newCharacter;
}

charSkills createCharacter(std::string & playerName)
{
    playerName = getPlayerName();
    return createCharacter(true);
}

void deleteCharacters()
{
    charSkills toBeDeleted;
    while (!g_characters.empty())
    {
        toBeDeleted = g_characters.back();
        g_characters.pop_back();
        delete[] toBeDeleted;
    }
}

std::string getPlayerName()
{
    using std::cout;

    cout << "Enter player's name: ";
    std::string name = readString();
    cout << std::endl;

    return name;
}
