#pragma once
#include "../GameObjects/player.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Scene.h"
#include "../Layers/TileLayer.h"
#include "../GameObjects/BoundaryObject.h"
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
		

		TileLayer tilelayer1 = TileLayer(Dimension2D{ 128,128 }, { 55,55 },
			1.0, "../Program/assets/ThrustMap/ThrustMap_FillerTerrain.csv", false);
		tilelayer1.LoadTileSet("../Program/assets/ThrustMap/TileSetBlueVersion.png", Dimension2D{ 5, 3 });
		tilelayer1.Load();

		TileLayer tilelayer2 = TileLayer(Dimension2D{ 128,128 }, { 55,55 },
			1.0, "../Program/assets/ThrustMap/ThrustMap_CollisionTerrain.csv", true);
		tilelayer2.LoadTileSet("../Program/assets/ThrustMap/TileSetBlueVersion.png", Dimension2D{ 5, 3 });
		tilelayer2.Load();

		BoundaryObject* boundaryLeft = new BoundaryObject(ObjectType::BOUNDARY);
		boundaryLeft->Initialise(Vector2D(-2050, 0), 50, 4000); //initialise the object
		ObjectManager::instance.AddItem(boundaryLeft); //add the object

		//Enemy* enemy1 = new Enemy();

		Scene* bgImage = new Scene(ObjectType::BACKGROUND);
		bgImage->Initialise("../Program/assets/ThrustMap/ThrustMap.png", Vector2D(0, 0), 0, 1);
		ObjectManager::instance.AddItem(bgImage);

		return true;
	}
};