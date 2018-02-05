#include "headers/PlayScene.hpp"
#include "headers/Laberinto.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

PlayScene::PlayScene() : lab(0, 0, 0, 10, 10) {

}


void PlayScene::update(float elapsed){

}

void PlayScene::draw(sf::RenderWindow &w){
	lab.DibujarLab(w, 0, 0);
}
