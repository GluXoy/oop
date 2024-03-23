#pragma once
#include <string>
#include <vector>//убрать после вынесени€ объ€вл.

//более подход€щее им€
struct Pair
{
	std::string encode;
	std::string decode;//изменить на char
};

//объ€вить внутри функции вместе со структурой
extern std::vector<Pair> replacements;

std::string HtmlDecode(std::string const& html, const std::vector<Pair>& replacements);