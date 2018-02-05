#include "../headers/Laberinto.h"
#include <cmath>
#include <iostream>
#include <ctime>

int main() {
	int ancho_pantalla = 1920, alto_pantalla = 1080;

	LabParams params;
	params.alto = 4;
	params.ancho = 6;
	params.entrada_x = 0;
	params.entrada_y = 0;
	params.semilla = time(nullptr);
	
//	Laberinto lab(params);
	Laberinto lab(time(nullptr), 0, 0, 4, 6);
	
	const Grilla g = lab.VerGrilla();
	
//	for(int fila = 0; fila < g.alto(); fila++) {
//		for(int col = 0; col < g.ancho(); col++) {
//			std::cout << "[";
//			for(int abert = 0; abert < 6; abert++) {
//				std::cout << " " << g.celda(Coordenadas(col, fila)).aberturas[abert] << " ";
//			}
//			std::cout << "], ";
//		}
//		std::cout << std::endl;
//	}

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

			lab.DibujarLab(window, 0, 0);

			window.display();
		}
	}
	return 0;
}
