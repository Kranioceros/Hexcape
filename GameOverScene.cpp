#include "headers/GameOverScene.hpp"
#include <iostream>

GameOverScene::GameOverScene() {
	game_over_font.loadFromFile("assets/munro/munro.ttf");
	game_over_text.setFont(game_over_font);
	game_over_text.setString("YOU DIED");
	game_over_text.setPosition(1920 / 2 - game_over_text.getGlobalBounds().width / 2,
				   1080 / 2 - game_over_text.getGlobalBounds().height / 2);
	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	view.zoom(1);
}

void GameOverScene::update(float elapsed) {

}

void GameOverScene::draw(sf::RenderWindow &w) {
	w.setView(view);
	w.draw(game_over_text);
}
