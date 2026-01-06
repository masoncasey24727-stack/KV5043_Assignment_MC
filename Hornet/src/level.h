#pragma once
#include "../Layers/Layer.h"

class Level
{
public:
	Level(int levelNumber, const std::string& fileName);
	bool LoadLevel();

private:

	bool ParseConfigFile();
	std::vector<std::string> split(const std::string& string, char delimiter);
	void ParseGameObject(const std::string& line);

	void ParseBoundary(const std::vector<std::string>& tokens);

private:
	std::string m_fileName;
	int m_levelNumber;
};