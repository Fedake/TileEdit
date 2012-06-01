#pragma once
#include "Tile.h"
#include "ResourceManager.h"
#include "SolidTile.h"
#include "Entity.h"

#include <string>
#include <fstream>
#include <iostream>

#define MAP_WIDTH	128
#define MAP_HEIGHT	128

class Map
{
	private:
		Tile* m_tiles[MAP_WIDTH][MAP_HEIGHT];
		SolidTile* m_solidMap[MAP_WIDTH][MAP_HEIGHT];
		Entity* m_entities[MAP_WIDTH][MAP_HEIGHT];

		Tile* m_newTile;
		SolidTile* m_newSolid;
		Entity* m_newEntity;

		ResourceManager* m_resMgr;

		sf::Text m_spawnMark;

		std::string m_levelName;

		int m_mapWidth, m_mapHeight, m_nr;

		int m_newType;
		int m_newSolidType;
		int m_newEntityType;

		bool m_drawing;
		int m_mode;
		
		sf::Vector2f m_startPos;

	public:
		Map(std::string levelName, ResourceManager* imgMgr);

		bool loadLevel();
		bool SaveLevel();

		void draw(sf::Vector2f pos);
		void NewType(sf::Vector2f pos);
		void setSpawn(sf::Vector2f pos);
		void setNewType(int nType);
		void pickTile(sf::Vector2f pos);
		void enabledraw(bool nBln){m_drawing = nBln;}
		void ChangeMode();

		void Render(sf::RenderWindow* win);

		int getMapWidth()	{return m_mapWidth;}
		int getMapHeight()	{return m_mapHeight;}
		sf::Vector2f getPlayerPos() {return m_startPos;} 

		Tile* getTile(int x, int y) {return m_tiles[x][y];}
};

struct MapFile
{	
	int ile; //Bo przyjemniej
	int w, h, x, y;

	char tiles[MAP_WIDTH][MAP_HEIGHT];
	int solid[MAP_WIDTH][MAP_HEIGHT];
	char ents[MAP_WIDTH][MAP_HEIGHT];
};