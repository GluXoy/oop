#pragma once
#include <iostream>
#include <string>
#include <map>

std::map<std::string, std::string> replacements =
{
	{"&quot;", "\""},
	{"&apos;", "'"},
	{"&lt;", "<"},
	{"&gt;", ">"},
	{"&amp;", "&"}
};

void decodeHtmlEntity(std::string& str, const std::string& encodeEl, const std::string& decodeEl);
std::string HtmlDecode(std::string const& html, std::map<std::string, std::string> replacements);