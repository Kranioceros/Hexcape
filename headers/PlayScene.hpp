#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP

#include <SFML/Graphics.hpp>
#include "Laberinto.h"
#include "BaseScene.hpp"
#include "Player.hpp"
#include "Bola.hpp"

class PlayScene: public BaseScene {
private:
	Laberinto lab;
	Player player;
	sf::View view;
	sf::Texture bola;

	vector<Bola> bolas;
	sf::Clock bolas_clock;
	float tiempo_spawn_bolas;
public:
	PlayScene(float _tiempo_spawn_bolas);
	void update(float elapsed);
	void draw(sf::RenderWindow &w);
};

#endif
