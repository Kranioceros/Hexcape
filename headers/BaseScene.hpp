/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#ifndef BASESCENE_HPP
#define BASESCENE_HPP
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entity.hpp"
#include <vector>
using namespace std;


/***
 * Representa una escena del juego.
 * Para crear una nueva clase de escena, heredar de ésta clase
 * y redefinir el comportamiento de los métodos
 */ 
class BaseScene {
public:
	/// constructor
	BaseScene();
	
	/// función que será invocada para actualizar la escena
	virtual void update(float elapsed, sf::Event e);
	
	/// función que será invocada para dibujar la escena
	virtual void draw(sf::RenderWindow &w);

	/// agrega un nuevo actor a la escena
	void add(Entity *e);
	
	/// eliminar un actor de la escena
	void remove(Entity *e);

	/// destructor virtual, por si se necesita hacer algo especial
	virtual ~BaseScene() {}
private:
	vector<Entity *> entities;
	vector<Entity *> to_delete;
};

#endif

