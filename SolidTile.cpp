#include "SolidTile.h"

SolidTile::SolidTile(sf::Vector2f nPos, int nType) : m_type(nType), m_pos(nPos)
{
	m_shape.setPosition(nPos);
	m_shape.setSize(sf::Vector2f(16, 16));

	if(nType == 0) m_shape.setFillColor(sf::Color::Transparent);
	else m_shape.setFillColor(sf::Color(255, 0, 0, 64));
}

void SolidTile::setType(int nType)
{
	m_type = nType;

	if(nType == 0) m_shape.setFillColor(sf::Color::Transparent);
	else m_shape.setFillColor(sf::Color(255, 0, 0, 64));
}