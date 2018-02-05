#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::Music musiquita;
	if (musiquita.openFromFile("../assets/devilman-no-uta.ogg")) {
		musiquita.play();
	} else {
		std::cout << "Epic fail. No music musicked." << std::endl;	
	}

	sf::RenderWindow window(sf::VideoMode(500, 500)
				, "prueba_grilla"
				, sf::Style::Close);
	window.setFramerateLimit(60);

	musiquita.play();

	while(window.isOpen()) {
		sf::Event ev;
		window.pollEvent(ev);
		if(ev.type == sf::Event::Closed)
			window.close();
	}
}
