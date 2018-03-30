/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#ifndef MENUSCENE_H
#define MENUSCENE_H
#include "BaseScene.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class MenuScene : public BaseScene {
private:
	sf::Text title_text;
	sf::Text transition_text;
  sf::Text credits_text;
	sf::Font font;
	sf::View view;
	sf::Texture portal;
	sf::Sprite spr_portal;

public:
	MenuScene();
	void update(float elapsed, sf::Event e) override;
	void draw(sf::RenderWindow &w) override;
};

#endif

