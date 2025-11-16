#ifndef PLAYER_EVENTS_NOTIFIER_H
#define PLAYER_EVENTS_NOTIFIER_H

#include "ScriptMgr.h"
#include "Player.h"
#include "DiscordBotConfig.h"
#include "DiscordWebhook.h"
#include "DiscordUtils.h"

// Class to handle player events and send notifications to Discord
class PlayerEventsNotifier : public PlayerScript
{
public:
    PlayerEventsNotifier();

    void OnPlayerLogin(Player* player) override;
    void OnPlayerLogout(Player* player) override;
    void OnPlayerLevelChanged(Player* player, uint8 oldLevel) override;
};

#endif // PLAYER_EVENTS_NOTIFIER_H