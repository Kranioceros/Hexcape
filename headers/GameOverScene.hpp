#ifndef GAMEOVER_SCENE_HPP
#define GAMEOVER_SCENE_HPP
#include "BaseScene.hpp"

#include <SFML/Graphics.hpp>

class GameOverScene: public BaseScene {
private:
	sf::Text game_over_text;
	sf::Font game_over_font;
	sf::View view;

public:
	GameOverScene();
	void update(float elapsed) override;
	void draw(sf::RenderWindow &w) override;
};

#endif
