#include "headers/PlayScene.hpp"
#include "headers/Laberinto.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <cstdlib>

PlayScene::PlayScene(float _tiempo_spawn_bolas) : lab(time(nullptr), 0, 0, 10, 10, 0.02) {
	bola.loadFromFile("assets/bola2.png");
	tiempo_spawn_bolas = _tiempo_spawn_bolas;

	player = new Player(200, 200, &lab.verParedes());
	add(player);	

	view.reset(sf::FloatRect(0, 0, 1920, 1080));	
	view.setCenter(player->verPosicion().x, player->verPosicion().y);
	view.zoom(0.5);

	bolas_clock.restart();
	max_bolas = 30;
}

void PlayScene::update(float elapsed){
	sf::Time bolas_time = bolas_clock.getElapsedTime();
	/* Se agregan nuevas bolas dependiendo del timer */
	if(bolas_time.asSeconds() > tiempo_spawn_bolas) {
		bolas_clock.restart();	

		/* Se calculan posiciones al azar dentro de las celdas */
		const float lado = 150, altura_lado = 130;
		const float ancho = 2*altura_lado;

		int xh = rand() % lab.VerGrilla().ancho(), yh = rand() % lab.VerGrilla().alto();

		int xr = xh*ancho + yh*altura_lado;
		int yr = yh*(3.0/2)*lado;
	
		Bola* nueva_bola = new Bola(xr + altura_lado, yr + lado,
				(rand() % 361) * (3.14159 / 180.0),
				2, bola, &lab.verParedes());

		add(nueva_bola);
		bolas.push_back(nueva_bola);

		/* Si son muchas, se empiezan a borrar las mas viejas */
		if (bolas.size() >= max_bolas) {
			bolas.erase(bolas.begin());
			remove(*bolas.begin());
		}
	}
	/* Se actualizan todas las entidades */
	BaseScene::update(elapsed);
	view.move(player->verOffset());
}

void PlayScene::draw(sf::RenderWindow &w){
	w.setView(view);
	lab.DibujarLab(w, 0, 0);

	/* Se dibujan las entidades */
	BaseScene::draw(w);
}
