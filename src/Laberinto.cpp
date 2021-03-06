/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#include "Laberinto.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

bool Coordenadas::operator==(const Coordenadas &x) const {
	return this->x == x.x && this->y == x.y;
}

/* Constructor por defecto. Genera una grilla de ancho x alto con celdas default. */
Grilla::Grilla(unsigned int ancho, unsigned int alto) {
	/* Se crea un vector de vectores */
	m_celdas.resize(ancho);
	for ( std::vector<Celda> &fila : m_celdas) {
		fila.resize(alto, Celda());
	}

	m_alto = alto; m_ancho = ancho;
}

/* Este constructor simplemente copia una matriz de celdas a m_celdas */
Grilla::Grilla(std::vector< std::vector<Celda> > &celdas) {
	m_alto = celdas.size(); m_ancho = celdas[0].size();
	m_celdas = celdas;
}

unsigned int Grilla::alto() const { return m_alto; }
unsigned int Grilla::ancho() const { return m_ancho; }

/* Celda por defecto */
Celda::Celda() {
	entrada = salida = visitada = false;
	visible = hueca = true;
	for (bool &abertura : aberturas)
		abertura = false;
}

/* Este constructor toma un arreglo de bools que representa cuales aberturas hay o no */
Celda::Celda(const bool *aberts) : Celda() {
	for (int i = 0; i < 6; i++)
		aberturas[i] = aberts[i];
}

/* Metodos que devuelven una celda para leer/modificar. Van a ser utiles dentro de
la clase Laberinto, donde seran usados para romper paredes. */

const Celda& Grilla::celda(Coordenadas pos) const {
	return m_celdas[pos.x][pos.y];
}
Celda& Grilla::celda(Coordenadas pos) {
	return m_celdas[pos.x][pos.y];
}

void Laberinto::generarlab(unsigned int xh, unsigned int yh){
	//std::cout << "Empieza GenerarLab" << std::endl;
	stack.push(Coordenadas(xh, yh));
	Celda *cel_actual = &Cuadro.celda(Coordenadas(xh, yh));
	cel_actual->visitada = true;
	//std::cout << "Termino inicio" << std::endl;
	/* Por cada celda en la grilla */
	for(unsigned int i=0;i<(Cuadro.alto()*Cuadro.ancho()-1);i++) {
		/* Si no se puede mover a ninguna celda vecina */
		//std::cout << "------------------------------------" << std::endl;
		//std::cout << "La celda actual es: " << stack.top().x << ", " << stack.top().y << std::endl;
		//std::cout << "Iteracion num " << i << std::endl;
		
		bool seMueve = false;
		for(int j = 0; j < 6; j++){
			bool lala = puedeMoverse(stack.top(), DIR[j]);
			seMueve = seMueve || lala;
			//if(lala) //std::cout<<"la direccion "<<j<<" esta disponible"<<std::endl;	
		}
		
		if(!seMueve) {
			//std::cout << "No se puede mover" << std::endl;
			i=i-1; // Repetir una vez mas porque esta iteracion no realizo un paso exitosamente
			stack.pop(); // Borramos celda actual del stack
			cel_actual = &Cuadro.celda(stack.top()); // La celda actual ahora es la anterior
			continue;
		}
		
		/* Obtenemos una direccion de las disponibles */
		Coordenadas dir_actual_coord;
		int dir_actual_int;
		dir_actual_coord = obtenerDir(stack.top(), dir_actual_int);
		//std::cout << "La direccion elegida es: " << dir_actual_int << std::endl;
		Coordenadas pos_nueva_celda(stack.top().x + dir_actual_coord.x, stack.top().y + dir_actual_coord.y);
		//std::cout << "La celda siguiente es: " << pos_nueva_celda.x << ", " << pos_nueva_celda.y << std::endl;
		Celda &cel_nueva = Cuadro.celda(pos_nueva_celda);
		cel_nueva.visitada = true;
		stack.push(pos_nueva_celda);
		
		/* romper paredeis */

		cel_actual->aberturas[dir_actual_int] = true;
		if (dir_actual_int >= 3) {
			cel_nueva.aberturas[(dir_actual_int + 3) % 6] = true;
		}  else { 
			cel_nueva.aberturas[dir_actual_int + 3] = true;
		}
		
		//std::cout << "Paredes de cel_actual" << std::endl;
//		imprimirParedes(*cel_actual);
		//std::cout << "Paredes de cel_nueva" << std::endl;
//		imprimirParedes(cel_nueva);
		
		cel_actual = &cel_nueva;
				   
		//std::cout << std::endl;
	}
	//std::cout << "Termino el constructor" << std::endl;
}
bool Laberinto::puedeMoverse(Coordenadas pos, Coordenadas dir){
	if(!estaDentro(pos, dir)){
		return false;
	}
	Celda &cel = Cuadro.celda(Coordenadas(pos.x+dir.x,pos.y+dir.y));
	
	if(!cel.hueca || !cel.visible || cel.visitada) {
		//std::cout<<"Esta visitada"<<std::endl;
		return false;
	}

	return true;
}

