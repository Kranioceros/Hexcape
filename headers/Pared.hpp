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
