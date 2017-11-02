#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "character.h"
#include "input.h"
#include "constants.h"

// holds characters' stats
std::vector<charSkills> g_characters;

charSkills createCharacter(bool player)
{
    charSkills newCharacter = new skill[SKILLS_COUNT + 1];
    newCharacter[ID] = g_characters.size();
    for (int i = 1; i < SKILLS_COUNT + 1; i++)
        newCharacter[i] = 0;
    g_characters.push_back(newCharacter);

    if (player)
        buildPlayer(newCharacter, STARTING_PTS_PLAYER);
    else
        buildMonster(newCharacter);

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

void buildPlayer(charSkills player, int availableSkillPoints)
{
    bool finished = false;
    do
    {
        displaySkills(player);
        finished = assignSkill(player, availableSkillPoints);
    } while (!finished);
}

void buildMonster(charSkills monster)
{
    monster[HP] = monster[ID];
    int availableSkillPoints = STARTING_PTS_MONSTER + monster[ID] - 1;
    srand(time(NULL));
    do
    {
        for (int i = 1; i <= SKILLS_COUNT; i++)
        {
            if (!availableSkillPoints)
                break;
            modifySkill(monster[i], availableSkillPoints);
        }
    } while (availableSkillPoints);
}

void displaySkills(const charSkills character)
{
    using std::endl;

    std::cout << "1) NA (Normal Attack): " << character[NA] << endl
              << "2) ND (Normal Defense): " << character[ND] << endl
              << "3) MA (Magic Attack): " << character[MA] << endl
              << "4) MD (Magic Defense): " << character[MD] << endl
              << "5) HP (Health Points): " << character[HP] << endl << endl;
}

bool assignSkill(charSkills character, int & availableSkillPoints)
{
    using std::cout;

    bool finished = false;
    if (!availableSkillPoints && character[HP] > 0
                              && (character[NA] > 0 || character[MA] > 0))
    {
        cout << "All Skill Points have been used.\n"
                "Do you want to finish your build? (y/n)\n";

        const char availableOptions[] = {'y', 'n'};
        char choice = readKey(availableOptions, sizeof availableOptions);
        finished = choice == 'y';
    }

    if (!finished)
    {
        cout << "Available Skill Points: " << availableSkillPoints << std::endl
             << "First, choose a skill to modify.\n";
        int chosenSkill = readNum(1, SKILLS_COUNT);
        cout << "Next, enter the amount (positive or negative).\n";
        int amount = readNum(-character[chosenSkill], availableSkillPoints);

        character[chosenSkill] += amount;
        availableSkillPoints -= amount;
    }

    return finished;
}

void modifySkill(skill & skillToModify, int & availableSkillPoints)
{
    const int MaxSkillModification = 3;
    int amount = rand() % (MaxSkillModification + 1);
    if (amount > availableSkillPoints)
        amount = availableSkillPoints;

    skillToModify += amount;
    availableSkillPoints -= amount;
}

std::string getPlayerName()
{
    using std::cout;

    cout << "Enter your character's name: ";
    std::string name = readString();
    cout << std::endl;

    return name;
}
