#ifndef DIBUJO_H
#define DIBUJO_H
#include <SFML/Graphics.hpp>
#include "../headers/Laberinto.h"

void dibujarGrilla(sf::RenderWindow& w, const Grilla &g, const sf::Texture &tileset, const sf::Texture &escotillas, float x, float y);

#endif
