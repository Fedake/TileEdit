#include "ResourceManager.h"

ResourceManager::ResourceManager(std::string tilename, std::string entityname)
{
	sf::Image sheet;
	sheet.loadFromFile(tilename);

	int x = 0, y = 0;
	for(int i = 0; i < TOTAL_SPRITES; i++)
	{
		m_tileTex[i] = new sf::Texture();
		m_tileTex[i]->loadFromImage(sheet, sf::IntRect(x, y, 16, 16));

		x += 16;

		if(x >= 128)
		{
			x = 0;
			y += 16;
		}
	}

	sheet.create(16, 16, sf::Color::Transparent);
	m_entTex[0] = new sf::Texture();
	m_entTex[0]->loadFromImage(sheet);

	sheet.loadFromFile(entityname);
	for(int i = 1; i < TOTAL_ENTITIES; i++)
	{
		m_entTex[i] = new sf::Texture();
		m_entTex[i]->loadFromImage(sheet, sf::IntRect(0, (i-1)*16, 16, 16));
	}
}
