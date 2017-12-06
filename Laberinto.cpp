#include "headers/Laberinto.h"

/* Constructor por defecto. Genera una grilla de ancho x alto con celdas default. */
Grilla::Grilla(unsigned int ancho, unsigned int alto) {
	/* Se crea un vector de vectores */
	m_celdas.resize(alto);
	for ( std::vector<Celda> &fila : m_celdas) {
		fila.resize(ancho);
	}

	m_alto = alto; m_ancho = ancho;
}

/* Este constructor simplemente copia una matriz de celdas a m_celdas */
Grilla::Grilla(std::vector< std::vector<Celda> > &celdas) {
	m_alto = celdas.size(); m_ancho = celdas[0].size();
	m_celdas = celdas;
}

int Grilla::alto() const { return m_alto; }
int Grilla::ancho() const { return m_ancho; }

/* Celda por defecto */
Celda::Celda() {
	entrada = salida = false;
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
const Celda& Grilla::celda(unsigned int yh, unsigned int xh) const {
	return m_celdas[yh][xh];
}
Celda& Grilla::celda(unsigned int yh, unsigned int xh) {
	return m_celdas[yh][xh];
}
