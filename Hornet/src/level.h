#pragma once
#include "../Layers/Layer.h"
#include <vector>

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
	void ParseBackground(const std::vector<std::string>& tokens);
	void ParsePickup(const std::vector<std::string>& tokens);
	void ParseFuelPump(const std::vector<std::string>& tokens);
	bool StringToBool(const std::string& theString);
	void ParseEnemy(const std::vector<std::string>& tokens);
	void ParsePlayer(const std::vector<std::string>& tokens);

private:
	std::string m_fileName;
	int m_levelNumber;
};