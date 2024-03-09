#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

std::multimap<std::string, std::string> FillDictionary(std::fstream& file)
{
	std::multimap<std::string, std::string> dictionary;
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream iss(line);
		std::string key, value;
		if (std::getline(iss, key, ':') && std::getline(iss, value))
		{
			dictionary.insert(std::make_pair(key, value));
		}
		else
		{
			throw std::runtime_error("Invalid format in line: " + line);
		}
	}

	if (file.bad())
	{
		throw std::runtime_error("Error: reading from input stream!");
	}

	file.close();
	return dictionary;
}

void AddOrIgnoreNewWord(const std::string& sourceWord, std::multimap<std::string, std::string>& dictionary)
{
	std::cout << "The word \"" << sourceWord <<
		"\" wasn't find. If you want add it to the dictionary, enter the translation, another case enter an empty string.\n";
	std::string translation;
	std::getline(std::cin, translation);
	if (!translation.empty())
	{
		dictionary.insert(std::make_pair(sourceWord, translation));
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

void SaveChangingsToFile(std::fstream& file, const std::multimap<std::string, std::string>& dictionary)
{
	for (auto itr = dictionary.begin(); itr != dictionary.end(); itr++)
	{
		file << itr->first << ':' << itr->second << '\n';
	}
	std::cout << "Changes were saved!\n";
}

void PrintTranslatedWords(std::multimap<std::string, std::string>& dictionary)
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
			std::string translations;
			std::string divider = ", ";
			for (auto itr = dictionary.begin(); itr != dictionary.end(); itr++)
			{
				if (itr->first == sourceWord)
				{
					translations = translations + itr->second + divider;
				}
			}
			std::cout << translations.substr(0, translations.length() - divider.length()) << '\n';
		}
		else
		{
			AddOrIgnoreNewWord(sourceWord, dictionary);
		}
	}
}

void WordsTranslater(std::string fileName)
{
	std::fstream file;
	file.open(fileName, std::ios::in);
	if (!file)
	{
		throw std::runtime_error("Failed to open " + fileName + " for reading!");
	}

	std::multimap<std::string, std::string> dictionary = FillDictionary(file);

	size_t startDictionarySize = dictionary.size();

	PrintTranslatedWords(dictionary);

	if (!IsSaveChangings(startDictionarySize, dictionary.size()))
	{
		return;
	}

	file.open(fileName, std::ios::out | std::ios::trunc);
	if (!file)
	{
		throw std::runtime_error("Failed to open " + fileName + " for writing!");
	}
	SaveChangingsToFile(file, dictionary);
}