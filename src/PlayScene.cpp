#include "PlayScene.hpp"
#include "TransitionScene.hpp"
#include "Laberinto.hpp"
#include "Game.hpp"
#include "GameOverScene.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream>

unsigned int calcularDimension(unsigned int nro_nivel);

PlayScene::PlayScene(unsigned int _num_nivel, unsigned int _puntos_jugador)
	: lab(time(nullptr), 0, 0, calcularDimension(_num_nivel), calcularDimension(_num_nivel), 0.02), bolas(0) {
	font.loadFromFile("fonts/munro.ttf");
	debug.setFont(font);
	debug.setFillColor(sf::Color::Yellow);
	debug.setString("NULL");
	debug.setCharacterSize(16);

	num_nivel=_num_nivel;
	puntos_jugador = _puntos_jugador;
	puntos_escena = 500 + 100*(num_nivel-1);

	tiempo_muerto = 3000;
	tiempo_victoria = 3000;

	tiempo_spawn_bolas = 0.39169*pow(num_nivel, -0.55352);
	max_bolas = 1.2*pow(lab.VerGrilla().ancho(), 2) + 2*num_nivel; 
	
	bola.loadFromFile("assets/bola2.png");
	escotilla.loadFromFile("assets/escotillas-516x86.png");
	portal.loadFromFile("assets/portal.png");
	fondo.loadFromFile("assets/fondo.png");

	spr_fondo.setTexture(fondo);

	player = new Player(200, 200, &lab.verParedes(), &bolas, spr_portal);
	add(player);	

	sf::Vector2f player_pos = player->verPosicion();

	view.reset(sf::FloatRect(0, 0, 1920, 1080));	
	view.setCenter(player_pos.x, player_pos.y);
	view.zoom(0.5);

	spr_fondo.setPosition(player_pos.x - spr_fondo.getLocalBounds().width / 2,
				player_pos.y - spr_fondo.getLocalBounds().height / 2);

	debug.setPosition(player_pos.x - 1920 / 4 + 5,
				player_pos.y - 1080 / 4 + 5);

	bolas_clock.restart();

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
				if (ptr_escotilla != nullptr)
					escotillas.push_back(ptr_escotilla);
			}
		}
	}

	/* Se agrega el portal al final de la escena */
	spr_portal.setTexture(portal);
	spr_portal.setOrigin(45, 45);
	spr_portal.setPosition((lab.VerGrilla().ancho()-1)*ancho + (lab.VerGrilla().alto()-1)*altura_lado + altura_lado,(lab.VerGrilla().alto()-1)*(3.0/2)*lado+lado);

	/* Se comienza a contar el tiempo del jugador */
	tiempo_score.restart();
}

