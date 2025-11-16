#ifndef SERVER_STATUS_NOTIFIER_H
#define SERVER_STATUS_NOTIFIER_H

#include "Common.h"
#include "ScriptMgr.h"
#include "DiscordWebhook.h"
#include "DiscordBotConfig.h"

// Class to handle server status notifications
class ServerStatusNotifier : public WorldScript
{
public:
    ServerStatusNotifier() : WorldScript("ServerStatusNotifier") { }

    void OnStartup() override;
    void OnShutdown() override;

    void NotifyServerError(const std::string& errorMessage);
    void NotifyServerOffline(int exitCode);

private:
    std::string FormatUptimeMessage();
    std::string FormatErrorMessage(const std::string& errorMessage);
    std::string FormatOfflineMessage(int exitCode);
};

#endif // SERVER_STATUS_NOTIFIER_H
