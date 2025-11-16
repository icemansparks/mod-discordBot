# AzerothCore Module: Discord Bot Notifier

## Description
This module sends event-based messages from AzerothCore to a Discord channel using webhooks. It supports player events (login, logout, level-up), creature kill notifications (rare spawns and bosses), and server status notifications, all with multi-language localization support.

## Features
- **Player Events**: Login, logout, and level-up notifications
- **Creature Kill Notifications**: Rare spawn and boss kill announcements
- **Server Status**: Startup, shutdown
- **Multiple Webhooks**: Separate webhook URLs for player and server events
- **Localization**: Database-driven message templates with language support
- **Account Filtering**: Restrict notifications to specific account IDs

## Installation
1. Place `mod-discordBot` in your AzerothCore `modules/` directory.
2. Run `cmake` and `make` to compile the module.
3. Import the SQL file: `sql/world/mod_discordbot_locale.sql` into your world database.
4. Copy `conf/mod-discordBot.conf.dist` to your server's `config` directory as `mod-discordBot.conf`.
5. Configure the module and restart your server.

## Configuration
Edit `mod-discordBot.conf` to configure:
- `modDiscordBotPlayerWebhookURL`: Webhook for player-related events
- `modDiscordBotServerWebhookURL`: Webhook for server-related events
- `modDiscordBotAllowedAccounts`: Comma-separated account IDs (empty = all accounts)
- `modDiscordBotEnableRareSpawnKills`: Enable rare spawn kill notifications
- `modDiscordBotEnableBossKills`: Enable boss kill notifications
- `modDiscordBotNotificationLanguage`: Language code (e.g., "en", "de")

## Module Structure

### Core Files
- **`DiscordBotLoader.cpp`** - Main entry point; loads configuration and registers all script hooks
- **`DiscordBotConfig.h/cpp`** - Configuration management; exposes module settings
- **`DiscordWebhook.h/cpp`** - HTTP client for sending webhook messages to Discord

### Event Notifiers
- **`PlayerEventsNotifier.h/cpp`** - Handles player login, logout, and level-up events
- **`CreatureKillNotifier.h/cpp`** - Handles rare spawn and boss kill notifications
- **`ServerStatusNotifier.h/cpp`** - Handles server uptime, error, and offline notifications
- **`DiscordNotifier.cpp`** - Registers all notifier scripts with AzerothCore

### Utilities & Localization
- **`DiscordUtils.h`** - Helper functions (race/class names, colors, account filtering, etc.)
- **`DiscordLocale.h/cpp`** - Database-driven localization system for message templates

### Configuration & Data
- **`conf/mod-discordBot.conf.dist`** - Configuration template
- **`sql/world/mod_discordbot_locale.sql`** - Localized message templates

## Adding New Notifications
1. Create a new notifier class (e.g., `YourEventNotifier.h/cpp`) inheriting from appropriate script base
2. Override relevant event hooks (e.g., `OnLogin`, `OnCreatureKill`, etc.)
3. Use `DiscordWebhook` to send messages and `DiscordLocale` for localization
4. Register your notifier in `DiscordNotifier.cpp`
5. Add message templates to `sql/world/mod_discordbot_locale.sql`

## Localization
Message templates are stored in the `mod_discordbot_locale` table with support for multiple languages. Templates use `{placeholder}` syntax for dynamic values (e.g., `{playerName}`, `{level}`, `{creatureName}`).

## Requirements
- AzerothCore (WOTLK 3.3.5a)
- Discord webhook URL(s)