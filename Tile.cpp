#include "Tile.h"

Tile::Tile(float nX, float nY, int nType, sf::Texture* tex) : m_pos(nX, nY), m_box(nX, nY, 16, 16), m_type(nType)
{	
	m_spr.setTexture(*tex);
	m_spr.setPosition(m_pos);
}

void Tile::setPos(sf::Vector2f nPos)
{
	m_pos = nPos;

	m_box.left = nPos.x;
	m_box.top = nPos.y;

	m_spr.setPosition(nPos);
}