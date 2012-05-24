#include <SFML\Graphics.hpp>

class Test
{
	private:
		sf::Sprite spr;

	public:
		Test()
		{
			sf::Texture tex;
			tex.LoadFromFile("grassM.png");
			spr.SetTexture(tex);
		}
		
		sf::Sprite getSprite(){return spr;}
};