Grilla Laberinto::VerGrilla(){
	return Cuadro;
}

Laberinto::Laberinto(unsigned int semilla, unsigned int e_x, unsigned int e_y, unsigned int _alto, unsigned int _ancho
		, float paredes_rotas) : Cuadro(_ancho, _alto), spr_tiles(64), spr_escotillas(1) {
	srand(semilla);
	generarlab(e_x,e_y);
	romperParedes(paredes_rotas);

	/* Se cargan las texturas del disco */
	tileset.loadFromFile("assets/hexagonos-2080x2400-debug.png");
	escotillas.loadFromFile("assets/escotillas-516x86.png");
	robertinho.loadFromFile("assets/robertinho2.png");

	/* Se crea un vector de sprites, cada uno con su respectivo tile del tileset */
	for(int i=0; i < 64; i++) {
		int fila = i / 8, col = i % 8;
		spr_tiles[i].setTexture(tileset);
		spr_tiles[i].setTextureRect(
			sf::IntRect(ancho*col, alto*fila, ancho, alto+1)
		);
	}
	
	/* Se crean las paredes que colisionaran con las entidades */
	for(unsigned int yh=0; yh < Cuadro.alto(); yh++) {
		for(unsigned int xh=0; xh < Cuadro.ancho(); xh++) {
			const Celda &c = Cuadro.celda(Coordenadas(xh, yh));
			
			if (!c.aberturas[0]) {
				paredes.push_back(Pared(xh, yh, 0, robertinho));
			}
			if (!c.aberturas[1]) {
				paredes.push_back(Pared(xh, yh, 1, robertinho));
			}
			if (!c.aberturas[2]) {
				paredes.push_back(Pared(xh, yh, 2, robertinho));
			}
			if (!c.aberturas[3]) {
				paredes.push_back(Pared(xh, yh, 3, robertinho));
			}
			if (!c.aberturas[4]) {
				paredes.push_back(Pared(xh, yh, 4, robertinho));
			}
			if (!c.aberturas[5]) {
				paredes.push_back(Pared(xh, yh, 5, robertinho));
			}
		}
	}

	spr_escotillas[0].setTexture(escotillas);
	spr_escotillas[0].setTextureRect(sf::IntRect(0, 0, 86, 86));
	spr_escotillas[0].setOrigin(43, 43);
}

bool Laberinto::estaDentro(Coordenadas pos, Coordenadas dir) {
	unsigned int x = pos.x, y = pos.y;
	int nuevo_x = x + dir.x, nuevo_y = y + dir.y;
	bool res = nuevo_x >= 0 && nuevo_y >= 0 && nuevo_x < (int) Cuadro.ancho() && nuevo_y < (int) Cuadro.alto();

	if (!res)
		;
		//std::cout<<"No esta dentro de la grilla"<<std::endl;
		
	return res;
}

