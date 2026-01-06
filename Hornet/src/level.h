#pragma once
#include <string>

class Level
{
public:
	Level(int levelNumber, const std::string& fileName)
	{
		
	}

	bool LoadLevel()
	{
		

		return true;
	}
	bool ParseConfigFile(const std::string& fileName);
};