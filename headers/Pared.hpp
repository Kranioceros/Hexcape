/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#ifndef PARED_H
#define PARED_H

#include <SFML/Graphics.hpp>

class Pared {
private:
	unsigned int xh, yh, tipo_pared;
	const sf::Texture &tex;
	float angulo;
	sf::Sprite spr_pared;

public:
	Pared(unsigned int _xh, unsigned int _yh, unsigned int _tipo_pared, const sf::Texture &_tex);
	Pared(const Pared &p);
	const sf::Sprite &verSprite() const;
	const float verAngulo() const;
};

#endif
