#pragma once
#include <string>
#include <regex>

enum class Protocol
{
    HTTP = 80,
    HTTPS = 443,
    FTP = 21
};

Protocol ParseProtocol(std::string protocolStr);
int GetPort(const std::string& portStr, Protocol protocol);

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);