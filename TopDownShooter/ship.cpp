#include "ship.h"

ship::ship(){
	bulletamount = 5;
	bullets = new bullet[bulletamount];
	for(int i = 0; i < bulletamount; i++)
		bullets[i].active = false;
	activeship = false;
}

void ship::updatePosition(sf::Vector2f value){
	position += value;
}

sf::Vector2f ship::getPosition(){
	return position;
}

void ship::setposition(sf::Vector2f value){
	position = value;
}

bool ship::isactiveBullet(int value){
	return bullets[value].active;
}

int ship::maxBullet(){
	return bulletamount;
}

void ship::shootbullet(int bulletvalue, sf::Vector2f pos, sf::Vector2f dir){
	bullets[bulletvalue].bulletposition = pos;
	bullets[bulletvalue].bulletdirection = dir;
}

void ship::updateBullets(){
	for(int i = 0; i < maxBullet(); i++){
		if(isactiveBullet(i)){ 
			bullets[i].bulletposition += bullets[i].bulletdirection;
		}
	}
}

void ship::setactiveBullet(int bulletvalue, bool value){
	bullets[bulletvalue].active = value;
}

sf::Vector2f ship::getBulletPosition(int value){
	return bullets[value].bulletposition;
}

bool ship::getactiveship(){
	return activeship;
}

void ship::setactiveship(bool value){
	activeship = value;
}

void ship::setenemyDir(sf::Vector2f value){
	dir = value;
}

sf::Vector2f ship::getenemyDir(){
	return dir;
}

void ship::updateEnemy(){
	position += dir;
}

void ship::resetClock(){
	clock.restart();
}

sf::Clock ship::getClock(){
	return clock;
}