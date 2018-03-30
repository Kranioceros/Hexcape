#include "Game.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

using namespace std;

Game *Game::instance = nullptr;
Game::Game(){}

Game &Game::create(const sf::VideoMode &videoMode, BaseScene *scene, const string &name){
	if(instance){
		cerr<<"ERROR: can't call create(), game already running."<<endl;
	}else{
		Game & g = getInstance();
		g.window.create(videoMode, name, sf::Style::Fullscreen);
		g.nextScene = nullptr;
		g.currentScene = scene;
		g.window.setFramerateLimit(60);
		g.clock.restart();
	}
	return getInstance();
}


Game &Game::getInstance(){
	if(!instance){
		instance = new Game();
	}
	return *instance;
}

void Game::run(){
  bool evento_nuevo = false;
	while(window.isOpen() && currentScene != nullptr) {
		sf::Event e;
		while(window.pollEvent(e)){
			if(e.type == sf::Event::Closed){
				window.close();
			}
      if(e.type == sf::Event::KeyPressed || e.type == sf::Event::TextEntered)
        evento_nuevo = true;
		}
		draw();
    if (evento_nuevo) {
      update(e);
      evento_nuevo = false;
    } else {
      sf::Event null_ev;
      null_ev.type = sf::Event::Count;
      update(null_ev);
    }
		if(nextScene != nullptr){
			delete currentScene;
			currentScene = nextScene;
			nextScene = nullptr;
		}
	}
	delete currentScene;
}




void Game::update(sf::Event e){
	currentScene->update(clock.getElapsedTime().asSeconds(), e);
	clock.restart();
}


void Game::draw(){
	window.clear(sf::Color(0,0,0,255));
	currentScene->draw(window);
	window.display();
}

void Game::switchScene(BaseScene *scene){
	nextScene = scene;
}

void Game::cerrarJuego() {
	window.close();
}
