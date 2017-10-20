#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

/* Este archivo de prueba es para testear si SFML/Zinjai/GCC fueron instalados
 * correctamente. Ademas sirve como una pequenia introduccion a SFML. */

/* CONTROLES:
 * 	ACHICAR HEXAGONO: FLECHA HACIA ABAJO
 * 	AGRANDAR HEXAGONO: FLECHA HACIA ARRIBA
 * 	GIRAR EN SENTIDO HORARIO: FLECHA HACIA LA DERECHA
 * 	GIRAR EN SENTIDO ANTIHORARIO: FLECHA HACIA LA IZQUIERDA
 * 	H, L, J, K: Mover la camara hacia la izquierda, derecha, abajo y arriba
 */

int main(int argc, char* argv[]) {
	/* RenderWindow permite crear una ventana de ciertas dimensiones
	 * El parametro sf::Style::Close es para gestores de ventanas especiales
	 * en Linux.*/
	sf::RenderWindow window(sf::VideoMode(300, 300), "SFML",
							sf::Style::Close);
	
	/* CircleShape permite crear circulos. En este caso le pasamos un 2do
	 * parametro opcional que define cuantos lados usar para aproximar el
	 * circulo -- asi obtenemos el circulo mas hexagonal del mundo. */
	sf::CircleShape shape(100.f, 6);

	/* Se define el punto sobre el cual se van a realizar las transformaciones:
	 * movimiento, rotacion, escalado, etc. */
	shape.setOrigin(100,100);

	shape.setPosition(150, 150); 			/* Se mueve la figura a las coordenadas */
	shape.setFillColor(sf::Color::Red); 		/* Color de relleno */
	shape.setOutlineColor(sf::Color::Blue); 	/* Color de borde */
	shape.setOutlineThickness(20); 			/* Grosor de borde */
	
	/* Las vistas son objetos que definen que parte del universo 2D se va
	 * a ver en pantalla. Los primeros dos parametros son los offsets con
	 * respecto al origen, mientras que los otros dos son ancho y alto */
	sf::View view(sf::FloatRect(0, 0, 300, 300));
	
	/* Mientras la ventana este abierta... */
	while(window.isOpen()) {

		/* Un objeto de tipo evento puede almacenar cualquiera de todos
		 * los eventos posibles, pero solo uno a la vez. Es una `union`. */
		sf::Event event;

		/* En SFML, la ventana es responsable de manejar los eventos
		 * pollevent obtiene un evento y lo guarda */
		while(window.pollEvent(event)) { 

			/* Como un objeto de tipo evento solo puede almacenar un
			 * evento a la vez, se le debe preguntar el tipo antes de
			 * intentar acceder a sus campos. De nuevo, leer sobre
			 * `union`. */

			/* Si se cerro la ventana... */
			if(event.type == sf::Event::Closed)
				window.close();

			/* Si se presiono una tecla... */
			if(event.type == sf::Event::KeyPressed) {
				switch(event.key.code) {
				/* Si la tecla es derecha... */
				case sf::Keyboard::Right:
					shape.rotate(15);
				break;
				/* Si la tecla es izquierda... */
				case sf::Keyboard::Left:
					shape.rotate(-15);
				break;
				/* Si la tecla es arriba... */
				case sf::Keyboard::Up:
					shape.scale(1.25, 1.25);
				break;
				/* Si la tecla es abajo... */
				case sf::Keyboard::Down:
					shape.scale(0.8, 0.8);
				break;
				/* Si la tecla es H... */
				case sf::Keyboard::H:
					view.move(-10, 0);
					window.setView(view);
				break;
				/* Si la tecla es L... */
				case sf::Keyboard::L:
					view.move(10, 0);
					window.setView(view);
				break;
				/* Si la tecla es J... */
				case sf::Keyboard::J:
					view.move(0, 10);
					window.setView(view);
				break;
				/* Si la tecla es K... */
				case sf::Keyboard::K:
					view.move(0, -10);
					window.setView(view);
				break;
				/* Si la tecla es cualquier otra... */
				default:
					/*cout << "Aprende los controles, bobo" << endl*/;
				}
			}

			/* Algunas cosas a tener en cuenta:
			 * + Cada vez que se modifica la view, es necesario
			 *   actualizar la ventana con esa view (window.setView). */
		}
		
		window.clear();		/* Se borra lo que hay en ventana */
		window.draw(shape);	/* Se dibuja el hexagono en el backbuffer */
		window.display();	/* Se muestra lo que hay en el backbuffer */
		
	}
	
	return 0;
}
