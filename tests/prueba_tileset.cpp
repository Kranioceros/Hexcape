#include "../headers/Laberinto.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int nroTile(const bool *arr);
void dibujarGrilla(sf::RenderWindow& w, const Grilla &g, const sf::Texture &tileset, float x, float y);

int main() {
	int ancho_pantalla = 1100, alto_pantalla = 900;
	sf::Texture tileset; tileset.loadFromFile("assets/hexagonos-2080x2400-debug.png");
	
	const bool noreste[] = {1, 0, 0, 0, 0, 0};
	Celda cel_noreste(noreste);
	const bool este[] = {0, 1, 0, 0, 0, 0};
	Celda cel_este(este);
	const bool sudeste[] = {0, 0, 1, 0, 0, 0};
	Celda cel_sudeste(sudeste);
	const bool sudoeste[] = {0, 0, 0, 1, 0, 0};
	Celda cel_sudoeste(sudoeste);
	const bool oeste[] = {0, 0, 0, 0, 1, 0};
	Celda cel_oeste(oeste);
	const bool noroeste[] = {0, 0, 0, 0, 0, 1};
	Celda cel_noroeste(noroeste);
	const bool todas[] = {1, 1, 1, 1, 1, 1};
	Celda cel_todas(todas);

	std::vector< std::vector < Celda > > grilloide =
	{ {Celda(), cel_sudeste, cel_sudoeste},
	  {cel_este, todas, cel_oeste},
	  {cel_noreste, noroeste, Celda()}};

	Grilla g( grilloide );
	g.celda(Coordenadas(0, 0)).visible = g.celda(Coordenadas(2, 2)).visible = false;

//	std::cout << "empieza prueba nroTile" << std::endl;
//	bool arr[] = { 0, 1, 1, 1, 0, 0 };
//	std::cout << "el numero es: " << nroTile(arr) << std::endl;

	/* Termina codigo ejemplo */

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

int nroTile(const bool *arr) {
	int res = 0;
	for(int i=0; i < 6; i++) {
		res += arr[i] << (6-i-1);
	}
	return res;
}
void dibujarGrilla(sf::RenderWindow& w, const Grilla &g, const sf::Texture &tileset, float x, float y) {
	float lado = 150, altura_lado = 130;
	float ancho = 2*altura_lado, alto = 2*lado;

	/* Se crea un vector de sprites, cada uno con su respectivo tile del tileset */
	std::vector<sf::Sprite> sprites(64);
	for(int i=0; i < 64; i++) {
		int fila = i / 8, col = i % 8;
		sprites[i].setTexture(tileset);
		sprites[i].setTextureRect(
			sf::IntRect(ancho*col, alto*fila, ancho, alto+1)
		);
	}

	for(int xh=0; xh < g.alto(); xh++) {
		for (int yh=0; yh < g.ancho(); yh++) {
			const Celda &c = g.celda(Coordenadas(yh, xh));

			if (c.visible == false)
				continue;

			int xr = x + xh*ancho + yh*altura_lado;
			int yr = y + yh*(3.0/2)*lado;
			int nro_tile = nroTile(c.aberturas);

			sprites[nro_tile].setPosition(xr, yr);
			w.draw(sprites[nro_tile]);
		}
	}
}
