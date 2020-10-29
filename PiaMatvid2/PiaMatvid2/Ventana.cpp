#include "Ventana.h"

Ventana::Ventana(int _ancho, int _alto, HWND _hwnd, HINSTANCE _hInstance) 
{
	this->ancho = _ancho;
	this->alto = _alto;
	this->mitadAncho = _ancho / 2;
	this->mitadAlto = _alto / 2;
	this->hwnd = _hwnd;
	this->hInstance = _hInstance;
}

int Ventana::getAncho() { return this->ancho; }
int Ventana::getAlto() { return this->alto; }
int Ventana::getMitadAncho() { return this->mitadAncho; }
int Ventana::getMitadAlto() { return this->mitadAlto; }
HWND Ventana::getHwnd() { return this->hwnd; }
HINSTANCE Ventana::gethInstance() { return this->hInstance; }