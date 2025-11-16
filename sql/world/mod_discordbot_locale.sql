-- Table for DiscordBot localization
CREATE TABLE IF NOT EXISTS `mod_discordbot_locale` (
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `msg_key` VARCHAR(64) NOT NULL,
    `lang` VARCHAR(8) NOT NULL,
    `template` TEXT NOT NULL,
    UNIQUE KEY `msg_lang` (`msg_key`, `lang`)
);

-- Remove all existing entries for this localization table
DELETE FROM `mod_discordbot_locale`;

-- Player login/logout/levelup
INSERT INTO `mod_discordbot_locale` (`msg_key`, `lang`, `template`) VALUES
('player_login',        'en', '**{PLAYER}** has logged in!'),
('player_login',        'de', '**{PLAYER}** hat sich eingeloggt!'),
('player_logout',       'en', '**{PLAYER}** has logged out!'),
('player_logout',       'de', '**{PLAYER}** hat sich ausgeloggt!'),
('player_levelup',      'en', '**{PLAYER}** has reached level **{LEVEL}** as a **{RACE} {CLASS}**! 🎉'),
('player_levelup',      'de', '**{PLAYER}** hat Level **{LEVEL}** als **{RACE} {CLASS}** erreicht! 🎉'),

-- Creature kills
('creature_rare_kill',  'en', '**{PLAYER}** (Level **{LEVEL}** {RACE} {CLASS}) has slain the rare spawn **{CREATURE}** (Level **{CREATURE_LEVEL}**)! 🏆'),
('creature_rare_kill',  'de', '**{PLAYER}** (Level **{LEVEL}** {RACE} {CLASS}) hat den seltenen Gegner **{CREATURE}** (Level **{CREATURE_LEVEL}**) besiegt! 🏆'),
('creature_boss_kill',  'en', '**{PLAYER}** (Level **{LEVEL}** {RACE} {CLASS}) has slain the boss **{CREATURE}** (Level **{CREATURE_LEVEL}**)! 🏆'),
('creature_boss_kill',  'de', '**{PLAYER}** (Level **{LEVEL}** {RACE} {CLASS}) hat den Boss **{CREATURE}** (Level **{CREATURE_LEVEL}**) besiegt! 🏆'),

-- Server status
('server_startup',      'en', '[{SERVER}] is now fully running and ready to accept connections! 🎉'),
('server_startup',      'de', '[{SERVER}] läuft jetzt und ist bereit für Verbindungen! 🎉'),
('server_shutdown',     'en', '[{SERVER}] is shutting down.'),
('server_shutdown',     'de', '[{SERVER}] wird heruntergefahren.'),

('server_uptime',       'en', '[{SERVER}] has been up for {UPTIME}.'),
('server_uptime',       'de', '[{SERVER}] läuft seit {UPTIME}.'),
('server_error',        'en', '[{SERVER}] error occurred: {ERROR}'),
('server_error',        'de', '[{SERVER}] Fehler aufgetreten: {ERROR}'),
('server_offline',      'en', '[{SERVER}] is offline. Exit code: {EXITCODE}'),
('server_offline',      'de', '[{SERVER}] ist offline. Exit-Code: {EXITCODE}');
