#include "Camera.h"
#include <iostream>

void Camera::set(sf::FloatRect box)
{
}

void Camera::Update(int dt)
{
	view.setSize(m_winSize.x, m_winSize.y);
	sf::Vector2f vCenter = m_vPos + static_cast<sf::Vector2f>(m_winSize/2);

	view.setCenter(vCenter);


	m_vPos.x += m_vel.x*(dt/1000.f);
	m_vPos.y += m_vel.y*(dt/1000.f);
}