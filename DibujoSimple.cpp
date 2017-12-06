#include "headers/DibujoSimple.h"
#include <cmath>

float calcX(float xh, float yh, float altura, float grosor);
float calcY(float yh, float lado, float grosor);

void dibujarGrilla(sf::RenderWindow& w, Grilla &g, float lado, float grosor, float x, float y,
		sf::Color relleno, sf::Color borde)
{
	float altura_lado = sqrt(pow(lado, 2)- pow(0.5 * lado, 2));

	sf::CircleShape hex_lleno(lado+grosor, 6); hex_lleno.setOrigin(lado+grosor, lado+grosor);
	sf::CircleShape hex_hueco(lado, 6); hex_hueco.setOrigin(lado, lado);
	hex_hueco.setOutlineThickness(grosor); hex_hueco.setOutlineColor(borde);
	hex_lleno.setFillColor(borde); hex_hueco.setFillColor(relleno);
	
	sf::Font font; font.loadFromFile("fonts/BebasNeue Bold.ttf");
	sf::Text entrada("Inicio", font); sf::Text salida("Final", font);

	entrada.setOrigin( entrada.getLocalBounds().width / 2,
			   entrada.getLocalBounds().height);
	salida.setOrigin( salida.getLocalBounds().width / 2,
			   salida.getLocalBounds().height);

	for (int yh = 0; yh < g.alto(); yh++){
		for (int xh = 0; xh < g.ancho(); xh++) {
			/* Se calculan las coordenadas rectangulares */
			float xr = x + calcX(xh, yh, altura_lado, grosor),
			      yr = y + calcY(yh, lado, grosor);

			Celda &celda = g.celda(yh, xh);

			/* Se dibuja la celda que corresponda */
			if (celda.hueca) {
				hex_hueco.setPosition(xr, yr);
				w.draw(hex_hueco);
			} else {
				hex_lleno.setPosition(xr, yr);
				w.draw(hex_lleno);
			}
			/* Se dibuja una E, S o nada dependiendo de si es entrada/salida/ninguna */
			if (celda.entrada) {
				entrada.setPosition(xr, yr);
				w.draw(entrada);
			} else if (celda.salida) {
				salida.setPosition(xr, yr);
				w.draw(salida);
			}
		}
	}

}

void dibujarAberturas(sf::RenderWindow& w, const Grilla &g, float lado, float grosor, float porcentaje, float x, float y, sf::Color color) {
	const float PI = 3.14159;
	sf::RectangleShape rec(sf::Vector2f(grosor, porcentaje*lado));
	rec.setFillColor(color);
	float altura_lado = sqrt(pow(lado, 2)- pow(0.5 * lado, 2));

	for (int yh = 0; yh < g.alto(); yh++){
		for (int xh = 0; xh < g.ancho(); xh++) {
			/* Se calculan las coordenadas rectangulares */
			float xr = x + calcX(xh, yh, altura_lado, grosor),
			      yr = y + calcY(yh, lado, grosor);

			/* NE */
			if (g.celda(yh, xh).aberturas[0]) {
				rec.setOrigin(0, 0);
				rec.setPosition(  xr + cosf(PI/6.0)*lado*(1-porcentaje)*0.5
						, yr - (lado - sinf(PI/6.0)*lado*(1-porcentaje)*0.5));
				rec.setRotation(-60);
				w.draw(rec);
			}	
			/* E */
			if (g.celda(yh, xh).aberturas[1]) {
				rec.setOrigin(0, 0);
				rec.setPosition(xr + altura_lado, yr - (0.5*lado-(1-porcentaje)/2*lado));
				rec.setRotation(0);
				w.draw(rec);
			}	
			/* SE */
			if (g.celda(yh, xh).aberturas[2]) {
				rec.setOrigin(0, porcentaje*lado);
				rec.setPosition(  xr + cosf(PI/6.0)*lado*(1-porcentaje)*0.5
						, yr + (lado - sinf(PI/6.0)*lado*(1-porcentaje)*0.5));
				rec.setRotation(60);
				w.draw(rec);
			}	
			/* SO */
			if (g.celda(yh, xh).aberturas[3]) {
				rec.setOrigin(grosor, porcentaje*lado);
				rec.setPosition(  xr - cosf(PI/6.0)*lado*(1-porcentaje)*0.5
						, yr + (lado - sinf(PI/6.0)*lado*(1-porcentaje)*0.5));
				rec.setRotation(-60);
				w.draw(rec);
			}	
			/* O */
			if (g.celda(yh, xh).aberturas[4]) {
				rec.setOrigin(0, 0);
				rec.setPosition(xr - altura_lado - grosor, yr - (0.5*lado-(1-porcentaje)/2*lado));
				rec.setRotation(0);
				w.draw(rec);
			}	
			/* NO */
			if (g.celda(yh, xh).aberturas[5]) {
				rec.setOrigin(grosor, 0);
				rec.setPosition(  xr - cosf(PI/6.0)*lado*(1-porcentaje)*0.5
						, yr - (lado - sinf(PI/6.0)*lado*(1-porcentaje)*0.5));
				rec.setRotation(60);
				w.draw(rec);
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
