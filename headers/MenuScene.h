#ifndef MENUSCENE_H
#define MENUSCENE_H
#include "BaseScene.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class MenuScene : public BaseScene {
private:
	sf::Text title_text;
	sf::Text transition_text;
	sf::Font font;
	sf::View view;
	sf::Music devilman;
	sf::Texture portal;
	sf::Sprite spr_portal;
	
public:
	MenuScene();
	void update(float elapsed) override;
	void draw(sf::RenderWindow &w) override;
};

#endif

