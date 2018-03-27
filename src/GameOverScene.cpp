#include "GameOverScene.hpp"
#include "Game.hpp"
#include "PlayScene.hpp"
#include "TransitionScene.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

GameOverScene::GameOverScene(unsigned int _puntos_jugador) {
	//std::cout<<"ni hizo esto"<<std::endl;
	puntos_jugador = _puntos_jugador;
	
	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	view.setCenter(1920 / 2, 1080 / 2);
	view.zoom(1);
	
	stringstream ss;
	ss << "YOU DIED\n" << puntos_jugador << std::endl;
	
	font.loadFromFile("fonts/munro.ttf");
	game_over_text.setFont(font);
	game_over_text.setString(ss.str());
	game_over_text.setCharacterSize(32);
	game_over_text.setOrigin(game_over_text.getLocalBounds().width / 2.0,
							 game_over_text.getLocalBounds().height / 2.0);
	game_over_text.setPosition(1920 / 2, 1080 / 2);
	
	instrucciones_text.setFont(font);
	instrucciones_text.setString("Presiona <Enter> para reiniciar\nPresiona <Esc> para salir");
	instrucciones_text.setCharacterSize(24);
	instrucciones_text.setPosition(
		1920.0 / 2 - instrucciones_text.getGlobalBounds().width / 2.0,
		1080.0 * 3.0 / 4.0 - instrucciones_text.getGlobalBounds().height / 2.0);
	
	unsigned int a=puntos_jugador;
	
	std::ofstream o_scores("leaderboard.bin",std::ios::binary|std::ios::app);
	if(!o_scores.is_open()){
		//std::cout<<"no se abrio el archivo"<<std::endl;
	}
	o_scores.write(reinterpret_cast<char*>(&a),sizeof(unsigned int));
	
	o_scores.close();

	std::ifstream i_scores("leaderboard.bin",std::ios::binary|std::ios::ate|std::ios::in);
	if(!i_scores.is_open()){
		//std::cout<<"no se abrio el archivo"<<std::endl;
	}
	int tam= i_scores.tellg()/sizeof(int);
	i_scores.seekg(0);
	std::vector<unsigned int> all_scores(tam);
	
	for(int i=0;i<tam;i++) { 
		i_scores.read(reinterpret_cast<char*>(&all_scores[i]),sizeof(unsigned int));
		//std::cout<<all_scores[i]<<std::endl;
	}
	
	std::stringstream ss2;
	sort(all_scores.begin(),all_scores.end());
	reverse(all_scores.begin(),all_scores.end());
	std::vector<unsigned int> highest_scores;
	if(all_scores.size()<5){
		for(unsigned int i=0;i<all_scores.size();i++) {  
			highest_scores.push_back(all_scores[i]);
			
		}
	}
	else{
		for(int i=0;i<5;i++) {  
		
			highest_scores.push_back(all_scores[i]);
		
		}
	}

	for(unsigned int i=0;i<all_scores.size();i++) { 
		std::cout<<"all_scoress: "<<all_scores[i]<<" ";
	}
	for(unsigned int i=0;i<highest_scores.size();i++) { 
		std::cout<<std::endl<<"score maximos: "<<highest_scores[i]<<" "<<std::endl;
	}
	for(unsigned int i=0;i<highest_scores.size();i++) {  
		
		ss2<<i+1<<" puesto-> "<<highest_scores[i] << std::endl;
		
	}
	//std::cout<<ss2.str()<<std::endl;
	score_text.setFont(font);
	score_text.setString(ss2.str());
	score_text.setCharacterSize(32);
	score_text.setOrigin(score_text.getLocalBounds().width / 2.0,
						 score_text.getLocalBounds().height / 2.0);
	score_text.setPosition(1920 / 2, 1080 / 2-200);
	
}

void GameOverScene::update(float elapsed) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		Game::getInstance().switchScene(new TransitionScene(0, 0));
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		Game::getInstance().cerrarJuego();
	}
}

void GameOverScene::draw(sf::RenderWindow &w) {
	w.setView(view);
	w.draw(game_over_text);
	w.draw(instrucciones_text);
	w.draw(score_text);
}
