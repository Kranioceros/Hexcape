#ifndef LABERINTO_H
#define LABERINTO_H

#include <stack>
#include <vector>
#include <map> 
#include <SFML/Graphics.hpp>


struct LabParams {
	//unsigned int pasos;
	unsigned int semilla;
	int entrada_x, entrada_y;
	//int salida_x, salida_y;
	unsigned int alto, ancho;
};

struct Coordenadas{
	int x;
	int y;
	Coordenadas(int _x, int _y) : x(_x), y(_y) {}
	Coordenadas() { x = y = 0; }
	bool operator==(const Coordenadas &x) const;
};

struct Celda {
	bool hueca, visible, salida, entrada;
	bool aberturas[6];
	Celda();
	Celda(const bool *aberturas);
	bool visitada;
};

const Coordenadas DIR[] = {Coordenadas(1, -1), Coordenadas(1, 0), Coordenadas(0, 1),
	Coordenadas(-1, 1), Coordenadas(-1, 0), Coordenadas(0, -1)};

class Grilla {
private:
	std::vector< std::vector<Celda> > m_celdas;
	unsigned int m_ancho, m_alto;
public:
	Grilla(unsigned int ancho, unsigned int alto);
	Grilla(std::vector< std::vector<Celda> > &celdas);
	int ancho() const;
	int alto() const;	
	const Celda &celda(Coordenadas pos) const;
	Celda &celda(Coordenadas pos);
};

/* La clase laberinto se encarga de generar una grilla en base a los parametros
que recibe (LabParams). Aqui se encuentra el grueso del codigo generador. Puede
ser que tengas que retocar algo de Grilla y Celda, pero la mayor parte ya esta. */

class Laberinto {
private:
	const float lado = 150, altura_lado = 130, alto = 2*lado;
	const float ancho = 2*altura_lado;
	Grilla Cuadro;
	std::stack<Coordenadas> stack;
	sf::Texture tileset;
	sf::Texture escotillas;
	std::vector<sf::Sprite> spr_tiles;
	std::vector<sf::Sprite> spr_escotillas;
	bool puedeMoverse(Coordenadas pos, Coordenadas dir);
	bool estaDentro(Coordenadas pos, Coordenadas dir);
	void imprimirParedes(const Celda& c);
	void generarlab(unsigned int xh, unsigned int yh);

	int nroTile(const bool *arr) {
		int res = 0;
		for(int i=0; i < 6; i++) {
			res += arr[i] << (6-i-1);
		}
		return res;
	}

	Coordenadas obtenerDir(Coordenadas pos, int &n);
public:
	Laberinto();
	Laberinto(unsigned int semilla, unsigned int e_x, unsigned int e_y, unsigned int alto, unsigned int ancho);
	Laberinto(const LabParams &p);
	Grilla VerGrilla();
	void DibujarLab(sf::RenderWindow &w, float x, float y);
};


#endif
