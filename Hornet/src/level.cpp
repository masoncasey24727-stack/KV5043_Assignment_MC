#include "level.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



Level::Level(int levelNumber, const std::string& fileName)
	: m_levelNumber(levelNumber)
	, m_fileName(fileName)
{
}

bool Level::ParseConfigFile()
{
	std::ifstream configFile(m_fileName);


	if (!configFile.is_open()) {
		return false;
	}
	else
	{
		std::string line;
		while (std::getline(configFile, line))
		{
			if (line.empty()) //check if line is empty
			{
				continue;
			}
			std::vector<std::string> tokens = split(line, ','); //splits lines into tokens
			if (tokens.empty())
			{
				continue;
			}
			
			const std::string& type = tokens[0];  // gets first token of line to determine what type it is

			if (type == "BACKGROUND" || type == "TILELAYER")
			{
				ParseLayer(line);
			}
			else
			{
				ParseGameObject(line);
			}
		}



		return true;
	}

	
}

//splits the line/string up into tokens based on where ','s are
std::vector<std::string> split(const std::string& string, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream stream(string);
	std::string token;

	while (std::getline(stream, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}