#ifndef LABERINTO_H
#define LABERINTO_H

#include <vector>

struct LabParams {
	unsigned int long_lado, pasos;
	int entrada_x, entrada_y;
	int salida_x, salida_y;
};

struct Celda {
	bool hueca, visible, salida, entrada;
	bool aberturas[6];
	Celda();
	Celda(const bool *aberturas);
};

class Grilla {
private:
	std::vector< std::vector<Celda> > m_celdas;
	unsigned int m_ancho, m_alto;
public:
	Grilla(unsigned int ancho, unsigned int alto);
	Grilla(std::vector< std::vector<Celda> > &celdas);
	int ancho() const;
	int alto() const;
	const Celda &celda(unsigned int yh, unsigned int xh) const;
	Celda &celda(unsigned int yh, unsigned int xh);
};

/* La clase laberinto se encarga de generar una grilla en base a los parametros
que recibe (LabParams). Aqui se encuentra el grueso del codigo generador. Puede
ser que tengas que retocar algo de Grilla y Celda, pero la mayor parte ya esta. */
class Laberinto {
private:
	
public:
	Laberinto();
	Laberinto(const LabParams &p);
};

#endif
