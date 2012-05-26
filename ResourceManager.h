#pragma once
#include <SFML\Graphics.hpp>

#define TOTAL_SPRITES 64
#define TOTAL_ENTITIES 21

class ResourceManager
{
	private:
		std::string m_tileName;
		sf::Texture* m_tileTex[TOTAL_SPRITES];
		sf::Texture* m_entTex[TOTAL_ENTITIES];

	public:
		ResourceManager(std::string tilename, std::string entityname);

		sf::Texture* getTileTexture(int nr){return m_tileTex[nr];}
		sf::Texture* getEntityTexture(int nr){return m_entTex[nr];}

		void Render(sf::RenderWindow* win);
};