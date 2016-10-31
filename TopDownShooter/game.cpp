#include "game.h"

game::game(){
	init();
	run();
}

void game::init(){
	windowSize = sf::Vector2f(800,600);
	speed = .1;
	enemyamount = 1;
	playerbulletspeed = .1;
	enemybulletspeed = .01;
	enemy = new ship[enemyamount];
	enemyspeed = .1;
	enemyspawnrate = .5;
	enemybulletrate = .05;

	midseperator.setSize(sf::Vector2f(2*windowSize.x/3,1));
	midseperator.setFillColor(sf::Color::Black);
	midseperator.setPosition(0,windowSize.y/2);

	sideBar.setSize(sf::Vector2f(windowSize.x/3,windowSize.y));
	sideBar.setFillColor(sf::Color::Black);
	sideBar.setPosition(2*windowSize.x/3,0);

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
	text.setPosition(0,0);

	playerBulletSprite.setTexture(playerBulletTexture);
	playerBulletSprite.setScale(.1,.1);

	enemyBulletSprite.setTexture(playerBulletTexture);
	enemyBulletSprite.setScale(.1,.1);
	enemyBulletSprite.setColor(sf::Color::Green);

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
		window.clear(sf::Color::White);
		drawObjects();
		window.display();
	}
}

void game::drawObjects(){
	window.draw(midseperator);
	drawPlayer();
	spawnEnemy();
	updateEnemy();
	window.draw(sideBar);
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
			if(!enemy[i].getactiveship()){
				enemyclock.restart();
				enemy[i].resetClock();
				enemy[i].setactiveship(true);
				enemysidespawn = std::rand()%2;
				if(enemysidespawn){
					enemy[i].setposition(sf::Vector2f(0-enemySprite.getGlobalBounds().width,std::rand() % int(int(windowSize.y) / 2 - enemySprite.getGlobalBounds().height)));
					enemy[i].setenemyDir(sf::Vector2f(enemyspeed, 0));
				}
				else{
					enemy[i].setposition(sf::Vector2f(2*windowSize.x/3,std::rand() % int(int(windowSize.y) / 2 - enemySprite.getGlobalBounds().height)));
					enemy[i].setenemyDir(sf::Vector2f(-enemyspeed, 0));
				}
				break;
			}
	}
}

void game::updateEnemy(){
	for(int i = 0; i < enemyamount; i++){
		if(enemy[i].getactiveship()){
			enemy[i].setactiveship(true);
			enemySprite.setPosition(enemy[i].getPosition());
			window.draw(enemySprite);
			enemy[i].updateEnemy();
			if((enemy[i].getPosition().x < 0-enemySprite.getGlobalBounds().width || enemy[i].getPosition().x > 2*windowSize.x/3 + enemySprite.getGlobalBounds().width)){
				enemy[i].setactiveship(false);
			}
		}
		shootenemybullet(i);
		for(int j = 0; j < enemy[i].maxBullet(); j++){
			if(enemy[i].isactiveBullet(i)){
				enemyBulletSprite.setPosition(enemy[i].getBulletPosition(j));
				window.draw(enemyBulletSprite);
				enemy[i].updateBullets();
				if(enemyBulletSprite.getPosition().y + enemyBulletSprite.getGlobalBounds().height >= windowSize.y){
					enemy[i].setactiveBullet(j, false);
				}
			}
		}
	}
}

void game::shootenemybullet(int value){
	for(int i = 0; i < enemy[value].maxBullet(); i++){
		if(!enemy[value].isactiveBullet(i) && enemy[value].getClock().getElapsedTime() >= sf::seconds(enemybulletrate) && enemy[value].getactiveship()){
			enemy[value].setactiveBullet(i, true);
			enemy[value].shootbullet(i,enemy[i].getPosition()+sf::Vector2f(enemySprite.getGlobalBounds().width/2 - enemyBulletSprite.getGlobalBounds().width/2,0),sf::Vector2f(0,enemybulletspeed));
			break;
		}
	}
}