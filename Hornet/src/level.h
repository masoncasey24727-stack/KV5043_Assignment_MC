#pragma once
#include "../GameObjects/player.h"
class Level
{
public:
	Level(int levelNumber, const std::string& fileName)
	{

	}

	bool LoadLevel()
	{
		Player* player = new Player(ObjectType::PLAYER);
		player->Initialise("../Program/assets/Rocket1.png",Vector2D(1000, 1000), 0, 0.12);
		ObjectManager::instance.AddItem(player);
		return true;
	}
};