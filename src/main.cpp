/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#include "Game.hpp"
#include "BaseScene.hpp"
#include "PlayScene.hpp"
#include "MenuScene.hpp"


using namespace sf;

int main(int argc, char *argv[]){
	BaseScene *scene = new MenuScene();
	Game &g = Game::create(sf::VideoMode(1920, 1080), scene, "Hexcape 0.001-pre-alpha");
	g.run();
	
	return 0;
}


