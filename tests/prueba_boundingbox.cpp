#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../headers/Collision.h"
#include "../headers/Laberinto.h"
#include "../headers/Dibujo.h"

using namespace std;

void agregarParedes(vector<sf::Sprite> &paredes, const Grilla &g, sf::Texture &tex);
float calcX(float xh, float yh, float altura, float grosor);
float calcY(float yh, float lado, float grosor);

const float PI = 3.14159;

int main() {
	int ancho_pantalla = 1280, alto_pantalla = 1024;
	
	sf::RenderWindow window(sf::VideoMode(ancho_pantalla, alto_pantalla)
							, "prueba_boundingbox"
							, sf::Style::Close);
	window.setFramerateLimit(60);
//	sf::View vista(sf::FloatRect(-100, -100, 2360, 2048));
//	window.setView(vista);
	
	sf::Texture tileset; tileset.loadFromFile("assets/hexagonos-2080x2400-debug.png");
	sf::Texture robertinho; robertinho.loadFromFile("assets/robertinho.png");

	sf::Texture akira; akira.loadFromFile("assets/akira.png");
	sf::Sprite spr_akira; spr_akira.setTexture(akira);
	spr_akira.setPosition(100, 100);

	sf::Texture akira_hitbox; akira_hitbox.loadFromFile("assets/akira_hitbox.png");
	sf::Sprite spr_akira_hitbox; spr_akira_hitbox.setTexture(akira_hitbox);
	spr_akira_hitbox.setPosition(spr_akira.getPosition().x + 5, spr_akira.getPosition().y + 5);
	
	LabParams params;
	params.alto = 6;
	params.ancho = 6;
	params.entrada_x = 0;
	params.entrada_y = 0;
	params.semilla = time(nullptr);
	
	Laberinto lab(params);
	
	const Grilla g = lab.VerGrilla();

	/* Creamos todos los sprites de las paredes */
	vector<sf::Sprite> paredes;

	agregarParedes(paredes, g, robertinho);
	
	/* Mientras este abierta la ventana */
	while(window.isOpen()) {
		sf::Event event;
//		bool derecha = 0, izquierda = 0, arriba = 0, abajo = 0;

		/* Obtener evento */
		while(window.pollEvent(event)) { 
			if(event.type == sf::Event::Closed)
				window.close();

			
//			if(event.type == sf::Event::KeyPressed) {
//				switch (event.key.code) {
//					case sf::Keyboard::Right:
//					derecha = true;	
//					break;
//
//					case sf::Keyboard::Left:
//					izquierda = true;	
//					break;
//
//					case sf::Keyboard::Up:
//					arriba = true;	
//					break;
//
//					case sf::Keyboard::Down:
//					abajo = true;	
//					break;
//
//					default:
//					break;
//				}
//			}
//
//			if(event.type == sf::Event::KeyReleased) {
//				switch (event.key.code) {
//					case sf::Keyboard::Right:
//					derecha = false;	
//					break;
//
//					case sf::Keyboard::Left:
//					izquierda = false;	
//					break;
//
//					case sf::Keyboard::Up:
//					arriba = false;	
//					break;
//
//					case sf::Keyboard::Down:
//					abajo = false;	
//					break;
//
//					default:
//					break;
//				}
//			}


		}

		sf::Vector2f coord = spr_akira.getPosition();
		int mov = 6;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			spr_akira_hitbox.move(-mov, 0);
			spr_akira.move(-mov, 0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			spr_akira.move(mov, 0);
			spr_akira_hitbox.move(mov, 0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			spr_akira.move(0, -mov);
			spr_akira_hitbox.move(0, -mov);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			spr_akira.move(0, mov);
			spr_akira_hitbox.move(0, mov);
		}

		// bounding box test
		bool choco = false;
		auto pared = paredes.begin();

		cout << "Empieza bounding box test!" << endl;

		while(pared != paredes.end() && Collision::BoundingBoxTest(spr_akira_hitbox, *pared) == false)
			pared++;

		if (pared != paredes.end())
			choco = true;

		if (choco) {
			cout << "Akira esta chocando!" << endl;
			spr_akira.setPosition(coord);
			spr_akira_hitbox.setPosition(coord.x+5, coord.y+5);
		}

		window.clear(sf::Color::Black);

		dibujarGrilla(window, g, tileset, 0, 0);
//		for (sf::Sprite &sp : paredes) {
//			window.draw(sp);
//		}
		window.draw(spr_akira);
//		window.draw(spr_akira_hitbox);

		window.display();
	}
	return 0;
}

void agregarParedes(vector<sf::Sprite> &paredes, const Grilla &g, sf::Texture &tex) {
	float lado = 150, altura_lado = 130;
	float ancho = 2*altura_lado, alto = 2*lado;
	
	sf::Sprite spr(tex);

	for(int yh=0; yh < g.alto(); yh++) {
		for(int xh=0; xh < g.ancho(); xh++) {
			int xr = xh*ancho + yh*altura_lado;
			int yr = yh*(3.0/2)*lado;
			
			const Celda &c = g.celda(Coordenadas(xh, yh));
			
			if (!c.aberturas[0]) {
				spr.setOrigin(0, 0);
				spr.setPosition(  48 + xr + cosf(PI/6.0)*lado*0.5
						, 135 + yr - (lado - sinf(PI/6.0)*lado*0.5));
				spr.setRotation(-60);
				paredes.push_back(spr);
				cout << "Se dibujo una pared" << endl;
			}

			if (!c.aberturas[1]) {
				spr.setOrigin(0, 0);
				spr.setPosition(100 + xr + altura_lado,70 + yr - (0.5*lado-0.5*lado));
				spr.setRotation(0);
				paredes.push_back(spr);
			}

			if (!c.aberturas[2]) {
				spr.setOrigin(0, 0);
				spr.setPosition(130 + xr + altura_lado, 190 + yr - (0.5*lado-0.5*lado));
				spr.setRotation(60);
				paredes.push_back(spr);
			}

			if (!c.aberturas[3]) {
				spr.setOrigin(0, lado);
				spr.setPosition(60 + xr + cosf(PI/6.0)*lado*0.5
						, 187 + yr + (lado - sinf(PI/6.0)*lado*0.5));
				spr.setRotation(-60);
				paredes.push_back(spr);
			}
			if (!c.aberturas[4]) {
				spr.setOrigin(30, lado);
				spr.setPosition(95 + xr - cosf(PI/6.0)*lado*0.5
						, 100 + yr + (lado - sinf(PI/6.0)*lado*0.5));
				spr.setRotation(0);
				paredes.push_back(spr);
			}
			if (!c.aberturas[5]) {
				spr.setOrigin(30, 0);
				spr.setPosition(220 + xr - cosf(PI/6.0)*lado*0.5
						, 130 + yr - (lado - sinf(PI/6.0)*lado*0.5));
				spr.setRotation(60);
				paredes.push_back(spr);
			}
		}
	}
}

float calcX(float xh, float yh, float altura, float grosor) {
	return 2*altura*xh + altura*yh + grosor*xh + 0.5*grosor*yh;
}
float calcY(float yh, float lado, float grosor) {
	return 3.0/2*lado*yh + 0.8*grosor*yh;
}
