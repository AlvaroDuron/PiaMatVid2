#ifndef PANTALLA_MENU_H
#define PANTALLA_MENU_H

#include <Windows.h>
#include "Ventana.h"
#include "Defines.h"

class Menu 
{
private: 
    Ventana* ventana;

    HWND btn[3];

    const int anchoBoton = 300;
    const int altoBoton = 40;
    const int definesBtn[3] = { BTN_MATRICES, BTN_CUATERNIONES , BTN_SAIR };

    const char* textoBtn[3] = { "Matrices", "Cuaterniones" ,"Salir" };

public:
    Menu(Ventana* _ventana);

    void crearBotones();
    void MostarBotones();
    void OcultarBotones();
};

#endif // !PANTALLA_MENU_H
