#include "DatabaseEnv.h"
#include "QueryResult.h"
#include "Field.h"
#include "DiscordLocale.h"
#include "DiscordBotConfig.h"

std::string GetLocalizedDiscordMessage(const std::string& key, const std::map<std::string, std::string>& params)
{
    std::string lang = modDiscordBotNotificationLanguage;
    std::string templateStr;

    QueryResult result = WorldDatabase.Query(
        "SELECT template FROM mod_discordbot_locale WHERE msg_key = '{}' AND lang IN ('{}', 'en') ORDER BY FIELD(lang, '{}', 'en') LIMIT 1",
        key, lang, lang);

   if (result)
    {
        Field* fields = result->Fetch();
        if (fields)
            templateStr = fields[0].Get<std::string>();
    }
    else
    {
        return "[DiscordBot] Missing message template for key: " + key + " in language: " + lang;
    }

    for (const auto& pair : params)
    {
        std::string placeholder = "{" + pair.first + "}";
        size_t pos = 0;
        while ((pos = templateStr.find(placeholder, pos)) != std::string::npos)
        {
            templateStr.replace(pos, placeholder.length(), pair.second);
            pos += pair.second.length();
        }
    }

    return templateStr;
}
