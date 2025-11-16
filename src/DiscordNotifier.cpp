#include "PlayerEventsNotifier.h"
#include "CreatureKillNotifier.h"
#include "ServerStatusNotifier.h"
#include "ScriptMgr.h"

// Register both login and level-up events
void AddPlayerEventsNotifier()
{
    new PlayerEventsNotifier();
}

// Register the script for creature kills
void AddCreatureKillNotifier()
{
    new CreatureKillNotifier();
}

// Register the server status notifier
void AddServerStatusNotifier()
{
    new ServerStatusNotifier();
}
