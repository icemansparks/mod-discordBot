#include "ServerStatusNotifier.h"
#include "GameTime.h"
#include "Log.h"
#include "DiscordBotConfig.h"
#include "DiscordLocale.h"
#include <sstream>

// Helper function to convert seconds to a human-readable time string
std::string secsToTimeString(uint32 seconds);

void ServerStatusNotifier::OnStartup()
{

    if (modDiscordBotDebug)
        LOG_INFO("module", "ServerStatusNotifier::OnStartup triggered");

    const DiscordBotConfig& config = DiscordBotConfig::getInstance();
    if (!config.isEnabled())
        return;

    const std::string& webhookURL = config.getServerWebhookURL();
    if (webhookURL.empty())
        return;

    std::map<std::string, std::string> params = {
        {"SERVER", config.getServerName()}
    };

    std::string message = GetLocalizedDiscordMessage("server_startup", params);

    DiscordWebhook webhook(webhookURL);
    webhook.send(message);
}

void ServerStatusNotifier::OnShutdown()
{

    if (modDiscordBotDebug)
        LOG_INFO("module", "ServerStatusNotifier::OnShutdown triggered");

    const DiscordBotConfig& config = DiscordBotConfig::getInstance();
    if (!config.isEnabled())
        return;

    const std::string& webhookURL = config.getServerWebhookURL();
    if (webhookURL.empty())
        return;

    std::map<std::string, std::string> params = {
        {"SERVER", config.getServerName()}
    };

    std::string message = GetLocalizedDiscordMessage("server_shutdown", params);

    DiscordWebhook webhook(webhookURL);
    webhook.send(message);
}

// Notify server uptime
/*
void ServerStatusNotifier::NotifyServerUptime()
{
    const DiscordBotConfig& config = DiscordBotConfig::getInstance();
    if (!config.isEnabled())
        return;

    const std::string& webhookURL = config.getServerWebhookURL();
    if (webhookURL.empty())
        return;

    std::string message = FormatUptimeMessage();
    DiscordWebhook webhook(webhookURL);
    webhook.send(message);
}
*/

// Notify server error
void ServerStatusNotifier::NotifyServerError(const std::string& errorMessage)
{
    const DiscordBotConfig& config = DiscordBotConfig::getInstance();
    if (!config.isEnabled())
        return;

    const std::string& webhookURL = config.getServerWebhookURL();
    if (webhookURL.empty())
        return;

    std::string message = FormatErrorMessage(errorMessage);
    DiscordWebhook webhook(webhookURL);
    webhook.send(message);
}

// Notify server offline
void ServerStatusNotifier::NotifyServerOffline(int exitCode)
{
    const DiscordBotConfig& config = DiscordBotConfig::getInstance();
    if (!config.isEnabled())
        return;

    const std::string& webhookURL = config.getServerWebhookURL();
    if (webhookURL.empty())
        return;

    std::string message = FormatOfflineMessage(exitCode);
    DiscordWebhook webhook(webhookURL);
    webhook.send(message);
}

// Format uptime message
std::string ServerStatusNotifier::FormatUptimeMessage()
{
    // Get the server's uptime in seconds
    uint32 uptime = static_cast<uint32>(GameTime::GetUptime().count());

    // Convert uptime to a human-readable format
    std::string uptimeStr = secsToTimeString(uptime);
    std::map<std::string, std::string> params = {
        {"SERVER", DiscordBotConfig::getInstance().getServerName()},
        {"UPTIME", uptimeStr}
    };
    return GetLocalizedDiscordMessage("server_uptime", params);
}

// Format error message
std::string ServerStatusNotifier::FormatErrorMessage(const std::string& errorMessage)
{
    std::map<std::string, std::string> params = {
        {"SERVER", DiscordBotConfig::getInstance().getServerName()},
        {"ERROR", errorMessage}
    };
    return GetLocalizedDiscordMessage("server_error", params);
}

// Format offline message
std::string ServerStatusNotifier::FormatOfflineMessage(int exitCode)
{
    std::map<std::string, std::string> params = {
        {"SERVER", DiscordBotConfig::getInstance().getServerName()},
        {"EXITCODE", std::to_string(exitCode)}
    };
    return GetLocalizedDiscordMessage("server_offline", params);
}

// Helper function to convert seconds to a human-readable time string
std::string secsToTimeString(uint32 seconds)
{
    uint32 hours = seconds / 3600;
    seconds %= 3600;
    uint32 minutes = seconds / 60;
    seconds %= 60;

    std::ostringstream oss;
    oss << hours << "h " << minutes << "m " << seconds << "s";
    return oss.str();
}
