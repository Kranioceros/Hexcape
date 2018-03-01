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
	float tiempo_spawn;
	enum {SPAWNING, NORMAL} estado;
	sf::Vector2f velocidad;
	const std::vector<Pared> *paredes;

	sf::Clock clock_spawn;

	void moverse();
	
public:
	Bola(float _x, float _y, float angulo, float _rapidez, float _tiempo_spawn, const sf::Texture &_tex, const std::vector<Pared> *_paredes);
	~Bola();
	void update(float elapsed) override;
	void draw(sf::RenderWindow &w) override;
	bool existe() const; // devuelve true si esta en estado NORMAL
	const sf::Sprite& getSprite() const;
};

#endif
