#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Pair
{
	std::string encode;
	std::string decode;
};

extern std::vector<Pair> replacements;

std::string HtmlDecode(std::string const& html, const std::vector<Pair>& replacements);