#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP

#include <SFML/Graphics.hpp>
#include "Laberinto.h"
#include "BaseScene.hpp"

class PlayScene: public BaseScene {
private:
	Laberinto lab;	
public:
	PlayScene();
	void update(float elapsed);
	void draw(sf::RenderWindow &w);
};

#endif
