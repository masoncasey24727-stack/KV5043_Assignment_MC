#pragma once

class Level
{
public:
	Level(int levelNumber, const std::string& fileName);
	bool LoadLevel();

private:

	bool ParseConfigFile();
	std::vector<std::string> split(const std::string& string, char delimiter);

private:
	std::string m_fileName;
	int m_levelNumber;
};