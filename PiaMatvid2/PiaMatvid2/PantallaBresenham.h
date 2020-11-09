#ifndef PANTALLA_BRESENHAM
#define PANTALLA_BRESENHAM

#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include "Nodo.h"
#include "Defines.h"
#include "Ventana.h"
#include "Validacion.h"

class Bresenham
{
private:
	Celda* primeroA;
	Celda* auxA;
	Celda* primeroR;
	Celda* auxR;
	Validacion* validacion;

	Ventana* ventana;

	int anchoCelda;
	int altoCelda;
	int estadoBresenham;
	double pendiente;

	HWND btnPuntos[6];
	HWND btnResultado;
	HWND editResultado;
	HWND lbl[4];

	const char* textoBtnPuntos[6] = { "Limpiar", "Recta", "Circunferencia", "Elipse",  "Generar" ,"Regresar" };
	const char* textoLblRecta[4] = { "xI", "yI", "xF",  "yF" };
	const char* textoLblCircunferencia[4] = { "xC", "yC", "radio", " " };
	const char* textoLblElipse[4] = { "rX", "rY", "xC",  "yC" };
	const char* textoBtnResultado = { "Limpiar" };

	const int definesBtnPuntos[6] = { BTN_LIMPIARB, BTN_BRESENHAMB, BTN_CIRCUNFERENCIAB, BTN_ELIPSEB, BTN_GENERARPUNTOSB ,BTN_REGRESARB };
	const int definesBtnResultado = { BTN_RESULTADOB };
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
	void OcultarBotonResultado();
	void MostrarBotonResultado();
	void LimpiarValoresNodos(char* _tipo);
	void LimpiarResultado();
	void Circunfernecia();
	void setEstadoBresenham(int estado) { this->estadoBresenham = estado; };
	int getEstadoBresenham() { return this->estadoBresenham; };
	void Elipse();
	void MostrarLblRecta();
	void MostrarLblCircunferencia();
	void MostrarLblElipse();
};

#endif // !PANTALLA_BRESENHAM
