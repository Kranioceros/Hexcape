/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "BaseScene.hpp"
using namespace std;


/***
 * Clase para manejar un bucle de juego con distintas escenas
 */
class Game {
public:
	/// comenzar el bucle de juego
	void run();
	
	/// cambiar la escena actual por otra 
	void switchScene(BaseScene *scene);

	/// cierra la escena actual y termina el juego
	void cerrarJuego();
	
	/// obtener la instancia de juego (singleton)
	static Game &getInstance();
	
	/// crear un juego especificando el modo de video y la escena inicial
	static Game &create(const sf::VideoMode &videoMode, BaseScene *scene, const string &name = "");

private:	
	sf::RenderWindow window;
	BaseScene *currentScene, *nextScene;
	sf::Clock clock;
	
	void processEvents();
	void update(sf::Event e);
	void draw();
	static Game *instance;
	Game();
};

#endif

