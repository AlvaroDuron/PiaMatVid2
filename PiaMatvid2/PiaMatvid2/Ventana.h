#ifndef VENTANA_H
#define VENTANA_H

#include <Windows.h>

class Ventana 
{
private:
	HWND hwnd;
	HINSTANCE hInstance;
	int ancho, alto, mitadAncho, mitadAlto;
public:

	Ventana(int _ancho, int _alto, HWND _hwnd, HINSTANCE _hInsatnce);

	int getAncho();
	int getAlto();
	int getMitadAncho();
	int getMitadAlto();
	HWND getHwnd();
	HINSTANCE gethInstance();
};

#endif // !VENTANA_H
