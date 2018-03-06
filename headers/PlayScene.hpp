#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP

#include <SFML/Graphics.hpp>
#include "Laberinto.hpp"
#include "BaseScene.hpp"
#include "Player.hpp"
#include "Bola.hpp"
#include "Escotilla.hpp"

class PlayScene: public BaseScene {
private:
	sf::View view;
	sf::Texture bola;
	sf::Texture escotilla;

	sf::Texture portal;
	sf::Sprite spr_portal;

	Laberinto lab;
	Player* player;
	float tiempo_muerto, tiempo_victoria;

	vector<Bola*> bolas;
	vector<Escotilla*> escotillas;
	sf::Clock bolas_clock;
	sf::Clock tiempo_player;
	float tiempo_spawn_bolas;
	unsigned int max_bolas;
	unsigned int num_nivel;
public:
	PlayScene(float _tiempo_spawn_bolas,unsigned int _num_nivel);
	virtual ~PlayScene() override;
	void update(float elapsed) override;
	void draw(sf::RenderWindow &w) override;
};

#endif
