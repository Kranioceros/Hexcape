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
	
	sf::Texture tileset; tileset.loadFromFile("assets/hexagonos-2080x2400-debug.png");
	sf::Texture robertinho; robertinho.loadFromFile("assets/robertinho.png");
	
	LabParams params;
	params.alto = 3;
	params.ancho = 3;
	params.entrada_x = 0;
	params.entrada_y = 0;
	params.semilla = 0;
	
	Laberinto lab(params);
	
	const Grilla g = lab.VerGrilla();

	/* Creamos todos los sprites de las paredes */
	vector<sf::Sprite> paredes;

	agregarParedes(paredes, g, robertinho);
	
	/* Mientras este abierta la ventana */
	while(window.isOpen()) {
		sf::Event event;

		/* Obtener evento */
		while(window.pollEvent(event)) { 
			if(event.type == sf::Event::Closed)
				window.close();

			window.clear(sf::Color::Black);

			dibujarGrilla(window, g, tileset, 0, 0);
			for (sf::Sprite &sp : paredes) {
				window.draw(sp);
			}

			window.display();
		}
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
				spr.setPosition(  75 + xr + cosf(PI/6.0)*lado*0.5
						, 155 + yr - (lado - sinf(PI/6.0)*lado*0.5));
				spr.setRotation(-60);
				paredes.push_back(spr);
				cout << "Se dibujo una pared" << endl;
			}

//			if (!c.aberturas[1]) {
//				spr.setOrigin(0, 0);
//				spr.setPosition(xr + altura_lado, yr - (0.5*lado-0.5*lado));
//				spr.setRotation(0);
//				paredes.push_back(spr);
//			}
//
//			if (!c.aberturas[2]) {
//				spr.setOrigin(0, 0);
//				spr.setPosition(xr + altura_lado, yr - (0.5*lado-0.5*lado));
//				spr.setRotation(0);
//				paredes.push_back(spr);
//			}
//
//			if (!c.aberturas[3]) {
//				spr.setOrigin(0, lado);
//				spr.setPosition(  xr + cosf(PI/6.0)*lado*0.5
//						, yr + (lado - sinf(PI/6.0)*lado*0.5));
//				spr.setRotation(60);
//				paredes.push_back(spr);
//			}
//			if (!c.aberturas[4]) {
//				spr.setOrigin(30, lado);
//				spr.setPosition(  xr - cosf(PI/6.0)*lado*0.5
//						, yr + (lado - sinf(PI/6.0)*lado*0.5));
//				spr.setRotation(-60);
//				paredes.push_back(spr);
//			}
//			if (!c.aberturas[4]) {
//				spr.setOrigin(0, 0);
//				spr.setPosition(xr - altura_lado - 30, yr - (0.5*lado-0.5*lado));
//				spr.setRotation(0);
//				paredes.push_back(spr);
//			}
//			if (!c.aberturas[5]) {
//				spr.setOrigin(30, 0);
//				spr.setPosition(  xr - cosf(PI/6.0)*lado*0.5
//						, yr - (lado - sinf(PI/6.0)*lado*0.5));
//				spr.setRotation(60);
//				paredes.push_back(spr);
//			}
		}
	}
}

float calcX(float xh, float yh, float altura, float grosor) {
	return 2*altura*xh + altura*yh + grosor*xh + 0.5*grosor*yh;
}
float calcY(float yh, float lado, float grosor) {
	return 3.0/2*lado*yh + 0.8*grosor*yh;
}
