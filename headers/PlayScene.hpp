#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP

#include <SFML/Graphics.hpp>
#include "Laberinto.hpp"
#include "BaseScene.hpp"
#include "Player.hpp"
#include "Bola.hpp"
#include "Escotilla.hpp"
#include <deque>

class PlayScene: public BaseScene {
private:
	sf::View view;
	sf::Texture bola;
	sf::Texture escotilla;

	sf::Texture portal;
	sf::Sprite spr_portal;
	sf::Font font;
	sf::Text debug;

	Laberinto lab;
	Player* player;
	float tiempo_muerto, tiempo_victoria;

	deque<Bola*> bolas;
	vector<Escotilla*> escotillas;
	sf::Clock bolas_clock;
	sf::Clock tiempo_player;
	sf::Clock tiempo_score;
	float tiempo_spawn_bolas;
	unsigned int max_bolas;
	unsigned int num_nivel;
	unsigned int puntos_jugador;
	unsigned int puntos_escena;
public:
	PlayScene(unsigned int _num_nivel, unsigned int _puntos_jugador);
	virtual ~PlayScene() override;
	void update(float elapsed) override;
	void draw(sf::RenderWindow &w) override;
};

#endif
