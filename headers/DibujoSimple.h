#ifndef DIBUJOSIMPLE
#define DIBUJOSIMPLE

#include <SFML/Graphics.hpp>
#include "../headers/Laberinto.h"

/* Dibuja todas las celdas contenidas en g */
void dibujarGrilla(sf::RenderWindow& w, const Grilla &g, float lado, float grosor, float x, float y,
		   sf::Color relleno = sf::Color::White, sf::Color borde = sf::Color::Black);

/* Borra los muros que correspondan en base a la informacion de la celda
 * Porcentaje es un float de 0 a 1 que indica que porcentaje de la pared es
 * el ancho de cada abertura */
void dibujarAberturas(sf::RenderWindow& w, const Grilla &g,
		float lado, float grosor, float porcentaje, float x, float y,
		sf::Color color = sf::Color::White);

#endif