void PlayScene::update(float elapsed){
	/* Se agregan nuevas bolas dependiendo del timer */

	sf::Time bolas_time = bolas_clock.getElapsedTime();
	if(bolas_time.asSeconds() > tiempo_spawn_bolas) {
		bolas_clock.restart();

		Bola* nueva_bola = escotillas[rand() % escotillas.size()]->spawn();

		/* Si realmente se agrego una nueva bola */
		if (nueva_bola != nullptr) {
			add(nueva_bola);
			bolas.push_back(nueva_bola);
		}
		
		/* Si son muchas, se empiezan a borrar las mas viejas */
		if (bolas.size() >= max_bolas && nueva_bola != nullptr) {
			auto it = bolas.begin();
			while(it != bolas.end() && (*it)->desapareciendo())
				it++;
			(*it)->desaparecer();
		}

		/* Borrar todas las bolas que ya estan DESAPARECIDAS */
		for (auto &bola : bolas) {
			if(bola->desaparecio()) {
				remove(*bolas.begin());
				bolas.pop_front();
			}
		}
	}
	/* Se actualizan las escotillas */
	for(Escotilla* e : escotillas)
		e->update(elapsed);

	/* Se gira el portal */
	spr_portal.rotate(2);
	
	/* Se actualizan todas las demas entidades */
	BaseScene::update(elapsed);
	view.move(player->verOffset());

	/* Se actualiza la posicion del fondo si el jugador se movio fuera del
	 * area que ocupa el sprite */
	sf::Vector2f player_pos = player->verPosicion();
	sf::Vector2f fondo_pos = spr_fondo.getPosition();
	float fondo_ancho = spr_fondo.getLocalBounds().width,
	      fondo_alto = spr_fondo.getLocalBounds().height;

	if(player_pos.x < fondo_pos.x || player_pos.x > fondo_pos.x + fondo_ancho) {
		float sentido = player_pos.x < fondo_pos.x ? -1 : 1;
		spr_fondo.move(fondo_ancho*sentido, 0);
	}

	if(player_pos.y < fondo_pos.y || player_pos.y > fondo_pos.y + fondo_alto) {
		float sentido = player_pos.y < fondo_pos.y ? -1 : 1;
		spr_fondo.move(0, fondo_alto*sentido);
	}

	/* Se actualiza la puntuacion */
	float segundos_score = tiempo_score.getElapsedTime().asSeconds();

	/* Si paso un segundo y el jugador no ha ganado o perdido */
	if(segundos_score > 1 && player->verEstado() == 1) {
		tiempo_score.restart();
		puntos_escena -= 10;
	}

	/* Se actualiza el mensaje debug */
	stringstream ss;
	int tamanio = lab.VerGrilla().ancho();
	ss << "Nro nivel: " << num_nivel << std::endl
	   << "Tamanio del laberinto: " << tamanio << "x" << tamanio << std::endl
	   << "Nro. de bolas: " << bolas.size() << "/" << max_bolas << std::endl
	   << "Velocidad de spawneo: " << tiempo_spawn_bolas << std::endl
	   << "Puntos de escena: " << puntos_escena << std::endl
	   << "Puntos de jugador: " << puntos_jugador << std::endl;
	debug.setString(ss.str());

	debug.move(player->verOffset().x, player->verOffset().y);

	/* Si el jugador perdio/gano, se cambia de escena */
	switch(player->verEstado()) {
		case 1: // Jugando
		tiempo_player.restart();
		break;

		case 0: // Muerto
		{
		sf::Time tiempo = tiempo_player.getElapsedTime();
		if(tiempo.asMilliseconds() > tiempo_muerto)
			Game::getInstance().switchScene(
			new GameOverScene(puntos_jugador));
		}
		break;

		case 2: // Gano
		{
		sf::Time tiempo = tiempo_player.getElapsedTime();
		if(tiempo.asMilliseconds() > tiempo_victoria)
			Game::getInstance().switchScene(
			new TransitionScene(num_nivel, puntos_jugador + puntos_escena + 500));
		}
		break;

	}
}

void PlayScene::draw(sf::RenderWindow &w){
	w.setView(view);

	/* Se dibuja el fondo 9 veces: una en la posicion del sprite y las otras
	 * 8 en las posiciones adyacentes y las esquinas. Esto forma una rejilla
	 * de 3x3 */
	sf::Vector2f fondo_pos = spr_fondo.getPosition();
	float fondo_ancho = spr_fondo.getLocalBounds().width,
	      fondo_alto  = spr_fondo.getLocalBounds().height;

	/* Posicion de la primera celda */
	sf::Vector2f fondo_origen(fondo_pos.x - fondo_ancho,
				  fondo_pos.y - fondo_alto);

	for(unsigned int fila=0; fila < 3; fila++) {
		for(unsigned int col=0; col < 3; col++) {
			spr_fondo.setPosition(fondo_origen.x + fondo_ancho*col,
					      fondo_origen.y + fondo_alto*fila);
			w.draw(spr_fondo);
		}
	}
	spr_fondo.setPosition(fondo_pos);

	lab.DibujarLab(w, 0, 0);
	for(auto &e : escotillas)
		e->draw(w);
	w.draw(spr_portal);

	/* Se dibujan las entidades */
	BaseScene::draw(w);

	/* Se dibuja el mensaje de debug */
	w.draw(debug);
}

PlayScene::~PlayScene() {
	for (auto &e : escotillas)
		delete e;

	for (auto &b : bolas)
		delete b;

	delete player;
}

unsigned int calcularDimension(unsigned int nro_nivel) {
	/* Curva obtenida por inteligencia artificial y otros metodos
	 * muy complejos */
	return 2.78673 * log(nro_nivel) + 2.85108;
}
