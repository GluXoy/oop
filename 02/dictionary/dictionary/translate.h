#pragma once
#include <string>
#include <map>
#include <fstream>


void WordsTranslater(std::string fileName);
std::multimap<std::string, std::string> FillDictionary(std::fstream& file);
void AddOrIgnoreNewWord(const std::string& sourceWord, std::multimap<std::string, std::string>& dictionary);