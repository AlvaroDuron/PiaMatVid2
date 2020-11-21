#include "PantallaMenu.h"

Menu::Menu(Ventana* _ventana) 
{
    this->btn[0] = NULL;
    this->btn[1] = NULL;
    this->btn[2] = NULL;
    this->btn[3] = NULL;
    this->btn[4] = NULL;
    this->btn[5] = NULL;

    this->ventana = _ventana;
}

void Menu::crearBotones() 
{
    for (int i = 0; i < (sizeof(btn) / sizeof(btn[0])); i++)
        this->btn[i] = CreateWindowEx
        (
            0,
            "BUTTON",
            this->textoBtn[i],
            BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
            this->ventana->getMitadAncho() - this->anchoBoton / 2,
            (50) + (i * this->altoBoton) + (i * 20),
            this->anchoBoton,
            this->altoBoton,
            this->ventana->getHwnd(),
            (HMENU)this->definesBtn[i],
            this->ventana->gethInstance(),
            NULL
        );
}

void Menu::MostarBotones() 
{
    for (int i = 0; i < (sizeof(this->btn) / sizeof(this->btn[0])); i++)
        ShowWindow(this->btn[i], TRUE);
}

void Menu::OcultarBotones()
{
    for (int i = 0; i < (sizeof(this->btn) / sizeof(this->btn[0])); i++)
        ShowWindow(this->btn[i], FALSE);
}