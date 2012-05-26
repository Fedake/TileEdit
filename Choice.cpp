#include "Choice.h"

Choice::Choice(ResourceManager* resMgr)
{
	m_mode = 0;

	ziomeczek.setSize(sf::Vector2f(16, 16));
	ziomeczek.setFillColor(sf::Color::Transparent);
	ziomeczek.setOutlineThickness(2);
	ziomeczek.setOutlineColor(sf::Color::Black);

	noSolid.setSize(sf::Vector2f(16, 16));
	noSolid.setFillColor(sf::Color::Transparent);

	solid.setSize(sf::Vector2f(16,16));
	solid.setFillColor(sf::Color(255, 0, 0, 64));

	int type = 0;

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (type < TOTAL_SPRITES)
				m_tiles[i][j] = new Tile(j*16, i*16, type, resMgr->getTileTexture(type));
			if (type < TOTAL_ENTITIES)
				m_entities[i][j] = new Entity(j*16, i*16, type, resMgr->getEntityTexture(type));
			++type;
		}
	}

	m_currentTile = m_tiles[0][0];
	m_currentEntity = m_entities[0][0];
}

void Choice::Render(sf::RenderWindow* win)
{
	int current = 0;

	if (m_mode == 0)
	{
		for (int i = 0; i < 16; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (current < TOTAL_SPRITES)
					m_tiles[i][j]->Render(win);
				++current;
			}
		}
		
		ziomeczek.setPosition(m_currentTile->getBox().left, m_currentTile->getBox().top);
		win->draw(ziomeczek);
	}

	if (m_mode == 1)
	{
		noSolid.setPosition(0, 0);
		win->draw(noSolid);

		solid.setPosition(16, 0);
		win->draw(solid);

		ziomeczek.setPosition(m_currentTile->getBox().left, m_currentTile->getBox().top);
		win->draw(ziomeczek);
	}

	if (m_mode == 2)
	{
		for (int i = 0; i < 16; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (current < TOTAL_ENTITIES)
					m_entities[i][j]->Render(win);
				++current;
			}
		}

		ziomeczek.setPosition(m_currentEntity->getBox().left, m_currentEntity->getBox().top);
		win->draw(ziomeczek);
	}
}

int Choice::Click(sf::Vector2f pos)
{
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_tiles[i][j]->getBox().contains(pos))
			{
				m_currentTile = m_tiles[i][j];
				m_currentEntity = m_entities[i][j];
				return m_tiles[i][j]->getType();
			}
		}
	}
}

void Choice::ChangeMode()
{
	++m_mode;

	if (m_mode > 2) m_mode = 0;
}