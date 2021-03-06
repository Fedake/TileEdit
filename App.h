#pragma once
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Choice.h"

class App
{
	private:
		int m_screenWidth;
		int m_screenHeight;
		int nr;

		std::string m_levelName;
		bool m_done;
		int m_type;

		sf::RenderWindow m_window;
		sf::RenderWindow m_choiceWindow;

		sf::Texture test;
		sf::Sprite testSpr;

		sf::Vector2f m_mPos;

		Map* m_map;
		Choice* m_choice;
		Camera* m_cam;
		ResourceManager* m_resMgr;

		sf::RectangleShape m_pauseShape;
	public:
		App(size_t win_width, size_t win_height, bool fullscreen_mode, std::string levelName) 
				: m_screenWidth(win_width), m_screenHeight(win_height), m_levelName(levelName){}
 
		void Run();
 
	private:
		bool Init();
		void draw();                // rysowanie 
		void Update(sf::Time dt);	// aktualizacja
		void ProcessEvents();       // przetwarzanie zdarze�, kt�re przysz�y	

		sf::Sprite getSpr(){return testSpr;}
};