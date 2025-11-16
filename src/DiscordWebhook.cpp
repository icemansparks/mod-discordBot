#include "DiscordWebhook.h"
#include "Log.h"
#include <windows.h>
#include <winhttp.h>
#include <iostream>

#pragma comment(lib, "winhttp.lib") // Ensure WinHTTP is linked

// Constructor for DiscordWebhook
DiscordWebhook::DiscordWebhook(const std::string& url) : url_(url) {}

// Send a message to the Discord webhook
void DiscordWebhook::send(const std::string& message)
{
    std::wstring wurl(url_.begin(), url_.end());

    // Open an HTTP session
    HINTERNET hSession = WinHttpOpen(L"Discord Bot",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);

    if (hSession)
    {
        URL_COMPONENTS components = {0};
        components.dwStructSize = sizeof(components);
        components.dwSchemeLength = -1;
        components.dwHostNameLength = -1;
        components.dwUrlPathLength = -1;

        WinHttpCrackUrl(wurl.c_str(), 0, 0, &components);
        std::wstring host(components.lpszHostName, components.dwHostNameLength);
        std::wstring path(components.lpszUrlPath, components.dwUrlPathLength);

        HINTERNET hConnect = WinHttpConnect(hSession, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
        if (hConnect)
        {
            HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", path.c_str(),
                                                    NULL, WINHTTP_NO_REFERER,
                                                    WINHTTP_DEFAULT_ACCEPT_TYPES,
                                                    WINHTTP_FLAG_SECURE);

            if (hRequest)
            {
                std::string payload = "{ \"content\": \"" + message + "\" }";
                BOOL bResults = WinHttpSendRequest(hRequest,
                                                   L"Content-Type: application/json\r\n",
                                                   -1, (LPVOID)payload.c_str(), payload.size(),
                                                   payload.size(), 0);

                if (bResults)
                {
                    bResults = WinHttpReceiveResponse(hRequest, NULL);
                    if (bResults)
                    {
                        if (modDiscordBotDebug)
                            LOG_INFO("module", "Discord notification sent: {}", message);
                    }
                    else
                    {
                        LOG_ERROR("module", "Failed to receive response from Discord webhook.");
                    }
                }
                else
                {
                    LOG_ERROR("module", "Failed to send request to Discord webhook.");
                }

                WinHttpCloseHandle(hRequest);
            }
            else
            {
                LOG_ERROR("module", "Failed to open HTTP request.");
            }
            WinHttpCloseHandle(hConnect);
        }
        else
        {
            LOG_ERROR("module", "Failed to connect to Discord webhook.");
        }
        WinHttpCloseHandle(hSession);
    }
    else
    {
        LOG_ERROR("module", "Failed to open HTTP session.");
    }
}
