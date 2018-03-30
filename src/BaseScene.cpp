/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#include "BaseScene.hpp"
#include <vector>

BaseScene::BaseScene() {
	
}

void BaseScene::update(float elapsed, sf::Event e) {	
	for(auto e: entities){
		e->update(elapsed);
	}
	
	// elimina actores
	for(auto d: to_delete){
		auto it = find(entities.begin(), entities.end(), d);
		if(it != entities.end()){
			delete *it;
			entities.erase(it);
		}
	}
	to_delete.clear();
}

void BaseScene::draw(sf::RenderWindow &w){
	for(auto e: entities){
		e->draw(w);
	}
}

void BaseScene::add(Entity *e){
	entities.push_back(e);
}

void BaseScene::remove(Entity *e){
	to_delete.push_back(e);
}

