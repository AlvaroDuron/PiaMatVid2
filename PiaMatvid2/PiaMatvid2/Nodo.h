#ifndef NODO_H
#define NODO_H
#include <Windows.h>

struct Celda 
{
    Celda* sig = NULL;
    HWND celda = NULL;
    double valor = NULL;
};

#endif
