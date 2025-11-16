#include "Config.h"
#include "Log.h"
#include "DiscordBotConfig.h"

// Global configuration variables
bool modDiscordBotEnabled;
std::string modDiscordBotServerName;
std::string modDiscordBotNotificationLanguage;
bool modDiscordBotDebug;
std::string modDiscordBotPlayerWebhookURL;
std::string modDiscordBotServerWebhookURL;
std::string modDiscordBotAllowedAccounts;
bool modDiscordBotEnableRareSpawnKills;
bool modDiscordBotEnableBossKills;

// Load the Discord bot configuration
void LoadDiscordBotConfig()
{
    // Ensure the config manager loads settings from the module config file
    modDiscordBotEnabled = sConfigMgr->GetOption<bool>("Enable", false);
    modDiscordBotServerName = sConfigMgr->GetOption<std::string>("ServerName", "AzerothCore Server");
    modDiscordBotNotificationLanguage = sConfigMgr->GetOption<std::string>("NotificationLanguage", "en");
    modDiscordBotDebug = sConfigMgr->GetOption<bool>("DiscordBotDebug", false);
    modDiscordBotPlayerWebhookURL = sConfigMgr->GetOption<std::string>("PlayerWebhookURL", "");
    modDiscordBotServerWebhookURL = sConfigMgr->GetOption<std::string>("ServerWebhookURL", "");
    modDiscordBotAllowedAccounts = sConfigMgr->GetOption<std::string>("AllowedAccounts", "");
    modDiscordBotEnableRareSpawnKills = sConfigMgr->GetOption<bool>("EnableRareSpawnKills", false);
    modDiscordBotEnableBossKills = sConfigMgr->GetOption<bool>("EnableBossKills", false);

    // Validate the webhook URLs
    if (modDiscordBotPlayerWebhookURL.empty())
    {
        LOG_ERROR("module", "Player webhook URL is not set in the configuration.");
    }
    if (modDiscordBotServerWebhookURL.empty())
    {
        LOG_ERROR("module", "Server webhook URL is not set in the configuration.");
    }

    // Log the loaded config values for debugging
    if (modDiscordBotDebug)
    {
        LOG_INFO("module", "mod-discordBot configuration loaded: Enable={}, PlayerWebhookURL={}, ServerWebhookURL={}, AllowedAccounts={}, EnableRareSpawnKills={}, EnableBossKills={}",
             modDiscordBotEnabled, modDiscordBotPlayerWebhookURL, modDiscordBotServerWebhookURL, modDiscordBotAllowedAccounts, modDiscordBotEnableRareSpawnKills, modDiscordBotEnableBossKills);

    }
}
