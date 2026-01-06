#include "level.h"
#include <fstream>
#include <string>

bool Level::ParseConfigFile(const std::string& fileName)
{
	std::ifstream configFile(fileName);


	if (!configFile.is_open()) {
		return false;
	}
	else
	{
		std::string line;
		while (std::getline(configFile, line))
		{
			if (line.empty())
			{
				continue;
			}
		}

	}
}