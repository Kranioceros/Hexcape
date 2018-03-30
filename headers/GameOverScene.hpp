/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#ifndef GAMEOVER_SCENE_HPP
#define GAMEOVER_SCENE_HPP
#include "BaseScene.hpp"
#include "TablaPuntajes.hpp"

#include <SFML/Graphics.hpp>

class GameOverScene: public BaseScene {
private:
	sf::Text game_over_text;
	sf::Font font;
	sf::View view;
	sf::Text score_text;
	unsigned int puntos_jugador;
  TablaPuntaje tabla;

public:
	GameOverScene(unsigned int _puntos_jugador);
	void update(float elapsed, sf::Event e) override;
	void draw(sf::RenderWindow &w) override;
};

#endif
