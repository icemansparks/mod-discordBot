#ifndef CREATURE_KILL_NOTIFIER_H
#define CREATURE_KILL_NOTIFIER_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "DiscordBotConfig.h"
#include "DiscordWebhook.h"
#include "DiscordUtils.h"

class CreatureKillNotifier : public PlayerScript
{
public:
    CreatureKillNotifier();

    void OnPlayerCreatureKill(Player* killer, Creature* creature) override;
};

#endif // CREATURE_KILL_NOTIFIER_H