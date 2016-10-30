#include <SFML\System.hpp>
#include "ship.h"
#include <iostream>
#include <string>

class game{
public:
	game();
	void init();
	void run();
	void drawObjects();
	void drawPlayer();
	void playerInput();
	void drawplayerBullet();
	void spawnEnemy();
private:
	sf::RenderWindow window;
	sf::Event Event;
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Sprite playerSprite;
	sf::Sprite enemySprite;
	ship player;
	int enemyamount;
	ship *enemy;
	sf::Vector2f windowSize;
	sf::Keyboard keyboard;
	float speed;
	sf::RectangleShape midseperator;
	sf::RectangleShape playArea;
	sf::Sprite playerBulletSprite;
	sf::Texture playerBulletTexture;
	sf::Clock playerclock;
	sf::Clock enemyclock;
	float playerbulletspeed;
	sf::Font font;
	sf::Text text;
	int enemysidespawn;
};