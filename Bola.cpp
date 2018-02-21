#include "headers/Bola.hpp"
#include <cmath>
#include <iostream>
#include "headers/Collision.h"

Bola::Bola(float _x, float _y, float _angulo, float _velocidad,  const sf::Texture &_tex, const std::vector<Pared> *_paredes) : tex(_tex) {
	x = _x; y = _y; angulo = _angulo;
	velocidad = _velocidad; paredes = _paredes;
	spr.setTexture(tex);
}

void Bola::update(float elapsed) {
	float nuevo_x = x, nuevo_y = y;

	nuevo_x = x + velocidad * sin(angulo);
	nuevo_y = y + velocidad * cos(angulo);

	/* Si hubo una colision, calcular el nuevo angulo y posicion */
	auto pared_chocada = paredes->begin();

	/* Mientras haya paredes para revisar Y no haya chocado */
	while(pared_chocada != paredes->end() && Collision::BoundingBoxTest(spr, pared_chocada->verSprite()) == false) {
		pared_chocada++;
	}

	/* Si choco */
	if (pared_chocada != paredes->end()) {
		nuevo_x = x + velocidad * sin(angulo + 3.14159/8.0);
		nuevo_y = y + velocidad * cos(angulo + 3.14159/8.0);
		angulo = angulo + 3.14159/8.0;
	}

	x = nuevo_x; y = nuevo_y;
	spr.setPosition(x, y);
}

void Bola::draw(sf::RenderWindow &w) {
	w.draw(spr);
}
