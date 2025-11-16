#ifndef DISCORD_BOT_CONFIG_H
#define DISCORD_BOT_CONFIG_H

#include <string>

// Global configuration variables
extern bool modDiscordBotEnabled;
extern std::string modDiscordBotServerName;
extern std::string modDiscordBotNotificationLanguage;
extern bool modDiscordBotDebug;
extern std::string modDiscordBotPlayerWebhookURL;
extern std::string modDiscordBotServerWebhookURL;
extern std::string modDiscordBotAllowedAccounts;
extern bool modDiscordBotEnableRareSpawnKills;
extern bool modDiscordBotEnableBossKills;

// Class to manage Discord bot configuration
class DiscordBotConfig
{
public:
    static DiscordBotConfig& getInstance()
    {
        static DiscordBotConfig instance;
        return instance;
    }

    bool isEnabled() const { return modDiscordBotEnabled; }
    const std::string& getServerName() const { return modDiscordBotServerName; }
    const std::string& getPlayerWebhookURL() const { return modDiscordBotPlayerWebhookURL; }
    const std::string& getServerWebhookURL() const { return modDiscordBotServerWebhookURL; }
    const std::string& getAllowedAccounts() const { return modDiscordBotAllowedAccounts; }
    bool isRareSpawnKillsEnabled() const { return modDiscordBotEnableRareSpawnKills; }
    bool isBossKillsEnabled() const { return modDiscordBotEnableBossKills; }

private:
    DiscordBotConfig() = default;

    // Prevent copying
    DiscordBotConfig(const DiscordBotConfig&) = delete;
    DiscordBotConfig& operator=(const DiscordBotConfig&) = delete;
};

#endif // DISCORD_BOT_CONFIG_H
