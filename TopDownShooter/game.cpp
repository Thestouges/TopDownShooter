#include "game.h"

game::game(){
	init();
	run();
}

void game::init(){
	windowSize = sf::Vector2f(800,600);
	speed = .1;
	enemyamount = 10;
	playerbulletspeed = .1;
	enemy = new ship[enemyamount];

	midseperator.setSize(sf::Vector2f(2*windowSize.x/3,1));
	midseperator.setFillColor(sf::Color::Black);
	midseperator.setPosition(0,windowSize.y/2);

	playArea.setSize(sf::Vector2f(2*windowSize.x/3,windowSize.y));
	playArea.setFillColor(sf::Color::White);
	playArea.setPosition(0,0);

	if(!playerTexture.loadFromFile("playerSprite.png")){
	}
	if(!playerBulletTexture.loadFromFile("redLaserRay.png")){
	}
	if(!font.loadFromFile("times.ttf")){
	}
	if(!enemyTexture.loadFromFile("enemySprite.png")){
	}

	enemySprite.setTexture(enemyTexture);
	enemySprite.setScale(0.1,0.1);
	enemySprite.setPosition(0,0);

	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(12);

	playerBulletSprite.setTexture(playerBulletTexture);
	playerBulletSprite.setScale(.1,.1);

	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(0.05,0.05);
	playerSprite.setPosition(windowSize.x/2, windowSize.y-playerSprite.getGlobalBounds().height);

	player.setposition(sf::Vector2f(windowSize.x/2, windowSize.y-playerSprite.getGlobalBounds().height));
}

void game::run(){
	window.create(sf::VideoMode(windowSize.x, windowSize.y), "FirstTopDownShooter");

	while(window.isOpen()){
		while(window.pollEvent(Event)){
			if (Event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		drawObjects();
		window.display();
	}
}

void game::drawObjects(){
	window.draw(playArea);
	window.draw(midseperator);
	drawPlayer();
	spawnEnemy();
}

void game::drawPlayer(){
	playerInput();
	window.draw(playerSprite);
}

void game::playerInput(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		speed = .05;
	else
		speed = .1;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x >= 0){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y >= windowSize.y/2){
			playerSprite.move(-speed,-speed);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y <= windowSize.y - playerSprite.getGlobalBounds().height){
			playerSprite.move(-speed,speed);
		}
		else{
			playerSprite.move(-speed, 0);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x <= 2*windowSize.x/3 - playerSprite.getGlobalBounds().width){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y >= windowSize.y/2){
			playerSprite.move(speed,-speed);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y <= windowSize.y - playerSprite.getGlobalBounds().height){
			playerSprite.move(speed, speed);
		}
		else{
			playerSprite.move(speed,0);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y >= windowSize.y/2){
		playerSprite.move(0, -speed);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y <= windowSize.y - playerSprite.getGlobalBounds().height){
		playerSprite.move(0, speed);
	}

	player.setposition(playerSprite.getPosition());

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && playerclock.getElapsedTime() >= sf::seconds(.1)){
		for(int i = 0; i < player.maxBullet(); i++){
			if(!player.isactiveBullet(i)){
				player.setactiveBullet(i, true);
				player.shootbullet(i,player.getPosition()+sf::Vector2f(playerSprite.getGlobalBounds().width/2 - playerBulletSprite.getGlobalBounds().width/2,0),sf::Vector2f(0,-playerbulletspeed));
				playerclock.restart();
				break;
			}
		}
	}
	drawplayerBullet();
}

void game::drawplayerBullet(){
	for(int i = 0; i < player.maxBullet(); i++){
		if(player.isactiveBullet(i)){
			playerBulletSprite.setPosition(player.getBulletPosition(i));
			window.draw(playerBulletSprite);
			player.updateBullets();
			if(playerBulletSprite.getPosition().y + playerBulletSprite.getGlobalBounds().height <= 0){
				player.setactiveBullet(i, false);
			}
		}
	}
}

void game::spawnEnemy(){
	if(enemyclock.getElapsedTime() >= sf::seconds(.5)){
		for(int i = 0; i < enemyamount; i++)
			if(enemy[i].getactiveship()){
				enemyclock.restart();
				enemy[i].setactiveship(true);
				enemysidespawn = std::rand()%2;
					if(enemysidespawn){
						enemy[i].setposition(sf::Vector2f(0,std::rand() % int(windowSize.y) / 2));
					}
					else{
						enemy[i].setposition(sf::Vector2f(0,0));
					}
			}
		
	}
	window.draw(enemySprite);
}