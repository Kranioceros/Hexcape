#include "../headers/Laberinto.h"
#include "../headers/Dibujo.h"
#include <cmath>
#include <iostream>
#include <ctime>

int main() {
	int ancho_pantalla = 1100, alto_pantalla = 900;

	sf::Texture tileset; tileset.loadFromFile("assets/hexagonos-2080x2400-debug.png");
	
	LabParams params;
	params.alto = params.ancho = 3;
	params.entrada_x = params.entrada_y = 0;
	params.semilla = time(nullptr);
	
	Laberinto lab(params);
	
	const Grilla g = lab.VerGrilla();
	
	for(int fila = 0; fila < g.alto(); fila++) {
		for(int col = 0; col < g.ancho(); col++) {
			std::cout << "[";
			for(int abert = 0; abert < 6; abert++) {
				std::cout << " " << g.celda(Coordenadas(col, fila)).aberturas[abert] << " ";
			}
			std::cout << "], ";
		}
		std::cout << std::endl;
	}

	sf::RenderWindow window(sf::VideoMode(ancho_pantalla, alto_pantalla)
				, "prueba_grilla"
				, sf::Style::Close);
	window.setFramerateLimit(60);
	
	/* Mientras este abierta la ventana */
	while(window.isOpen()) {
		sf::Event event;

		/* Obtener evento */
		while(window.pollEvent(event)) { 
			if(event.type == sf::Event::Closed)
				window.close();

			window.clear(sf::Color::Black);

			dibujarGrilla(window, g, tileset, 0, 50);

			window.display();
		}
	}
	return 0;
}
