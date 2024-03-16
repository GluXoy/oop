#include <iostream>
#include <string>
#include <regex>
#include "parse.h"

using namespace std;

Protocol ParseProtocol(std::string protocolStr)
{
    transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(), ::tolower);
    if (protocolStr == "http")
    {
        return Protocol::HTTP;
    }
    else if (protocolStr == "https")
    {
        return Protocol::HTTPS;
    }
    else if (protocolStr == "ftp")
    {
        return Protocol::FTP;
    }
    else
    {
        throw std::invalid_argument("Unknown protocol");
    }
}

int GetPort(const std::string& portStr, Protocol protocol)
{
    const int PORT_MAX = 65535;
    const int PORT_MIN = 1;
    if (portStr.empty())
    {
        return static_cast<int>(protocol);
    }
    // проверка границы
    else if (stoi(portStr.substr(1)) > PORT_MAX || stoi(portStr.substr(1)) < PORT_MIN)
    {
        throw invalid_argument("Invalid port number!");
    }
    else
    {
        return stoi(portStr.substr(1));
    }
}

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
    std::regex urlRegex("([\\w]+)://([^/:]+)(:\\d{1,5})?(/.*)?");
    std::smatch match;

    try
    {
        if (!regex_match(url, match, urlRegex))
        {
            throw runtime_error("URL parsing failed.");
        }
        protocol = ParseProtocol(match[1]);
        host = match[2];
        port = GetPort(match[3], protocol);
        document = match[4];
        if (!document.empty())
        {
            document = document.substr(1);
        }
    }
    catch (const std::exception& ex)
    {
        // try-catch в main
        cout << ex.what() << '\n';
        return false;
    }
    return true;
}