Coordenadas Laberinto::obtenerDir(Coordenadas pos, int &n) {
	std::vector<Coordenadas> disponibles; // Direcciones disponibles
	//std::cout << "Empieza obtenerDir: " << std::endl;
	for(int i = 0; i < 6; i++) {
		if (puedeMoverse(pos, DIR[i]))
			disponibles.push_back(DIR[i]);
	}
	int i = rand() % disponibles.size();
		n = 0;
	if( disponibles[i] == Coordenadas(1, 0) )
		n = 1;
	if( disponibles[i] == Coordenadas(0, 1) )
		n = 2;
	if( disponibles[i] == Coordenadas(-1, 1) )
		n = 3;
	if( disponibles[i] == Coordenadas(-1, 0) )
		n = 4;
	if( disponibles[i] == Coordenadas(0, -1) )
		n = 5;
	
	return disponibles[i];	
}
void Laberinto::imprimirParedes(const Celda& c) {
	std::cout << "[";
	for (auto pared : c.aberturas)
		std::cout << " " << pared << " ";
	std::cout << "]" << std::endl;
}

void Laberinto::DibujarLab(sf::RenderWindow &w, float x, float y) {
	for(unsigned int xh=0; xh < Cuadro.ancho(); xh++) {
		for (unsigned int yh=0; yh < Cuadro.alto(); yh++) {
			const Celda &c = Cuadro.celda(Coordenadas(xh, yh));

			if (c.visible == false)
				continue;

			int xr = x + xh*ancho + yh*altura_lado;
			int yr = y + yh*(3.0/2)*lado;
			int nro_tile = nroTile(c.aberturas);

			spr_escotillas[0].setPosition(xr + altura_lado, yr + lado);
			spr_tiles[nro_tile].setPosition(xr, yr);

			w.draw(spr_tiles[nro_tile]);
//			w.draw(spr_escotillas[0]);
		}
	}
	
	/* Paredes verdes -- debug.lala */
//	for(auto &pared : paredes) {
//		w.draw(pared.verSprite());
//	}
}

const std::vector<Pared>& Laberinto::verParedes() const {
	return paredes;
}

void Laberinto::romperParedes(float probabilidad) {
	if (probabilidad <= 0)
		return ;

	Grilla &g = Cuadro;
	for(unsigned int xh=0; xh < g.ancho(); xh++) {
		for(unsigned int yh=0; yh < g.alto(); yh++) {
			for(unsigned int dir=0; dir < 6; dir++) {
				unsigned int dir_op = dirOpuesta(dir);
				Coordenadas coord_c1(xh, yh);

				bool disponible = true;

				if(!estaDentro(coord_c1, convertirDir(dir))) {
					continue;
				} else {

					Celda &c1 = g.celda(coord_c1);
					Coordenadas coord_c2(xh + convertirDir(dir).x, yh + convertirDir(dir).y);
					Celda &c2 = g.celda(coord_c2);
					
					if(!c1.hueca || !c1.visible || !c2.hueca || !c2.visible) {
						continue;
					} else if(disponible) {

						float rnd = (rand() % 1000) / 1000.0;

						if (rnd < probabilidad) {
							c1.aberturas[dir] = true;
							c2.aberturas[dir_op] = true;
						}
					}
				}
			}
		}
	}
}

unsigned int Laberinto::dirOpuesta(unsigned int dir) {
	switch(dir) {
	case 0: return 3;
	case 1: return 4;
	case 2: return 5;
	case 3: return 0;
	case 4: return 1;
	case 5: return 2;
	}
	return 6;
}

Coordenadas Laberinto::convertirDir(unsigned int dir) {
	switch(dir) {
	case 0: return Coordenadas(1, -1);
	case 1: return Coordenadas(1, 0);
	case 2: return Coordenadas(0, 1);
	case 3: return Coordenadas(-1, 1);
	case 4: return Coordenadas(-1, 0);
	case 5: return Coordenadas(0, -1);
	}
	return Coordenadas(0, 0);
}
