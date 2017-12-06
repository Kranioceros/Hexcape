#include "../headers/Laberinto.h"
#include "../headers/DibujoSimple.h"
#include <cmath>

int main() {
	int ancho_pantalla = 1024, alto_pantalla = 768;
	
	float lado = 90; float grosor = 30;
	float altura_lado = sqrt(pow(lado, 2)- pow(0.5 * lado, 2));
	
	/* Posicion del primer hexagono de la grilla. Es el origen (0, 0). */
	float origenx = altura_lado + grosor, origeny = lado + grosor;

	/* EL SIGUIENTE CODIGO ES UNA GRILLA DE EJEMPLO. REEMPLAZAR CON UN OBJETO DE CLASE
	LABERINTO Y LUEGO USAR LA GRILLA GENERADA PARA IMPRIMIR */

	const bool este[] = {0, 1, 0, 0, 0, 0};
	Celda cel_este(este);
	const bool oeste[] = {0, 0, 0, 0, 1, 0};
	Celda cel_oeste(oeste);
	const bool esteoeste[] = {0, 1, 0, 0, 1, 0};
	Celda cel_esteoeste(esteoeste);

	std::vector < std::vector <Celda> > celdas =
	{ {cel_este, cel_oeste, Celda()}
	 ,{Celda(), cel_este, cel_oeste}
	 ,{cel_este, cel_esteoeste, cel_oeste} };

	Grilla g(celdas); 
	g.celda(0, 2).hueca = g.celda(1, 0).hueca = false;
	g.celda(2, 2).salida = true;
	g.celda(0, 0).entrada = true;
	g.celda(2, 0).aberturas[0] = g.celda(1, 1).aberturas[3] = true;
	g.celda(1, 2).aberturas[2] = g.celda(2, 2).aberturas[5] = true;

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

			dibujarGrilla(window, g, lado, grosor, origenx, origeny, sf::Color::Blue, sf::Color::Red);
			dibujarAberturas(window, g, lado, grosor, 0.70, origenx, origeny, sf::Color::Green);

			window.display();
		}
	}
	return 0;
}
