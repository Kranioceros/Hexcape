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


