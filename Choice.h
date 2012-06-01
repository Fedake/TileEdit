#pragma once
#include "Tile.h"
#include "ResourceManager.h"
#include "Entity.h"

#include <iostream>

#define TOTAL_SPRITES 64
#define TOTAL_ENTITIES 21

class Choice
{
	private:
		Tile* m_tiles[16][4];
		Entity* m_entities[16][4];

		sf::RectangleShape ziomeczek, noSolid, solid, halfSolid;

		Tile* m_currentTile;
		Entity* m_currentEntity;

		int m_mode;
	public:
		Choice(ResourceManager* resMgr);

		void ChangeMode();

		void Render(sf::RenderWindow* win);
		int Click(sf::Vector2f pos);
};