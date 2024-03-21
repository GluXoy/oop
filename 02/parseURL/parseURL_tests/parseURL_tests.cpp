#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../parseURL/parse.h"
#include <Windows.h>

TEST_CASE("ParseURL - Valid HTTP URL")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    REQUIRE(ParseURL("http://www.example.com/path/to/resource", protocol, port, host, document) == true);

    CHECK(protocol == Protocol::HTTP);
    CHECK(port == 80);
    CHECK(host == "www.example.com");
    CHECK(document == "path/to/resource");
}

TEST_CASE("ParseURL - Valid HTTPS URL")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    REQUIRE(ParseURL("https://www.example.com/path/to/resource", protocol, port, host, document) == true);

    CHECK(protocol == Protocol::HTTPS);
    CHECK(port == 443);
    CHECK(host == "www.example.com");
    CHECK(document == "path/to/resource");
}

TEST_CASE("ParseURL - Valid FTP URL")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    REQUIRE(ParseURL("ftp://ftp.example.com/resource", protocol, port, host, document) == true);

    CHECK(protocol == Protocol::FTP);
    CHECK(port == 21);
    CHECK(host == "ftp.example.com");
    CHECK(document == "resource");
}

TEST_CASE("ParseURL - URL with Custom Port and random protocol letter case")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    REQUIRE(ParseURL("FtP://www.example.com:8080/path/to/resource", protocol, port, host, document) == true);

    CHECK(protocol == Protocol::FTP);
    CHECK(port == 8080);
    CHECK(host == "www.example.com");
    CHECK(document == "path/to/resource");
}

TEST_CASE("ParseURL - URL with Empty Document")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    REQUIRE(ParseURL("http://www.example.com", protocol, port, host, document) == true);

    CHECK(protocol == Protocol::HTTP);
    CHECK(port == 80);
    CHECK(host == "www.example.com");
    CHECK(document.empty());
}

TEST_CASE("ParseURL - Invalid URL")
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    SECTION("URL без протокола")
    {
        CHECK_THROWS_AS(ParseURL("www.example.com/path/to/resource", protocol, port, host, document), std::runtime_error);
        CHECK_THROWS_AS(ParseURL("example.com/path/to/resource", protocol, port, host, document), std::runtime_error);
        CHECK_THROWS_AS(ParseURL("://www.example.com/path/to/resource", protocol, port, host, document), std::runtime_error);
    }

    SECTION("Некорректные значения хоста")
    {
        CHECK_THROWS_AS(ParseURL("http://:8080/path/to/resource", protocol, port, host, document), std::runtime_error);
        CHECK_THROWS_AS(ParseURL("http:///path/to/resource", protocol, port, host, document), std::runtime_error);
    }

    SECTION("URL с неправильным форматом порта")
    {
        CHECK_THROWS_AS(ParseURL("http://www.example.com:0/path/to/resource", protocol, port, host, document), std::invalid_argument);
        CHECK_THROWS_AS(ParseURL("http://www.example.com:-1/path/to/resource", protocol, port, host, document), std::runtime_error);
        CHECK_THROWS_AS(ParseURL("http://www.example.com:abc/path/to/resource", protocol, port, host, document), std::runtime_error);
        CHECK_THROWS_AS(ParseURL("http://www.example.com:65536/path/to/resource", protocol, port, host, document), std::invalid_argument);
    }

    SECTION("URL с пустым путем")
    {
        CHECK_THROWS_AS(ParseURL("http://www.example.com:", protocol, port, host, document), std::runtime_error);
    }
}

TEST_CASE("ParseURL - boundary ports URL")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    SECTION("URL with boundary ports return true")
    {
        CHECK(ParseURL("http://www.example.com:1/path/to/resource", protocol, port, host, document) == true);
        CHECK(ParseURL("http://www.example.com:65535/path/to/resource", protocol, port, host, document) == true);
    }
}