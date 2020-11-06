#ifndef PANTALLA_BRESENHAM
#define PANTALLA_BRESENHAM

#include <Windows.h>
#include <stdio.h>
#include "Nodo.h"
#include "Defines.h"
#include "Ventana.h"

class Bresenham 
{
private:
	Celda* primeroA;
	Celda* auxA;
	Celda* primeroR;
	Celda* auxR;

	Ventana* ventana;

	int xI;
	int yI;
	int xF;
	int yF;
	int deltaX;
	int deltaY;
	int A;
	int B;
	int P;
	int anchoCelda;
	int altoCelda;

	HWND btnPuntos[3];
	HWND editResultado;

	const char* textoBtnPuntos[3] = {"Limpiar", "Bresenham", "Regresar"};

	const int definesBtnPuntos[3] = {BTN_LIMPIARB, BTN_BRESENHAMB, BTN_REGRESARB};
	const int altoBtn = 20;
public:
	Bresenham(Ventana* brensenham);
	void CrearBotones();
	void MostrarBotones();
	void OcultarBotones();
	void GenerarNodos(char* _tipo);
	void EliminarNodos(char* _tipo);
	void DestruirCeldas(char* _tipo);
	void HabilitarBotones();
	void DeshabilitarBotones();
	void GetValoresCeldas(char* _tipo);
	void SetValoresCeldas(char* _tipo);
	void CrearCeldas(char* _tipo);
	void LimpiarCeldas();
	void RealizarBresenham();
	void GenerarNodosP(int cantidad);
};

#endif // !PANTALLA_BRESENHAM
