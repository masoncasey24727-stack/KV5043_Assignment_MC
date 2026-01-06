#include "level.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../Layers/TileLayer.h"
#include "../GameObjects/BoundaryObject.h"
#include "../Engine/ObjectManager.h" 
#include "../GameObjects/Pickup.h"
#include "../GameObjects/FuelPump.h"
#include "../Engine/HtGraphics.h"


bool Level::StringToBool(const std::string& theString)
{
	if (theString == "TRUE" || theString == "true" || theString == "1")
	{
		return true;
	}
	return false;
}

bool Level::LoadLevel()
{
	return true;
}

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
std::vector<std::string> Level::split(const std::string& string, char delimiter)
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

	if (type == "BACKGROUND")
	{
		ParseBackground(tokens);
		return;
	}

	if (type == "PICKUP")
	{
		ParsePickup(tokens);
		return;
	}

	if (type == "FUEL_PUMP")
	{
		ParseFuelPump(tokens);
		return;
	}

	if (type == "BOUNDARY" || type == "BOUNDARY_FINISH")
	{
		ParseBoundary(tokens);
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

//Background

void Level::ParseBackground(const std::vector<std::string>& tokens)
{
	// BACKGROUND line uses: ... SCALE, IMAGE, ANGLE, IS_FLIPPED_H, IS_FLIPPED_V ...
	constexpr size_t kMinTokens = 7;
	if (tokens.size() < kMinTokens)
	{
		return;
	}

	const std::string& imagePath = tokens[6];

	PictureIndex picture = HtGraphics::instance.LoadPicture(imagePath);
	if (picture != NO_PICTURE_INDEX)
	{
		HtGraphics::instance.SetBackgroundTexture(picture);
	}
}

//Pickup
void Level::ParsePickup(const std::vector<std::string>& tokens)
{
	constexpr size_t kMinTokens = 12; 
	{
		return;
	}

	try
	{
		const double x = std::stod(tokens[1]);
		const double y = std::stod(tokens[2]);
		const double scale = std::stod(tokens[5]);

		const std::string& image = tokens[6];
		const double angle = std::stod(tokens[7]);

		const int value = std::stoi(tokens[11]);

		PickUp* pickup = new PickUp(ObjectType::PICK_UP);
		pickup->Initialise(image.c_str(), Vector2D(x, y), angle, scale);
		pickup->SetValue(value);

		ObjectManager::instance.AddItem(pickup);
	}
	catch (const std::exception&)
	{
		return; 
	}
}

//FuelPump

void Level::ParseFuelPump(const std::vector<std::string>& tokens)
{
	// Need up to ANIM_SPEED
	constexpr size_t kMinTokens = 15;
	if (tokens.size() < kMinTokens)
	{
		return;
	}

	try
	{
		const double x = std::stod(tokens[1]);
		const double y = std::stod(tokens[2]);
		const double scale = std::stod(tokens[5]);

		const std::string& image = tokens[6];
		const double angle = std::stod(tokens[7]);

		const int fuelValue = std::stoi(tokens[11]);

		const bool isAnimated = StringToBool(tokens[12]);
		const int frameCount = std::stoi(tokens[13]);
		const double animSpeed = std::stod(tokens[14]);

		FuelPump* fuelPump = new FuelPump(ObjectType::FUEL_PUMP);
		fuelPump->Initialise(image.c_str(), Vector2D(x, y), angle, scale);
		fuelPump->SetFuelValue(fuelValue);

		if (isAnimated)
		{
			fuelPump->SetFrameCount(frameCount);
			fuelPump->SetAnimationSpeed(animSpeed);
		}

		ObjectManager::instance.AddItem(fuelPump);
	}
	catch (const std::exception&)
	{
		// Designer-proofing (Criteria 4)
		return;
	}
}