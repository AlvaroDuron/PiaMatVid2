#ifndef PANTALLA_MENU_H
#define PANTALLA_MENU_H

#include <Windows.h>
#include "Ventana.h"
#include "Defines.h"

class Menu
{
private:
	Ventana* ventana;

	HWND btn[6];

	const int anchoBoton = 300;
	const int altoBoton = 40;
	const int definesBtn[6] = { BTN_MATRICES, BTN_CUATERNIONES, BTN_TRANSFORMACIONES , BTN_VECTORES , BTN_BRESENHAM ,BTN_SAIR };

	const char* textoBtn[6] = { "Matrices", "Cuaterniones", "Transformaciones", "Vectores", "Bresenham" ,"Salir" };

public:
	Menu(Ventana* _ventana);

	void crearBotones();
	void MostarBotones();
	void OcultarBotones();
};

#endif // !PANTALLA_MENU_H
