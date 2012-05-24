#pragma once
#include <SFML\Graphics.hpp>

class Tile
{
	private:
		sf::Vector2f m_pos;
		sf::FloatRect m_box;
		sf::Sprite m_spr;

		int m_type;
	public:
		Tile(float nX, float nY, int nType, sf::Texture* newTexture);

		int getType(){return m_type;}

		void Render(sf::RenderWindow* win){win->draw(m_spr);}
		sf::FloatRect getBox(){return m_box;}

		void setPos(sf::Vector2f nPos);
		void setType(int nType){m_type = nType;}

};