#include "App.h"
bool App::Init()  // YOO
{
	m_window.create(sf::VideoMode(m_screenWidth, m_screenHeight, 32), "PlatformFighter Editor");
	m_window.setFramerateLimit(60);
	m_window.setKeyRepeatEnabled(false);

	m_choiceWindow.create(sf::VideoMode(64, 244, 32), "Choice", sf::Style::Titlebar);
	
	int winpx = m_window.getPosition().x;
	int winsx = m_window.getSize().x;
	int cwinpx = m_choiceWindow.getPosition().x;
	int cwinsx = m_choiceWindow.getSize().x;

	m_choiceWindow.setPosition(sf::Vector2i(winpx + winsx + 5, m_window.getPosition().y + 40));

	m_resMgr = new ResourceManager("sheet.png", "entSheet.png");

	m_map = new Map(m_levelName, m_resMgr);
	if(!m_map->loadLevel()) return false;

	m_cam = new Camera(sf::Vector2i(m_window.getSize().x, m_window.getSize().y), sf::Vector2i(m_map->getMapWidth(), m_map->getMapHeight()));

	m_choice = new Choice(m_resMgr);

	return true;
}

void App::Run()
{
	if(!Init()) m_done = true;
	sf::Clock dt;
	sf::Clock fpsCap;
	dt.restart();
	// pêtla g³ówna
	m_done = false;
	
	while (!m_done)
	{
		fpsCap.restart();

		ProcessEvents();
		if(dt.getElapsedTime().asSeconds() < 0.1f)
			Update(dt.getElapsedTime());
		
		dt.restart();
		
		draw();
		if(fpsCap.getElapsedTime().asMilliseconds() != 0)
		{
			if(1000/fpsCap.getElapsedTime().asMilliseconds() > 40)
			{
				sf::Time sleepTime = sf::milliseconds((1000/40) - fpsCap.getElapsedTime().asMilliseconds());
				sf::sleep(sleepTime);
			}
		}
	}
	m_window.close();
	m_choiceWindow.close();
}

void App::draw()
{
    //RYSOWANIE UWZGLEDNIAJAC KAMERE
	m_window.setView(m_cam->getView());
	m_window.clear(sf::Color(255, 255, 255));
	m_choiceWindow.clear(sf::Color(255, 255, 255));
	//Render mapy
	m_map->Render(&m_window);
	//Render wyboru
	m_choice->Render(&m_choiceWindow);
	//RYSOWANIE STALYCH ELEMENTOW EKRANU
	m_window.setView(m_window.getDefaultView());
	//m_window.draw(testSpr);
	m_window.display();
	m_choiceWindow.display();
}

void App::ProcessEvents()
{
	if (m_done)
	{ // je¿eli mamy zakoñczyæ, to pomijamy obs³ugê zdarzeñ
		return;
	}
	
	m_map->enabledraw(sf::Mouse::isButtonPressed(sf::Mouse::Left));

	// przejrzymy kolejne zdarzenia z kolejki
	sf::Event Event;
	while (m_window.pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{   // zamkniêcie okna
			m_map->SaveLevel();
			m_done = true;
			return;
		}

		else if(Event.type == sf::Event::MouseMoved)
		{
			m_mPos = sf::Vector2f(Event.mouseMove.x, Event.mouseMove.y) + m_cam->getPos();
			m_map->NewType(m_mPos);
		}

		else if(Event.type == sf::Event::MouseButtonPressed)
		{
			if(Event.key.code == sf::Mouse::Left)
			{
				m_map->NewType(m_mPos);
			}
		}
		else if(Event.type == sf::Event::KeyPressed)
		{
			if(Event.key.code == sf::Keyboard::Space) 
			{
				m_map->ChangeMode();
				m_choice->ChangeMode();
			}

			else if(Event.key.code == sf::Keyboard::W) m_cam->setVel(0, -100);
			else if(Event.key.code == sf::Keyboard::S) m_cam->setVel(0, 100);
			else if(Event.key.code == sf::Keyboard::A) m_cam->setVel(-100, 0);
			else if(Event.key.code == sf::Keyboard::D) m_cam->setVel(100, 0);
		}
		/*else if(Event.type == sf::Event::MouseWheelMoved)
		{
			if(Event.mouseWheel.delta > 0) m_map->setNewType(1);
			if(Event.mouseWheel.delta < 0) m_map->setNewType(-1);
		}*/
		else if(Event.type == sf::Event::KeyReleased)
		{
			if(Event.key.code == sf::Keyboard::W) m_cam->setVel(0, 100);
			else if(Event.key.code == sf::Keyboard::S) m_cam->setVel(0, -100);
			else if(Event.key.code == sf::Keyboard::A) m_cam->setVel(100, 0);
			else if(Event.key.code == sf::Keyboard::D) m_cam->setVel(-100, 0);
		}
	}

	while (m_choiceWindow.pollEvent(Event))
	{
		if(Event.type == sf::Event::MouseMoved)
		{
			m_mPos = sf::Vector2f(Event.mouseMove.x, Event.mouseMove.y) + m_cam->getPos();
		}

		else if (Event.type == sf::Event::MouseButtonPressed)
		{
			if (Event.key.code == sf::Mouse::Left)
			{
				int type = m_choice->Click(m_mPos - m_cam->getPos());
				m_map->setNewType(type);
			}
		}
		else if(Event.type == sf::Event::KeyPressed)
		{
			if(Event.key.code == sf::Keyboard::Space) 
			{
				m_map->ChangeMode();
				m_choice->ChangeMode();
			}
		}
	}
}

void App::Update(sf::Time dt)
{
	m_cam->Update(dt.asMilliseconds());

	//sf::Vector2i nPos = m_window.getPosition() - sf::Vector2i(m_choiceWindow.getSize().x+10, -5);
	//m_choiceWindow.setPosition(nPos);
}
