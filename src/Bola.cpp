#include "Bola.hpp"
#include <cmath>
#include <iostream>
#include "Collision.hpp"

Bola::Bola(float _x, float _y, float angulo, float _rapidez, float _tiempo_spawn, const sf::Texture &_tex, const std::vector<Pared> *_paredes) : tex(_tex) {
	x = _x; y = _y; rapidez = _rapidez;
	paredes = _paredes;
	tiempo_spawn = _tiempo_spawn;
	estado = SPAWNING;
	desaparecida = false;
	se_dibuja = true;


	velocidad.x = sin(angulo) * rapidez;
	velocidad.y = cos(angulo) * rapidez;
	spr.setPosition(x, y);
	spr.setTexture(tex);
	clock_spawn.restart();
	clock_intermitencia.restart();
	clock_desapareciendo.restart();
}

void Bola::update(float elapsed) {
	switch(estado) {
		case NORMAL:
		moverse();
		break;

		case SPAWNING:
		{
		sf::Time tiempo = clock_spawn.getElapsedTime();
		if (tiempo.asMilliseconds() > tiempo_spawn)
			estado = NORMAL;
		}
		break;

		case DESAPARECIENDO:
		{
		moverse();

		float msegundos_intermitencia = clock_intermitencia.getElapsedTime().asMilliseconds();
		if (msegundos_intermitencia > 180) {
			se_dibuja = se_dibuja ? false : true;
			clock_intermitencia.restart();
		}

		float segundos_desapareciendo = clock_desapareciendo.getElapsedTime().asSeconds();
		if (segundos_desapareciendo > 2) {
			desaparecida = true;
		}
		}
		break;
	}
}

void Bola::draw(sf::RenderWindow &w) {
	if (estado != SPAWNING && se_dibuja) {
		w.draw(spr);
	}
}

void Bola::moverse() {
	float nuevo_x = x, nuevo_y = y;

	nuevo_x = x + velocidad.x;
	nuevo_y = y + velocidad.y;
	sf::Vector2f nueva_vel = velocidad;

	/* Si hubo una colision, calcular el nuevo angulo y posicion */
	auto pared_chocada = paredes->begin();

	/* Mientras haya paredes para revisar Y no haya chocado */
	while(pared_chocada != paredes->end() &&
	Collision::BoundingBoxTest(spr, pared_chocada->verSprite()) == false)
	{
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

		nueva_vel.x = w.x - u.x;
		nueva_vel.y = w.y - u.y;

		/* Se calculan las nuevas coordenadas y se mueve al sprite */
		nuevo_x = x + nueva_vel.x;
		nuevo_y = y + nueva_vel.y;
		spr.setPosition(nuevo_x, nuevo_y);

		/* Si la nueva velocidad lleva a la bola a una posicion invalida, se
		 * la descarta y se toma la direccion contraria */
		pared_chocada = paredes->begin();

		while(pared_chocada != paredes->end() &&
		Collision::BoundingBoxTest(spr, pared_chocada->verSprite()) == false)
		{
			pared_chocada++;
		}

		/* La nueva posicion es invalida */
		if (pared_chocada != paredes->end()) {
			nueva_vel.x = -velocidad.x;
			nueva_vel.y = -velocidad.y;

			nuevo_x = x + nueva_vel.x;
			nuevo_y = y + nueva_vel.y;
		}
		/* La nueva posicion es valida y no se cambia la nueva velocidad */
	}

	velocidad = nueva_vel;
	x = nuevo_x; y = nuevo_y;

	spr.setPosition(x, y);

}

const sf::Sprite& Bola::getSprite() const {
	return spr;
}

bool Bola::existe() const {
	return estado != SPAWNING;
}

Bola::~Bola() {
}

bool Bola::desaparecio() const {
	return desaparecida;
}

bool Bola::desapareciendo() const {
	return estado == DESAPARECIENDO;
}

void Bola::desaparecer() {
	if (estado != DESAPARECIENDO) {
		estado = DESAPARECIENDO;
		clock_desapareciendo.restart();
		clock_intermitencia.restart();
	}
}
