#ifndef ESCOTILLA_H
#define ESCOTILLA_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Bola.hpp"
#include "Pared.hpp"
#include <vector>

class Escotilla : public Entity {
private:
	sf::Texture &tex;
	sf::Texture &tex_bola;
	sf::Sprite spr;

	sf::Clock clock_cambiar_anim;
	float velocidad, rapidez;
	const std::vector<Pared>* paredes;
	enum {CERRADO, ABRIENDO, ABIERTO, CERRANDO} estado;
	unsigned int progreso_anim, ticks_abierto;
	void cambiarAnim();
public:
	Escotilla(unsigned int x, unsigned int y, float _rapidez, const std::vector<Pared>* _paredes,
			sf::Texture &_tex, sf::Texture &_tex_bola);
	~Escotilla();
	void update(float elapsed) override;
	void draw(sf::RenderWindow &w) override;
	Bola* spawn();
};

#endif
