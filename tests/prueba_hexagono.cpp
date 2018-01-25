/* En esta prueba se emplea una funcion que dibuja las aberturas de una celda */
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../headers/Laberinto.h"
#include <cmath>

using namespace std;

void dibujarAbertura(sf::RenderWindow& w, Celda &c,
	float lado, float grosor, float porcentaje, float x, float y,
	sf::Color color = sf::Color::White);

int main() {
	int ancho_pantalla = 300, alto_pantalla = 300;
	
	float lado = 80; float grosor = 20;
	
	float origenx = ancho_pantalla / 2, origeny = alto_pantalla / 2;
	
	Celda c;
	c.aberturas[0] = c.aberturas[1] = c.aberturas[2] = c.aberturas[3] = c.aberturas[4] = c.aberturas[5] = true;
	
	sf::RenderWindow window(sf::VideoMode(ancho_pantalla, alto_pantalla)
				, "prueba_hexagono"
				, sf::Style::Close);
	
	sf::CircleShape shape(lado, 6);
	shape.setOrigin(lado,lado);
	shape.setPosition(origenx, origeny);
	
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(grosor);

	while (window.isOpen()) {
		sf::Event event;		
		while (window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();

			window.clear(sf::Color::White);
			window.draw(shape);
			dibujarAbertura(window, c, lado, grosor, 0.62, origenx, origeny, sf::Color::Red);
			window.display();
		}
	}

	return 0;
}

void dibujarAbertura(sf::RenderWindow& w, Celda &c, float lado, float grosor, float porcentaje, float x, float y, sf::Color color) {
	const float PI = 3.14159;
	sf::RectangleShape rec(sf::Vector2f(grosor, porcentaje*lado));
	rec.setFillColor(color);
	float altura_lado = sqrt(pow(lado, 2)- pow(0.5 * lado, 2));
	/* NE */
	if (c.aberturas[0]) {
		rec.setOrigin(0, 0);
		rec.setPosition(  x + cosf(PI/6.0)*lado*(1-porcentaje)*0.5
				, y - (lado - sinf(PI/6.0)*lado*(1-porcentaje)*0.5));
		rec.setRotation(-60);
		w.draw(rec);
	}	
	/* E */
	if (c.aberturas[1]) {
		rec.setOrigin(0, 0);
		rec.setPosition(x + altura_lado, y - (0.5*lado-(1-porcentaje)/2*lado));
		rec.setRotation(0);
		w.draw(rec);
	}	
	/* SE */
	if (c.aberturas[2]) {
		rec.setOrigin(0, porcentaje*lado);
		rec.setPosition(  x + cosf(PI/6.0)*lado*(1-porcentaje)*0.5
				, y + (lado - sinf(PI/6.0)*lado*(1-porcentaje)*0.5));
		rec.setRotation(60);
		w.draw(rec);
	}	
	/* SO */
	if (c.aberturas[3]) {
		rec.setOrigin(grosor, porcentaje*lado);
		rec.setPosition(  x - cosf(PI/6.0)*lado*(1-porcentaje)*0.5
				, y + (lado - sinf(PI/6.0)*lado*(1-porcentaje)*0.5));
		rec.setRotation(-60);
		w.draw(rec);
	}	
	/* O */
	if (c.aberturas[4]) {
		rec.setOrigin(0, 0);
		rec.setPosition(x - altura_lado - grosor, y - (0.5*lado-(1-porcentaje)/2*lado));
		rec.setRotation(0);
		w.draw(rec);
	}	
	/* NO */
	if (c.aberturas[5]) {
		rec.setOrigin(grosor, 0);
		rec.setPosition(  x - cosf(PI/6.0)*lado*(1-porcentaje)*0.5
				, y - (lado - sinf(PI/6.0)*lado*(1-porcentaje)*0.5));
		rec.setRotation(60);
		w.draw(rec);
	}	
}
