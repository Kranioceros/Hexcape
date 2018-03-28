#include "GameOverScene.hpp"
#include "Game.hpp"
#include "PlayScene.hpp"
#include "TransitionScene.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

GameOverScene::GameOverScene(unsigned int _puntos_jugador) : tabla("leaderboard.bin", _puntos_jugador) {
	puntos_jugador = _puntos_jugador;

	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	view.setCenter(1920 / 2, 1080 / 2);
	view.zoom(1);

	stringstream ss;
	ss << "YOU DIED";

	font.loadFromFile("fonts/munro.ttf");
	game_over_text.setFont(font);
	game_over_text.setString(ss.str());
	game_over_text.setCharacterSize(80);
	game_over_text.setOrigin(game_over_text.getLocalBounds().width / 2.0,
                           game_over_text.getLocalBounds().height / 2.0);
	game_over_text.setPosition(1920 / 2, 1080 / 4);
}

void GameOverScene::update(float elapsed, sf::Event e) {
  tabla.actualizar(e);
	if(tabla.quiereSalir()) {
    tabla.escribirPuntaje();
		Game::getInstance().switchScene(new TransitionScene(0, 0));
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    tabla.escribirPuntaje();
		Game::getInstance().cerrarJuego();
	}
}

void GameOverScene::draw(sf::RenderWindow &w) {
	w.setView(view);
  tabla.dibujar(1920 / 2, 1080 / 2, w);
	w.draw(game_over_text);
  //w.draw(score_text);
}
