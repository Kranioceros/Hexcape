#include "TransitionScene.h"

#include "Game.hpp"
#include "PlayScene.hpp"
TransitionScene::TransitionScene() {
	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	view.setCenter(1920 / 2, 1080 / 2);
	view.zoom(1);
	
	nro_nivel = 1;
	
	font.loadFromFile("fonts/munro.ttf");
	title_text.setFont(font);
	title_text.setString("nivel: " nro_nivel);
	title_text.setCharacterSize(50);
	title_text.setOrigin(title_text.getLocalBounds().width / 2.0,
						 title_text.getLocalBounds().height / 2.0);
	title_text.setPosition(1920 / 2, 1080 / 2);
}
void TransitionScene::update(float elapsed) {
	sf::Time tiempo_espera = espera_clock.getElapsedTime();
	if(tiempo_espera.asSeconds() > 4) {
		espera_clock.restart();
		nro_nivel=nro_nivel+1;
		Game::getInstance().switchScene(new PlayScene(0.2));
	}
}

void TransitionScene::draw(sf::RenderWindow &w) {
	w.setView(view);
	w.draw(title_text);
	
	
	
}


