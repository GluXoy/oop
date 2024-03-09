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

std::string HtmlDecode(std::string const& html, const std::map<std::string, std::string>& replacements);