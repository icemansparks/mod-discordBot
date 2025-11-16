#include "PlayerEventsNotifier.h"
#include "DiscordLocale.h"

// Constructor for PlayerEventsNotifier
PlayerEventsNotifier::PlayerEventsNotifier() : PlayerScript("PlayerEventsNotifier") {}

// Called when a player logs in
void PlayerEventsNotifier::OnPlayerLogin(Player* player)
{
    const DiscordBotConfig& config = DiscordBotConfig::getInstance();

    if (!config.isEnabled())
        return;

    const std::string& webhookURL = config.getPlayerWebhookURL();
    if (webhookURL.empty())
        return;

    if (!IsAccountAllowed(player, config.getAllowedAccounts()))
        return;

    // Gather player information
    std::string playerName = player->GetName();
    std::map<std::string, std::string> params = { {"PLAYER", playerName} };

    std::string message = GetLocalizedDiscordMessage("player_login", params);

    // Send message to Discord
    DiscordWebhook webhook(webhookURL);
    webhook.send(message);
}

// Called when a player logs out
void PlayerEventsNotifier::OnPlayerLogout(Player* player)
{
    const DiscordBotConfig& config = DiscordBotConfig::getInstance();

    if (!config.isEnabled())
        return;

    if (!IsAccountAllowed(player, config.getAllowedAccounts()))
        return;

    const std::string& webhookURL = config.getPlayerWebhookURL();
    if (webhookURL.empty())
        return;

    std::string playerName = player->GetName();
    std::map<std::string, std::string> params = { {"PLAYER", playerName} };
    std::string message = GetLocalizedDiscordMessage("player_logout", params);

    DiscordWebhook webhook(webhookURL);
    webhook.send(message);
}

// Called when a player levels up
void PlayerEventsNotifier::OnPlayerLevelChanged(Player* player, uint8 oldLevel)
{
    const DiscordBotConfig& config = DiscordBotConfig::getInstance();

    if (!config.isEnabled())
        return;

    if (!IsAccountAllowed(player, config.getAllowedAccounts()))
        return;

    const std::string& webhookURL = config.getPlayerWebhookURL();
    if (webhookURL.empty())
        return;

    // Ensure newLevel is declared before use
    uint8 newLevel = player->GetLevel();

    // Get player details
    std::string playerName = player->GetName();
    std::string race = GetRaceName(player->getRace());
    std::string playerClass = GetClassName(player->getClass());

    std::map<std::string, std::string> params = {
        {"PLAYER", playerName},
        {"LEVEL", std::to_string(newLevel)},
        {"RACE", race},
        {"CLASS", playerClass}
    };

    // Format the message
    std::string message = GetLocalizedDiscordMessage("player_levelup", params);

    // Send to Discord
    DiscordWebhook webhook(webhookURL);
    webhook.send(message);
}
