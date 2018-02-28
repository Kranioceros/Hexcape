#include "headers/PlayScene.hpp"
#include "headers/Laberinto.h"
#include "headers/Game.hpp"
#include "headers/GameOverScene.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <cstdlib>

PlayScene::PlayScene(float _tiempo_spawn_bolas) : lab(time(nullptr), 0, 0, 5, 5, 0.02) {
	bola.loadFromFile("assets/bola2.png");
	escotilla.loadFromFile("assets/escotillas-516x86.png");
	portal.loadFromFile("assets/portal.png");
	tiempo_spawn_bolas = _tiempo_spawn_bolas;

	tiempo_muerto = 3000;
	tiempo_victoria = 3000;
	player = new Player(200, 200, &lab.verParedes(), &bolas, spr_portal);
	add(player);	

	view.reset(sf::FloatRect(0, 0, 1920, 1080));	
	view.setCenter(player->verPosicion().x, player->verPosicion().y);
	view.zoom(0.5);

	bolas_clock.restart();
	max_bolas = 30;

	const float lado = 150, altura_lado = 130;
	const float ancho = 2*altura_lado;

	/* Se agregan las escotillas */
	for(unsigned int fila=0; fila < lab.VerGrilla().alto(); fila++) {
		for(unsigned int col=0; col < lab.VerGrilla().ancho(); col++) {

			int xr = col*ancho + fila*altura_lado;
			int yr = fila*(3.0/2)*lado;

			/* Que no ponga la ultima escotilla (ahi va el portal) */
			if(escotillas.size() < lab.VerGrilla().ancho() * lab.VerGrilla().alto() - 1) {
				Escotilla* ptr_escotilla =
				new Escotilla(xr+altura_lado, yr+lado, 2, &lab.verParedes(), escotilla, bola);
				escotillas.push_back(ptr_escotilla);
			}
		}
	}

	/* Se agrega el portal al final de la escena */
	spr_portal.setTexture(portal);
	spr_portal.setOrigin(45, 45);
	spr_portal.setPosition((lab.VerGrilla().ancho()-1)*ancho + (lab.VerGrilla().alto()-1)*altura_lado + altura_lado					,(lab.VerGrilla().alto()-1)*(3.0/2)*lado+lado);
}

void PlayScene::update(float elapsed){
	sf::Time bolas_time = bolas_clock.getElapsedTime();

	/* Se agregan nuevas bolas dependiendo del timer */
	if(bolas_time.asSeconds() > tiempo_spawn_bolas) {
		bolas_clock.restart();
		Bola* nueva_bola = escotillas[rand() % escotillas.size()]->spawn();
		if (nueva_bola != nullptr) {
			add(nueva_bola);
			bolas.push_back(nueva_bola);
		}
		
		/* Si son muchas, se empiezan a borrar las mas viejas */
		if (bolas.size() >= max_bolas) {
			bolas.erase(bolas.begin());
			remove(*bolas.begin());
		}
	}
	/* Se actualizan todas las entidades */
	for(auto &e : escotillas)
		e->update(elapsed);

	spr_portal.rotate(2);

	BaseScene::update(elapsed);
	view.move(player->verOffset());

	/* Si el jugador perdio/gano, se cambia de escena */
	switch(player->verEstado()) {
		case 1: // Jugando
		tiempo_player.restart();
		break;

		case 0: // Muerto
		{
		sf::Time tiempo = tiempo_player.getElapsedTime();
		if(tiempo.asMilliseconds() > tiempo_muerto)
			Game::getInstance().switchScene(new GameOverScene());
		}
		break;

		case 2: // Gano
		{
		sf::Time tiempo = tiempo_player.getElapsedTime();
		if(tiempo.asMilliseconds() > tiempo_victoria)
			Game::getInstance().switchScene(new PlayScene(0.2));
		}
		break;

	}
}

void PlayScene::draw(sf::RenderWindow &w){
	w.setView(view);
	lab.DibujarLab(w, 0, 0);
	for(auto &e : escotillas)
		e->draw(w);
	w.draw(spr_portal);

	/* Se dibujan las entidades */
	BaseScene::draw(w);
}

PlayScene::~PlayScene() {
	for (auto &e : escotillas)
		delete e;
	for (auto &b : bolas)
		delete b;
	remove(player);
}
