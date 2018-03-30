/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

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
	title_text.setString("Hexcape 1.0");
	title_text.setCharacterSize(50);
	title_text.setOrigin(title_text.getLocalBounds().width / 2.0,
							 title_text.getLocalBounds().height / 2.0);
	title_text.setPosition(1920 / 2, 1080 / 2);


	transition_text.setFont(font);
	transition_text.setString("Presiona <Enter> para jugar");
	transition_text.setCharacterSize(24);
	transition_text.setPosition(1920.0 / 2 - transition_text.getGlobalBounds().width / 2.0,
								   1080.0 * 3.0 / 4.0 - transition_text.getGlobalBounds().height / 2.0);

  credits_text.setFont(font);
  credits_text.setString("Copyright 2018\nIgnacio Fucksmann\nRamiro Garay");
  credits_text.setCharacterSize(18);
  sf::Vector2f tam_credits(credits_text.getLocalBounds().width,
                           credits_text.getLocalBounds().height);
  credits_text.setOrigin(tam_credits.x, tam_credits.y);
  credits_text.setPosition(1920-5, 1080-5);

	portal.loadFromFile("assets/portal.png");
	spr_portal.setTexture(portal);
	spr_portal.setOrigin(45, 45);
	spr_portal.setPosition(1920/2,1080/2);
	spr_portal.setScale(20,20);
}

void MenuScene::update(float elapsed, sf::Event e) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		Game::getInstance().switchScene(new TransitionScene(0, 0));
	}
	spr_portal.rotate(2);
}

void MenuScene::draw(sf::RenderWindow &w) {
	w.setView(view);
	w.draw(spr_portal);
	w.draw(title_text);
	w.draw(transition_text);
  w.draw(credits_text);
}
