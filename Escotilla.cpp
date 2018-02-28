#include "headers/Escotilla.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>

Escotilla::Escotilla(unsigned int x, unsigned int y, float _rapidez, const std::vector<Pared>* _paredes,
	       sf::Texture &_tex, sf::Texture &_tex_bola) : tex(_tex), tex_bola(_tex_bola) {
	spr.setTexture(tex);
	spr.setTextureRect(sf::IntRect(0, 0, 86, 86));
	spr.setOrigin(43, 43);
	spr.setPosition(x, y);
	estado = CERRADO;
	progreso_anim = 0;
	velocidad = 250;
	rapidez = _rapidez;
	paredes = _paredes;
	ticks_abierto = 4;
	clock_cambiar_anim.restart();
}

void Escotilla::update(float elapsed) {
	sf::Time tiempo = clock_cambiar_anim.getElapsedTime();
	if (tiempo.asMilliseconds() > velocidad) {
		clock_cambiar_anim.restart();
		cambiarAnim();
	}
}

void Escotilla::draw(sf::RenderWindow &w) {
	w.draw(spr);
}

Bola* Escotilla::spawn() {
	if (estado == CERRADO) {
		estado = ABRIENDO;
		sf::Vector2f pos = spr.getPosition();
		return new Bola(pos.x, pos.y, rand() % 361, rapidez, 6*velocidad + velocidad*ticks_abierto/2.0,
				tex_bola, paredes);
	}

	return nullptr;
}

void Escotilla::cambiarAnim() {
	switch(estado) {
		case CERRADO:
		break;

		case ABRIENDO:
		if(progreso_anim < 6) {
			spr.setTextureRect(sf::IntRect(86*progreso_anim, 0, 86, 86));
			progreso_anim++;
		} else {
			estado = ABIERTO;
			progreso_anim = 0;
		}
		break;

		case ABIERTO:
		if (progreso_anim < ticks_abierto) {
			progreso_anim++;	
		} else {
			estado = CERRANDO;
			progreso_anim = 6;
		}
		break;

		case CERRANDO:
		if (progreso_anim > 0) {
			spr.setTextureRect(sf::IntRect(86*(progreso_anim-1), 0, 86, 86));
			progreso_anim--;
		} else {
			estado = CERRADO;
		}
		break;
	}

}
