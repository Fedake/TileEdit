#include "Map.h"

Map::Map(std::string name, ResourceManager* resMgr) : m_mapWidth(0), m_mapHeight(0), m_levelName(name), m_newType(0), m_resMgr(resMgr),
													  m_mode(0), m_newSolidType(0), m_newEntityType(0)
{
	m_newTile = new Tile(0, 0, m_newType, m_resMgr->getTileTexture(m_newType));
	m_newSolid = new SolidTile(sf::Vector2f(0, 0), m_newSolidType);
	m_newEntity = new Entity(0, 0, m_newEntityType, m_resMgr->getEntityTexture(m_newEntityType));

	m_spawnMark.setCharacterSize(14);
	m_spawnMark.setColor(sf::Color::Black);
	m_spawnMark.setString("R");
	m_spawnMark.setStyle(sf::Text::Style::Bold);
}


void Map::NewType(sf::Vector2f pos)
{
	if(pos.x <= m_mapWidth*16 && pos.y <= m_mapHeight*16)
	{
		for(int j = 0; j < m_mapHeight; j++)
		{
			for(int i = 0; i < m_mapWidth; i++)
			{
				if(m_tiles[i][j]->getBox().contains(pos))
				{
					sf::FloatRect box = m_tiles[i][j]->getBox();

					m_newTile->setPos(sf::Vector2f(box.left, box.top));
					m_newSolid->setPos(sf::Vector2f(box.left, box.top));
					m_newEntity->setPos(sf::Vector2f(box.left, box.top));

					if(m_drawing && m_mode == 0) m_tiles[i][j] = new Tile(*m_newTile);
					if(m_drawing && m_mode == 1) m_solidMap[i][j]->setType(m_newSolidType); 
					if(m_drawing && m_mode == 2) m_entities[i][j] = new Entity(*m_newEntity);
				}
			}
		}
	}
}

void Map::setSpawn(sf::Vector2f pos)
{
	m_startPos = sf::Vector2f(static_cast<int>(pos.x), static_cast<int>(pos.y));
	m_spawnMark.setPosition(m_startPos);	
}

void Map::setNewType(int nType)
{
	if(m_mode == 0)
	{
		m_newType = nType;
		if(m_newType > TOTAL_SPRITES) m_newType = 0;
		if(m_newType < 0) m_newType = 63;
	}
	else if(m_mode == 1)
	{
		m_newSolidType = nType;
		if(m_newSolidType > 2) m_newSolidType = 0;
		if(m_newSolidType < 0) m_newSolidType = 1;
	}
	else if(m_mode == 2)
	{
		m_newEntityType = nType;
		if(m_newEntityType > 20) m_newEntityType = 0;
		if(m_newEntityType < 0) m_newEntityType = 20;
	}

	sf::FloatRect box = m_newTile->getBox();
	m_newTile = new Tile(box.left, box.top, m_newType, m_resMgr->getTileTexture(m_newType));
	m_newSolid->setType(m_newSolidType);
	m_newEntity = new Entity(box.left, box.top, m_newEntityType, m_resMgr->getEntityTexture(m_newEntityType));
}

void Map::pickTile(sf::Vector2f pos)
{
	if(pos.x <= m_mapWidth*16 && pos.y <= m_mapHeight*16)
	{
		for(int j = 0; j < m_mapHeight; j++)
		{
			for(int i = 0; i < m_mapWidth; i++)
			{
				if(m_tiles[i][j]->getBox().contains(pos))
				{
					if(m_mode == 0) m_newTile = new Tile(*m_tiles[i][j]);
					if(m_mode == 1) {m_newSolidType = m_solidMap[i][j]->getType(); m_newSolid->setType(m_newSolidType);}
					if(m_mode == 2) m_newEntity = new Entity(*m_entities[i][j]);
				}
			}
		}
	}
}


void Map::ChangeMode()
{
	m_mode++;

	if(m_mode > 2) m_mode = 0;
}

bool Map::loadLevel()
{
	std::ifstream file("maps/" + m_levelName + ".map", std::ios::binary);
	if(file == NULL) return false;

	char* temp = new char[sizeof(MapFile)];
	file.read(temp, sizeof(MapFile));
	MapFile* map = (MapFile*)(temp);

	m_mapWidth = map->w;
	m_mapHeight = map->h;
	m_nr = map->ile;

	m_startPos = sf::Vector2f(map->x, map->y);

	std::cout << "Map witdh " << map->w << std::endl;
	std::cout << "Map height " << map->h << std::endl;
	std::cout << "Map number " << map->ile << std::endl;
	std::cout << "Player pos x:" << map->x << " y: " << map->y << std::endl;

	for(int j = 0; j < m_mapHeight; j++)
	{
		for(int i = 0; i < m_mapWidth; i++)
		{
			//TILES
			if(map->tiles[i][j] < 0 || map->tiles[i][j] >= 64) return false;
			m_tiles[i][j] = new Tile(static_cast<float>(i*16), static_cast<float>(j*16), map->tiles[i][j], m_resMgr->getTileTexture(map->tiles[i][j]));
			//SOLID
			if(map->solid[i][j] < 0 || map->solid[i][j] > 2) return false;
			m_solidMap[i][j] = new SolidTile(sf::Vector2f(static_cast<float>(i*16), static_cast<float>(j*16)), map->solid[i][j]);
			//ENTITIES
			m_entities[i][j] = new Entity(static_cast<float>(i*16), static_cast<float>(j*16), map->ents[i][j], m_resMgr->getEntityTexture(map->ents[i][j]));	
		}
	}
	m_spawnMark.setPosition(m_startPos);
	return true;
}

bool Map::SaveLevel()
{
	MapFile* map = new MapFile();

	map->w = m_mapWidth;
	map->h = m_mapHeight;
	map->ile = m_nr;

	map->x = m_startPos.x;
	map->y = m_startPos.y;

	for(int j = 0; j < m_mapHeight; j++)
	{
		for(int i = 0; i < m_mapWidth; i++)
		{
			map->tiles[i][j] = m_tiles[i][j]->getType();
			map->solid[i][j] = m_solidMap[i][j]->getType();
			map->ents[i][j] = m_entities[i][j]->getType();
		}
	}

	std::ofstream file("maps/" + m_levelName + ".map", std::ios::binary);
	file.write((char*)(map), sizeof(MapFile));
	file.close();

	delete map;
	return true;
}


void Map::Render(sf::RenderWindow* win)
{
	for(int j = 0; j < m_mapHeight; j++)
	{
		for(int i = 0; i < m_mapWidth; i++)
		{
			if(m_tiles[i][j]->getType() != 0) m_tiles[i][j]->Render(win);

			m_entities[i][j]->Render(win);
			if(m_mode == 1) win->draw(m_solidMap[i][j]->getShape());
		}
	}

	win->draw(m_spawnMark);

	if(m_mode == 0) m_newTile->Render(win);
	if(m_mode == 1) win->draw(m_newSolid->getShape());
	if(m_mode == 2) m_newEntity->Render(win);
}