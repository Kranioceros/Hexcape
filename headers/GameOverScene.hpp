#ifndef GAMEOVER_SCENE_HPP
#define GAMEOVER_SCENE_HPP
#include "BaseScene.hpp"

#include <SFML/Graphics.hpp>

class GameOverScene: public BaseScene {
private:
	sf::Text game_over_text;
	sf::Text instrucciones_text;
	sf::Font font;
	sf::View view;
	sf::Text score_text;
	unsigned int puntos_jugador;

public:
	GameOverScene(unsigned int _puntos_jugador);
	void update(float elapsed) override;
	void draw(sf::RenderWindow &w) override;
};

#endif
