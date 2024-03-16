#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTML_Decode/decode.h"

TEST_CASE("HtmlDecode test")
{
    SECTION("Test decoding of HTML entities")
    {
        CHECK(HtmlDecode("&quot;", replacements) == "\"");
        CHECK(HtmlDecode("&apos;", replacements) == "'");
        CHECK(HtmlDecode("&lt;", replacements) == "<");
        CHECK(HtmlDecode("&gt;", replacements) == ">");
        CHECK(HtmlDecode("&amp;", replacements) == "&");
    }

    SECTION("Test decoding of multiple HTML entities")
    {
        CHECK(HtmlDecode("&amp;&amp;", replacements) == "&&");
        CHECK(HtmlDecode("&lt;&lt;", replacements) == "<<");
    }

    SECTION("Test decoding of HTML entities with other characters")
    {
        CHECK(HtmlDecode("&amp;amp;", replacements) == "&amp;");
        CHECK(HtmlDecode("123&amp;", replacements) == "123&");
        CHECK(HtmlDecode("&amp;123&amp;", replacements) == "&123&");
        CHECK(HtmlDecode("Cat&lt;says&gt;&quot;Meow&quot;.M&amp;M&apos;s", replacements) == "Cat<says>\"Meow\".M&M's");
    }

    SECTION("Test decoding of non-HTML entities")
    {
        CHECK(HtmlDecode("123", replacements) == "123");
        CHECK(HtmlDecode("\n", replacements) == "\n");
        CHECK(HtmlDecode("", replacements) == "");
        CHECK(HtmlDecode("&&", replacements) == "&&");
    }
}