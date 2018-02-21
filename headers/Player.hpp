#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Pared.hpp"
#include <vector>

class Player : public Entity {
private:
	sf::Texture tex;
	sf::Texture hitbox_tex;
	sf::Sprite spr;
	sf::Sprite hitbox_spr;
	const std::vector<Pared> *paredes;
	sf::Vector2f offset;
	
public:
	Player(unsigned int x, unsigned int y, const std::vector<Pared> *p);
	void update(float elapsed) override;
	void draw(sf::RenderWindow &w) override;
	const sf::Vector2f verPosicion() const;
	const sf::Vector2f verOffset() const;
};

#endif
