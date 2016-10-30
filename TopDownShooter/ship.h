#include <SFML\Graphics.hpp>
#include "bullet.h"
#include <iostream>

class ship{
public:
	ship();
	void updatePosition(sf::Vector2f);
	sf::Vector2f getPosition();
	void setposition(sf::Vector2f);
	void shootbullet(int, sf::Vector2f, sf::Vector2f);
	bool isactiveBullet(int);
	int maxBullet();
	sf::Vector2f getbulletValue();
	void updateBullets();
	void setactiveBullet(int, bool);
	sf::Vector2f getBulletPosition(int);
	bool getactiveship();
	void setactiveship(bool);
	void setenemyDir(sf::Vector2f);
	sf::Vector2f getenemyDir();
private:
	sf::Vector2f position;
	bullet *bullets;
	int bulletamount;
	bool activeship;
	sf::Vector2f dir;
};