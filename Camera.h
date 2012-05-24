#pragma once
#include <SFML\Graphics.hpp>

class Camera
{
	private:
		sf::Vector2i m_winSize;
		sf::Vector2i m_lvlSize;

		sf::Vector2f m_vel;

		sf::Vector2f m_vPos;
		

		sf::View view;
	public:
		Camera(sf::Vector2i winSize, sf::Vector2i lvlSize) : m_winSize(winSize), m_lvlSize(lvlSize), m_vel(0, 0), m_vPos(0, 0){}

		void set(sf::FloatRect centerRect);
		void Update(int dt);
		void setVel(float vX, float vY){m_vel.x += vX; m_vel.y += vY;}

		sf::View getView(){return view;}
		sf::Vector2f getPos() {return m_vPos;}
};