#include "headers/Pared.hpp"
#include <cmath>
#include <iostream>

Pared::Pared(unsigned int _xh, unsigned int _yh, unsigned int _tipo_pared, const sf::Texture &_tex) : tex(_tex) {
	xh = _xh; yh = _yh; tipo_pared = _tipo_pared;
	float lado = 150, altura_lado = 130;
	float ancho = 2*altura_lado;
	
	spr_pared.setTexture(tex);
	
	int xr = xh*ancho + yh*altura_lado;
	int yr = yh*(3.0/2)*lado;
	
	float PI = 3.14159;
			
	switch(tipo_pared) {
	case 0:
		spr_pared.setOrigin(0, 0);
		spr_pared.setPosition(  48 + xr + cosf(PI/6.0)*lado*0.5
						, 135 + yr - (lado - sinf(PI/6.0)*lado*0.5));
		spr_pared.setRotation(-60);
		angulo = 120 * PI/180.0;
		break;
	case 1:
		spr_pared.setOrigin(0, 0);
		spr_pared.setPosition(100 + xr + altura_lado,70 + yr - (0.5*lado-0.5*lado));
		spr_pared.setRotation(0);
		angulo = 180 * PI/180.0;
		break;
	case 2:
		spr_pared.setOrigin(0, 0);
		spr_pared.setPosition(130 + xr + altura_lado, 190 + yr - (0.5*lado-0.5*lado));
		spr_pared.setRotation(60);
		angulo = 240 * PI/180.0;
		break;
	case 3:
		spr_pared.setOrigin(0, lado);
		spr_pared.setPosition(60 + xr + cosf(PI/6.0)*lado*0.5
						, 187 + yr + (lado - sinf(PI/6.0)*lado*0.5));
		spr_pared.setRotation(-60);
		angulo = 300 * PI/180.0;
		break;
	case 4:
		spr_pared.setOrigin(30, lado);
		spr_pared.setPosition(95 + xr - cosf(PI/6.0)*lado*0.5
						, 100 + yr + (lado - sinf(PI/6.0)*lado*0.5));
		spr_pared.setRotation(0);
		angulo = 180 * PI/180.0;
		break;
	case 5:
		spr_pared.setOrigin(30, 0);
		spr_pared.setPosition(220 + xr - cosf(PI/6.0)*lado*0.5
						, 130 + yr - (lado - sinf(PI/6.0)*lado*0.5));
		spr_pared.setRotation(60);
		angulo = 60 * PI/180.0;
		break;
	}
}

Pared::Pared(const Pared &p) : Pared(p.xh, p.yh, p.tipo_pared, p.tex) {
}

const sf::Sprite& Pared::verSprite() const{
	return spr_pared;
}
const float Pared::verAngulo() const {
	return angulo;
}
