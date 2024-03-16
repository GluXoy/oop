#pragma once
#include <string>
#include <map>
#include <fstream>

typedef std::multimap<std::string, std::string> Dictionary;

void WordsTranslater(const std::string& fileName);
void PrintTranslatedWord(const Dictionary& dictionary, const std::string& sourceWord);
Dictionary FillDictionary(std::fstream& file);
