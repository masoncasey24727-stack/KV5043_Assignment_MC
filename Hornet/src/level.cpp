#include "level.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../Layers/TileLayer.h"
#include "../GameObjects/BoundaryObject.h"
#include "../Engine/ObjectManager.h" 



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

			if (type == "LAYER_TYPE" || type == "OBJECT_TYPE") //skips where the headings are
			{
				continue;
			}

			if (type == "TILE")   //seperates based on layers and gameobjects
			{
				//ParseLayer(line);
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

//goes through each type for game objects
void Level::ParseGameObject(const std::string& line)
{
	std::vector<std::string> tokens = split(line, ',');
	if (tokens.empty())
	{
		return;
	}

	const std::string& type = tokens[0];

	if (type == "OBJECT_TYPE")
	{
		return;
	}

	if (type == "PLAYER")
	{
		//ParsePlayer(tokens);
		return;
	}

	if (type == "ENEMY")
	{
		
		return;
	}

	if (type == "BACKGROUND" || type == "PICKUP" || type == "FUEL_PUMP")
	{
		
		return;
	}

	if (type == "BOUNDARY" || type == "BOUNDARY_FINISH")
	{
		
		return;
	}
}

//parses for game objects:
//boundary
void Level::ParseBoundary(const std::vector<std::string>& tokens)
{
	// OBJECT_TYPE, X_POSITION, Y_POSITION, WIDTH, HEIGHT, SCALE
	constexpr size_t kMinTokens = 6;
	if (tokens.size() < kMinTokens)
	{
		return;
	}

	try
	{
		const std::string& type = tokens[0];

		const double x = std::stod(tokens[1]);
		const double y = std::stod(tokens[2]);

		const int width = std::stoi(tokens[3]);
		const int height = std::stoi(tokens[4]);

		(void)std::stod(tokens[5]);

		ObjectType objType = ObjectType::BOUNDARY;
		if (type == "BOUNDARY_FINISH")
		{
			objType = ObjectType::BOUNDARY_FINISH;
		}

		BoundaryObject* boundary = new BoundaryObject(objType);
		boundary->Initialise(Vector2D(x, y), width, height);

		ObjectManager::instance.AddItem(boundary);
	}
	catch (const std::exception&)
	{
		return;
	}
}