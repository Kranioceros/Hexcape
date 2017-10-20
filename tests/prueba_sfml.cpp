#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(300, 300), "SFML",
							sf::Style::Close);
	
	sf::CircleShape shape(100.f, 6);
	shape.setOrigin(100,100);
	shape.setPosition(150, 150);
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineColor(sf::Color::Blue);
	shape.setOutlineThickness(20);
	
	sf::View view(sf::FloatRect(0, 0, 300, 300));
	
	
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed) {
				switch(event.key.code) {
				case sf::Keyboard::Right:
					shape.rotate(15);
				break;
				case sf::Keyboard::Left:
					shape.rotate(-15);
				break;
				case sf::Keyboard::Up:
					shape.scale(1.25, 1.25);
				break;
				case sf::Keyboard::Down:
					shape.scale(0.8, 0.8);
				break;
				case sf::Keyboard::H:
					view.move(-10, 0);
				window.setView(view);
				break;
				case sf::Keyboard::L:
					view.move(10, 0);
				window.setView(view);
				break;
				case sf::Keyboard::J:
					view.move(0, 10);
				window.setView(view);
				break;
				case sf::Keyboard::K:
					view.move(0, -10);
				window.setView(view);
				break;
				default:
					;
				}
			}
		}
		
		window.clear();
		window.draw(shape);
		window.display();
		
	}
	
	return 0;
}
