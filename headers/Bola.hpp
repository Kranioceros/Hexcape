#ifndef BOLA_HPP
#define BOLA_HPP

#include "Entity.hpp"
#include "Pared.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Bola : public Entity {
private:
	const sf::Texture &tex;
	sf::Sprite spr;
	float x, y, rapidez;
	sf::Vector2f velocidad;
	const std::vector<Pared> *paredes;
	
public:
	Bola(float _x, float _y, float angulo, float _rapidez, const sf::Texture &_tex, const std::vector<Pared> *_paredes);
	virtual void update(float elapsed) override;
	virtual void draw(sf::RenderWindow &w) override;
};

#endif
