#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include "translate.h"


Dictionary FillDictionary(std::fstream& file)
{
	Dictionary dictionary;
	std::string line;
	std::string word;
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			word.clear();
		}
		else
		{
			if (word.empty())
			{
				word = line;
			}
			else
			{
				dictionary.emplace(word, line);
			}
		}
	}

	if (file.bad())
	{
		throw std::runtime_error("Error: reading from input stream!");
	}

	file.close();
	return dictionary;
}

void AddOrIgnoreNewWord(const std::string& sourceWord, Dictionary& dictionary)
{
	std::cout << "The word \"" << sourceWord <<
		"\" wasn't find. If you want add it to the dictionary, enter the translation, another case enter an empty string.\n";
	std::string translation;
	std::getline(std::cin, translation);
	if (!translation.empty())
	{
		dictionary.emplace(sourceWord, translation);
		std::cout << "The word \"" << sourceWord << "\" was kept as \"" << translation << "\" in the dictionary.\n";
	}
	else
	{
		std::cout << "The word \"" << sourceWord << "\" was ignored.\n";
	}
}

bool IsSaveChangings(size_t dictStartLen, size_t dictCurrLen)
{
	if (dictStartLen == dictCurrLen)
	{
		return false;
	}

	std::cout << "Dictionary was changed. If you want to save changes, enter Y/y:\n";
	char isSave;
	std::cin >> isSave;
	if (!(isSave == 'y' || isSave == 'Y'))
	{
		return false;
	}

	return true;
}

void SaveChangingsToFile(std::fstream& file, const Dictionary& dictionary)
{
	for (auto& [word, translation] : dictionary)
	{
		file << word << '\n' << translation << '\n' << '\n';
	}
	std::cout << "Changes were saved!\n";
}

void PrintTranslatedWord(const Dictionary& dictionary, const std::string& sourceWord)
{
	std::string translations;
	std::string divider = ", ";
	for (auto& [word, translation] : dictionary)
	{
		if (word == sourceWord)
		{
			translations = translations + translation + divider;
		}
	}
	std::cout << translations.substr(0, translations.length() - divider.length()) << '\n';
}

void FindWords(Dictionary& dictionary)
{
	const std::string EXIT_SIGN = "...";
	while (1)
	{
		std::cout << "Enter word for translation:\n";
		std::string sourceWord;
		do
		{
			std::getline(std::cin, sourceWord);
		} while (sourceWord.empty());

		if (sourceWord == EXIT_SIGN)
		{
			return;
		}

		auto it = dictionary.find(sourceWord);
		if (it != dictionary.end())
		{
			PrintTranslatedWord(dictionary, sourceWord);
		}
		else
		{
			AddOrIgnoreNewWord(sourceWord, dictionary);
		}
	}
}

void OpenFileForReading(std::fstream& file, const std::string& fileName)
{
	file.open(fileName, std::ios::in);
	if (!file)
	{
		throw std::runtime_error("Failed to open " + fileName + " for reading!");
	}
}

void OpenFileForWriting(std::fstream& file, const std::string& fileName)
{
	file.open(fileName, std::ios::out | std::ios::trunc);
	if (!file)
	{
		throw std::runtime_error("Failed to open " + fileName + " for writing!");
	}
}

void WordsTranslater(const std::string& fileName)
{
	std::fstream file;
	OpenFileForReading(file, fileName);

	Dictionary dictionary = FillDictionary(file);
	
	size_t startDictionarySize = dictionary.size();

	FindWords(dictionary);

	if (!IsSaveChangings(startDictionarySize, dictionary.size()))
	{
		return;
	}

	OpenFileForWriting(file, fileName);
	SaveChangingsToFile(file, dictionary);
}