#include "headers/Bola.hpp"
#include <cmath>
#include <iostream>
#include "headers/Collision.h"

Bola::Bola(float _x, float _y, float angulo, float _rapidez,  const sf::Texture &_tex, const std::vector<Pared> *_paredes) : tex(_tex) {
	x = _x; y = _y; rapidez = _rapidez;
	velocidad.x = sin(angulo) * rapidez;
	velocidad.y = cos(angulo) * rapidez;
	paredes = _paredes;
	spr.setTexture(tex);
}

void Bola::update(float elapsed) {
	float nuevo_x = x, nuevo_y = y;

	nuevo_x = x + velocidad.x;
	nuevo_y = y + velocidad.y;

	/* Si hubo una colision, calcular el nuevo angulo y posicion */
	auto pared_chocada = paredes->begin();

	/* Mientras haya paredes para revisar Y no haya chocado */
	while(pared_chocada != paredes->end() && Collision::BoundingBoxTest(spr, pared_chocada->verSprite()) == false) {
		pared_chocada++;
	}

	/* Si choco */
	if (pared_chocada != paredes->end()) {
		/* Se obtiene un vector unitario paralelo a la pared */
		float angulo_pared = pared_chocada->verAngulo();
		sf::Vector2f vec_paral(sin(angulo_pared), cos(angulo_pared));

		/* Se obtiene un vector unitario normal a la pared */
		sf::Vector2f vec_normal(vec_paral.y, -vec_paral.x);

		/* Se obtiene el vector velocidad en funcion de los componentes
		 * U y W (vectores normal y paralelo a la pared) */
		float producto_vel_n = velocidad.x*vec_normal.x + velocidad.y*vec_normal.y;
		sf::Vector2f u(producto_vel_n * vec_normal.x, producto_vel_n * vec_normal.y); 

		sf::Vector2f w(velocidad.x - u.x, velocidad.y - u.y);

		sf::Vector2f nueva_vel(w.x - u.x, w.y - u.y);

		/* Se ajusta X e Y de acuerdo a la nueva velocidad */
		velocidad = nueva_vel;
		nuevo_x = x + velocidad.x;
		nuevo_y = y + velocidad.y;
	}

	x = nuevo_x; y = nuevo_y;
	spr.setPosition(x, y);
}

void Bola::draw(sf::RenderWindow &w) {
	w.draw(spr);
}
