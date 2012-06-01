#include <SFML\Graphics.hpp>
#include <iostream>

class SolidTile
{
	private:
		sf::RectangleShape m_shape;

		sf::Vector2f m_pos;
		int m_type;

	public:
		SolidTile(sf::Vector2f nPos, int nType);

		void setPos(sf::Vector2f nPos){m_pos = nPos; m_shape.setPosition(nPos);}
		void setType(int nType);

		int getType(){return m_type;}
		sf::RectangleShape getShape(){return m_shape;}
};