#include "headers/Player.hpp"
#include "headers/Collision.h"
#include "headers/GameOverScene.hpp"
#include "headers/PlayScene.hpp"
#include "headers/Game.hpp"
#include <cmath>
#include <iostream>

Player::Player(unsigned int x, unsigned int y, const std::vector<Pared> *p, const std::vector<Bola*> *_bolas,
		const sf::Sprite &_spr_portal) : spr_portal(_spr_portal) {

	tex.loadFromFile("assets/player_spritesheet.png"); spr.setTexture(tex);
	spr.setPosition(x, y);

	tex_muerto.loadFromFile("assets/player_muerto.png");

	hitbox_tex.loadFromFile("assets/akira_hitbox.png");
	hitbox_spr.setTexture(hitbox_tex);
	hitbox_spr.setOrigin(10, 10);
	hitbox_spr.setPosition(x, y);

	offset.x = 0; offset.y = 0;

	paredes = p;
	bolas = _bolas;

	dir = 4;
	anim = 0;
	seMueve = false;
	estado = JUGANDO;
	spr.setTextureRect(sf::IntRect(30*dir, 0, 30, 30));
	spr.setOrigin(15, 15);

	clock_cambiar_anim.restart();
	velocidad = 100;
}

void Player::update(float elapsed){
	if (estado == JUGANDO) {
		moverse();
	}
}
void Player::draw(sf::RenderWindow &w){
	w.draw(spr);
}

const sf::Vector2f Player::verPosicion() const {
	return spr.getPosition();
}

const sf::Vector2f Player::verOffset() const {
	return offset;
}

bool Player::chocoBola() {
	auto bola = bolas->begin();
	while(bola != bolas->end() && Collision::BoundingBoxTest(hitbox_spr, (*bola)->getSprite()) == false) {
		bola++;	
	}

	if(bola != bolas->end())
		return true;
	else
		return false;
}

void Player::moverse() {
	offset.x = offset.y = 0;

	sf::Vector2f coord = spr.getPosition();
	sf::Vector2f offset_viejo = offset;
	
	float mov = 6;
	float mov_cat = sqrt(mov*mov/2);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		seMueve = true;
		// NO
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			dir = 7;
			spr.move(-mov_cat, -mov_cat);
			hitbox_spr.move(-mov_cat, -mov_cat);
			offset.x -= mov_cat; offset.y -= mov_cat;
			
			// SO
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			dir = 5; spr.move(-mov_cat, mov_cat); hitbox_spr.move(-mov_cat, mov_cat);
			offset.x -= mov_cat; offset.y += mov_cat;
		} else {
			// O
			dir = 6;
			hitbox_spr.move(-mov, 0);
			spr.move(-mov, 0);
			offset.x -= mov;
		}
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		seMueve = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			dir = 1;
			spr.move(mov_cat, -mov_cat);
			hitbox_spr.move(mov_cat, -mov_cat);
			offset.x += mov_cat; offset.y -= mov_cat;
		// SE
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			dir = 3;
			spr.move(mov_cat, mov_cat);
			hitbox_spr.move(mov_cat, mov_cat);
			offset.x += mov_cat; offset.y += mov_cat;
		// E
		} else {
			dir = 2;
			hitbox_spr.move(mov, 0);
			spr.move(mov, 0);
			offset.x += mov;
		}
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		// N
		dir = 0;
		seMueve = true;
		spr.move(0, -mov);
		hitbox_spr.move(0, -mov);
		offset.y -= mov;
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		// S
		seMueve = true;
		dir = 4;
		spr.move(0, mov);
		hitbox_spr.move(0, mov);
		offset.y += mov;
	} else {
		// No se mueve
		seMueve = false;
	}

	/* Codigo para detectar colisiones */
	
	bool ha_chocado = false;
	auto pared = paredes->begin();
	
	/* Mientras haya paredes Y no haya chocado */
	while(pared != paredes->end() && Collision::BoundingBoxTest(hitbox_spr, pared->verSprite()) == false) {
		pared++;
	}
	
	if (pared != paredes->end()) {
		ha_chocado = true;
	}
		
	if (ha_chocado) {
		spr.setPosition(coord);
		hitbox_spr.setPosition(coord.x+5, coord.y+5);
		offset = offset_viejo;
	}

	/* Se cambia el fotograma si el tiempo ocurrido es mayor a velocidad */
	sf::Time tiempo_ocurrido = clock_cambiar_anim.getElapsedTime();
	if (tiempo_ocurrido.asMilliseconds() > velocidad) {
		anim = (anim + 1) % 3;
		clock_cambiar_anim.restart();
	}

	/* Se actualiza el sprite en base a la rotacion del personaje y su
	 * movimiento */
	if (seMueve) {
		spr.setTextureRect(sf::IntRect(30*dir, 30*anim, 30, 30));
	} else {
		spr.setTextureRect(sf::IntRect(30*dir, 30, 30, 30));
	}

	/* Si el jugador choco con una bola, MUERE */
	if (chocoBola()) {
		estado = MUERTO;
		offset.x = offset.y = 0;
		spr.setTexture(tex_muerto, true);
	}

	/* Si el jugador choco con el portal, GANA (se usa deteccion de colisiones
	 * entre circulo y cuadrado */
	sf::Vector2f pos_portal = spr_portal.getPosition();
	sf::Vector2f pos_player = spr.getPosition();
	sf::Vector2i closest_point(pos_player.x - 15, pos_player.y - 15);
	sf::Vector2i closest_dist(abs(pos_player.x - pos_portal.x), abs(pos_player.y - pos_portal.y));

	for(int x=closest_point.x; x < pos_player.x + 15; x++) {
		int dist_x = abs(x - pos_portal.x); 
		if( dist_x < closest_dist.x) {
			closest_point.x = x;
			closest_dist.x = dist_x;
		}
	}

	for(int y=closest_point.y; y < pos_player.y + 15; y++) {
		int dist_y = abs(y - pos_portal.y); 
		if( dist_y < closest_dist.y) {
			closest_point.y = y;
			closest_dist.y = dist_y;
		}
	}

	if ( closest_dist.x*closest_dist.x + closest_dist.y*closest_dist.y < 15*15 ) {
		estado = GANO;
		offset.x = offset.y = 0;
	}
}

Player::~Player() {

}
