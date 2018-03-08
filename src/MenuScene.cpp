#include "MenuScene.hpp"
#include "Game.hpp"
#include "PlayScene.hpp"
#include "TransitionScene.hpp"
#include <iostream>
MenuScene::MenuScene() {
	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	view.setCenter(1920 / 2, 1080 / 2);
	view.zoom(1);
	
	font.loadFromFile("fonts/munro.ttf");
	title_text.setFont(font);
	title_text.setString("HEXCAPE 0.1");
	title_text.setCharacterSize(50);
	title_text.setOrigin(title_text.getLocalBounds().width / 2.0,
							 title_text.getLocalBounds().height / 2.0);
	title_text.setPosition(1920 / 2, 1080 / 2);
	
	
	transition_text.setFont(font);
	transition_text.setString("Presiona <Enter> para jugar");
	transition_text.setCharacterSize(24);
	transition_text.setPosition(1920.0 / 2 - transition_text.getGlobalBounds().width / 2.0,
								   1080.0 * 3.0 / 4.0 - transition_text.getGlobalBounds().height / 2.0);
	
	portal.loadFromFile("assets/portal.png");
	spr_portal.setTexture(portal);
	spr_portal.setOrigin(45, 45);
	spr_portal.setPosition(1920/2,1080/2);
	spr_portal.setScale(20,20);
	
	if (!devilman.openFromFile("sounds/devilman-no-uta.ogg")){
	std::cout<<"no abrio devilmannouta"<<std::endl;
	}
}

void MenuScene::update(float elapsed) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		Game::getInstance().switchScene(new TransitionScene(0, 0));
	}
	spr_portal.rotate(2);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		devilman.play();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		devilman.pause();
	}
}

void MenuScene::draw(sf::RenderWindow &w) {
	w.setView(view);
	w.draw(spr_portal);
	w.draw(title_text);
	w.draw(transition_text);
}
