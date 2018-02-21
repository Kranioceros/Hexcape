#include "headers/Player.hpp"
#include "headers/Collision.h"
#include <cmath>
#include <iostream>

Player::Player(unsigned int x, unsigned int y, const std::vector<Pared> *p) {
	tex.loadFromFile("assets/akira.png");
	spr.setTexture(tex);
	spr.setOrigin(15, 15);
	spr.setPosition(x, y);

	hitbox_tex.loadFromFile("assets/akira_hitbox.png");
	hitbox_spr.setTexture(hitbox_tex);
	hitbox_spr.setOrigin(10, 10);
	hitbox_spr.setPosition(x, y);

	offset.x = 0; offset.y = 0;

	paredes = p;
}

void Player::update(float elapsed){
	offset.x = offset.y = 0;

	sf::Vector2f coord = spr.getPosition();
	sf::Vector2f offset_viejo = offset;
	
	float mov = 6;
	float mov_cat = sqrt(mov*mov/2);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		// NO
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			spr.move(-mov_cat, -mov_cat);
			hitbox_spr.move(-mov_cat, -mov_cat);
			offset.x -= mov_cat; offset.y -= mov_cat;
			
			// SO
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			spr.move(-mov_cat, mov_cat);
			hitbox_spr.move(-mov_cat, mov_cat);
			offset.x -= mov_cat; offset.y += mov_cat;
		} else {
			// O
			hitbox_spr.move(-mov, 0);
			spr.move(-mov, 0);
			offset.x -= mov;
		}
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		// NE
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			spr.move(mov_cat, -mov_cat);
			hitbox_spr.move(mov_cat, -mov_cat);
			offset.x += mov_cat; offset.y -= mov_cat;
		// SE
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			spr.move(mov_cat, mov_cat);
			hitbox_spr.move(mov_cat, mov_cat);
			offset.x += mov_cat; offset.y += mov_cat;
		// E
		} else {
			hitbox_spr.move(mov, 0);
			spr.move(mov, 0);
			offset.x += mov;
		}
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		// N
		spr.move(0, -mov);
		hitbox_spr.move(0, -mov);
		offset.y -= mov;
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		// S
		spr.move(0, mov);
		hitbox_spr.move(0, mov);
		offset.y += mov;
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
