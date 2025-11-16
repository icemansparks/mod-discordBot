#include "CreatureKillNotifier.h"
#include "DiscordLocale.h"

// Constructor for the CreatureKillNotifier class
CreatureKillNotifier::CreatureKillNotifier() : PlayerScript("CreatureKillNotifier") { }

// Function to handle creature kills
void CreatureKillNotifier::OnPlayerCreatureKill(Player* killer, Creature* creature)
{
    // Get the configuration instance
    const DiscordBotConfig& config = DiscordBotConfig::getInstance();

    // Check if the module is enabled and the webhook URL is set
    if (!config.isEnabled() || config.getPlayerWebhookURL().empty())
        return;

    // Check if the killer's account is allowed to trigger notifications
    if (!IsAccountAllowed(killer, config.getAllowedAccounts()))
        return;

    // Ensure the killer and creature are valid
    if (!killer || !creature)
        return;

    // Determine if the creature is a rare spawn or a boss
    bool isRareSpawn = IsRareSpawn(creature);
    bool isBoss = creature->GetCreatureTemplate()->rank == CREATURE_ELITE_WORLDBOSS;

    // Check if notifications for rare spawns or bosses are enabled
    if ((!config.isRareSpawnKillsEnabled() && isRareSpawn) || (!config.isBossKillsEnabled() && isBoss))
        return;

    // Ensure the killer is a player
    if (!killer->IsPlayer())
        return;

    // Get the player instance
    Player* player = killer->ToPlayer();

    // Get the webhook URL from the configuration
    const std::string& webhookURL = config.getPlayerWebhookURL();
    if (webhookURL.empty())
        return;

    // Get killer details
    std::string playerName = player->GetName();
    std::string race = GetRaceName(player->getRace());
    std::string playerClass = GetClassName(player->getClass());
    uint32 level = player->GetLevel();

    // Get creature details
    std::string creatureName = creature->GetName();
    uint32 creatureLevel = creature->GetLevel();

    std::map<std::string, std::string> params = {
        {"PLAYER", playerName},
        {"LEVEL", std::to_string(level)},
        {"RACE", race},
        {"CLASS", playerClass},
        {"CREATURE", creatureName},
        {"CREATURE_LEVEL", std::to_string(creatureLevel)}
};

    // Format the message based on the type of creature killed
    std::string message;
    if (isRareSpawn)
    {
         message = GetLocalizedDiscordMessage("creature_rare_kill", params);
    }
    else if (isBoss)
    {
        message = GetLocalizedDiscordMessage("creature_boss_kill", params);
    }
    else
    {
        // If the creature is neither a rare spawn nor a boss, do not send a message
        return;
    }

    // Send the message to Discord
    DiscordWebhook webhook(webhookURL);
    webhook.send(message);
}
