#ifndef DISCORD_UTILS_H
#define DISCORD_UTILS_H

#include "Player.h"
#include "Creature.h"
#include "Config.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>

// Utility function to determine if a creature is rare (based on its rank)
inline bool IsRareSpawn(Creature* creature)
{
    return (creature->GetCreatureTemplate()->rank == CREATURE_ELITE_RARE || 
            creature->GetCreatureTemplate()->rank == CREATURE_ELITE_RAREELITE);
}

// Utility function to split a comma-separated string into a vector of integers
inline std::vector<uint32> ParseAccountList(const std::string& accountList)
{
    std::vector<uint32> accountIDs;
    std::stringstream ss(accountList);
    std::string token;

    while (std::getline(ss, token, ','))
    {
        try
        {
            accountIDs.push_back(std::stoi(token));
        }
        catch (...) {} // Ignore invalid numbers
    }
    return accountIDs;
}

// Utility function to check if an account is allowed
inline bool IsAccountAllowed(Player* player, const std::string& allowedAccounts)
{
    // If no accounts are specified, allow all players
    if (allowedAccounts.empty())
        return true;

    // Parse the allowed accounts
    std::vector<uint32> accountIDs = ParseAccountList(allowedAccounts);

    // Check if the player's account ID is in the allowed list
    uint32 playerAccountID = player->GetSession()->GetAccountId();
    return std::find(accountIDs.begin(), accountIDs.end(), playerAccountID) != accountIDs.end();
}

// Utility function to get faction name
inline std::string GetFactionName(uint32 teamId)
{
    return (teamId == ALLIANCE) ? "Alliance" : "Horde";
}

// Utility function to get race name
inline std::string GetRaceName(uint8 raceId)
{
    static std::map<uint8, std::string> raceMap = {
        {RACE_HUMAN, "Human"}, {RACE_ORC, "Orc"}, {RACE_DWARF, "Dwarf"},
        {RACE_NIGHTELF, "Night Elf"}, {RACE_UNDEAD_PLAYER, "Undead"},
        {RACE_TAUREN, "Tauren"}, {RACE_GNOME, "Gnome"}, {RACE_TROLL, "Troll"},
        {RACE_BLOODELF, "Blood Elf"}, {RACE_DRAENEI, "Draenei"}
    };
    return raceMap.count(raceId) ? raceMap[raceId] : "Unknown";
}

// Utility function to get class name
inline std::string GetClassName(uint8 classId)
{
    static std::map<uint8, std::string> classMap = {
        {CLASS_WARRIOR, "Warrior"}, {CLASS_PALADIN, "Paladin"}, {CLASS_HUNTER, "Hunter"},
        {CLASS_ROGUE, "Rogue"}, {CLASS_PRIEST, "Priest"}, {CLASS_DEATH_KNIGHT, "Death Knight"},
        {CLASS_SHAMAN, "Shaman"}, {CLASS_MAGE, "Mage"}, {CLASS_WARLOCK, "Warlock"},
        {CLASS_DRUID, "Druid"}
    };
    return classMap.count(classId) ? classMap[classId] : "Unknown";
}

// Utility function to get class color for Discord messages
inline std::string GetClassColor(uint8 classId)
{
    static std::map<uint8, std::string> classColorMap = {
        {CLASS_WARRIOR, "diff"},       // Red
        {CLASS_PALADIN, "fix"},        // Yellow
        {CLASS_HUNTER, "css"},         // Green
        {CLASS_ROGUE, "yaml"},         // Orange
        {CLASS_PRIEST, "md"},          // White
        {CLASS_DEATH_KNIGHT, "json"},  // Dark Red
        {CLASS_SHAMAN, "ini"},         // Blue
        {CLASS_MAGE, "bash"},          // Light Blue
        {CLASS_WARLOCK, "diff"},       // Purple
        {CLASS_DRUID, "fix"}           // Brown
    };

    return classColorMap.count(classId) ? classColorMap[classId] : "md"; // Default to white
}

#endif // DISCORD_UTILS_H