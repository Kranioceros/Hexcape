#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Pared.hpp"
#include "Bola.hpp"
#include <vector>
#include <deque>

class Player : public Entity {
private:

	enum Estado_Player {MUERTO, JUGANDO, GANO} estado;

	sf::Texture tex;
	sf::Texture tex_muerto;
	sf::Texture hitbox_tex;
	sf::Sprite spr;
	sf::Sprite hitbox_spr;
	const std::vector<Pared> *paredes;
	const std::deque<Bola*> *bolas;
	sf::Vector2f offset;

	const sf::Sprite& spr_portal;

	unsigned int dir, anim;
	bool seMueve;	
	sf::Clock clock_cambiar_anim;
	float velocidad, tiempo_muerto, tiempo_victoria;
public:
	Player(unsigned int x, unsigned int y, const std::vector<Pared> *p, const std::deque<Bola*> *_bolas,
		const sf::Sprite& _portal);
	~Player();
	void update(float elapsed) override;
	void draw(sf::RenderWindow &w) override;
	bool chocoBola();
	const sf::Vector2f verPosicion() const;
	const sf::Vector2f verOffset() const;
	void moverse();
	Estado_Player verEstado(){ return estado; }
	
};

#endif
