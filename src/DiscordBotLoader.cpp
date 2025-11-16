#include "Config.h"
#include "Log.h"
#include "DiscordBotConfig.h"

// Function declarations
void Addmod_discordBotScripts();
void AddPlayerEventsNotifier();
void AddCreatureKillNotifier();
void AddServerStatusNotifier();
void LoadDiscordBotConfig();

// Initialize Discord bot scripts
void Addmod_discordBotScripts()
{
    // Load the configuration for the Discord bot
    LoadDiscordBotConfig(); // Ensure config is loaded before scripts

    // Register the player events notifier
    AddPlayerEventsNotifier();

    // Register the creature kill notifier
    AddCreatureKillNotifier();

    // Register the server status notifier
    AddServerStatusNotifier();

}
