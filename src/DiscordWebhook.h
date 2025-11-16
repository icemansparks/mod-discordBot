#ifndef DISCORD_WEBHOOK_H
#define DISCORD_WEBHOOK_H

#include <string>
#include "DiscordBotConfig.h"

// Class to handle sending messages to a Discord webhook
class DiscordWebhook
{
public:
    explicit DiscordWebhook(const std::string& url);
    void send(const std::string& message);

private:
    std::string url_;
};

#endif // DISCORD_WEBHOOK_H
