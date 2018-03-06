#include "GameOverScene.hpp"
#include "Game.hpp"
#include "PlayScene.hpp"
#include "TransitionScene.h"
#include <iostream>
#include <sstream>

GameOverScene::GameOverScene(unsigned int _puntos_jugador) {
	puntos_jugador = _puntos_jugador;

	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	view.setCenter(1920 / 2, 1080 / 2);
	view.zoom(1);

	stringstream ss;
	ss << "YOU DIED\n" << puntos_jugador << std::endl;

	font.loadFromFile("fonts/munro.ttf");
	game_over_text.setFont(font);
	game_over_text.setString(ss.str());
	game_over_text.setCharacterSize(32);
	game_over_text.setOrigin(game_over_text.getLocalBounds().width / 2.0,
				game_over_text.getLocalBounds().height / 2.0);
	game_over_text.setPosition(1920 / 2, 1080 / 2);

	instrucciones_text.setFont(font);
	instrucciones_text.setString("Presiona <Enter> para reiniciar\nPresiona <Esc> para salir");
	instrucciones_text.setCharacterSize(24);
	instrucciones_text.setPosition(1920.0 / 2 - instrucciones_text.getGlobalBounds().width / 2.0,
				   1080.0 * 3.0 / 4.0 - instrucciones_text.getGlobalBounds().height / 2.0);

}

void GameOverScene::update(float elapsed) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		Game::getInstance().switchScene(new TransitionScene(0, 0));
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		Game::getInstance().cerrarJuego();
	}
}

void GameOverScene::draw(sf::RenderWindow &w) {
	w.setView(view);
	w.draw(game_over_text);
	w.draw(instrucciones_text);
}
