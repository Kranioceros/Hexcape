#include "headers/PlayScene.hpp"
#include "headers/Laberinto.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <cstdlib>

PlayScene::PlayScene(float _tiempo_spawn_bolas) : lab(0, 0, 0, 10, 10), player(200, 200, &lab.verParedes()) {
	bola.loadFromFile("assets/bola2.png");
	tiempo_spawn_bolas = _tiempo_spawn_bolas;

	view.reset(sf::FloatRect(0, 0, 1920, 1080));	
	view.setCenter(player.verPosicion().x, player.verPosicion().y);
	view.zoom(2);

	bolas_clock.restart();

//	const float lado = 150, altura_lado = 130, alto = 2*lado;
//	const float ancho = 2*altura_lado;
//
//	int xr = 0*ancho + 0*altura_lado;
//	int yr = 0*(3.0/2)*lado;
//
	/* Se agrega solo una bola */
//	bolas.push_back(Bola(xr + altura_lado, yr + lado,
//			(rand() % 361) * (3.14159 / 180.0),
//			2, bola, &lab.verParedes()));
}


void PlayScene::update(float elapsed){
	player.update(elapsed);
	sf::Vector2f player_pos = player.verPosicion();
	view.move(player.verOffset());

	sf::Time bolas_time = bolas_clock.getElapsedTime();

	/* Se agregan nuevas bolas dependiendo del timer */
	if(bolas_time.asSeconds() > tiempo_spawn_bolas) {
		const float lado = 150, altura_lado = 130, alto = 2*lado;
		const float ancho = 2*altura_lado;

		int xh = rand() % lab.VerGrilla().ancho(), yh = rand() % lab.VerGrilla().alto();

		int xr = xh*ancho + yh*altura_lado;
		int yr = yh*(3.0/2)*lado;

		bolas_clock.restart();	

		bolas.push_back(Bola(xr + altura_lado, yr + lado,
				(rand() % 361) * (3.14159 / 180.0),
			       	2, bola, &lab.verParedes()));
	}

	/* Se actualizan las bolas */
	for (auto &bola : bolas)
		bola.update(elapsed);

}

void PlayScene::draw(sf::RenderWindow &w){
	w.setView(view);
	lab.DibujarLab(w, 0, 0);
	player.draw(w);
	for (auto &bola : bolas) {
		bola.draw(w);
	}
}
