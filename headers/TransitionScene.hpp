/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#ifndef TRANSITIONSCENE_H
#define TRANSITIONSCENE_H
#include "BaseScene.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class TransitionScene: public BaseScene {
private:
	sf::Text title_text;
	sf::Clock espera_clock;
	sf::Font font;
	sf::View view;
	
	unsigned int nro_nivel;
	unsigned int puntos_jugador;
public:
	TransitionScene(unsigned int _nro_nivel, unsigned int _puntos_jugador);
	void update(float elapsed, sf::Event e) override;
	void draw(sf::RenderWindow &w) override;

};

#endif

