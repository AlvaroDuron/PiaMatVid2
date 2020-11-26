#ifndef PANTALLA_VECTORES
#define PANTALLA_VECTORES

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Ventana.h"
#include "Defines.h"
#include "Nodo.h"
#include "Validacion.h"

class Vectores
{
private:

	Ventana* ventana;

	Celda* auxA;
	Celda* primeroA;
	Celda* auxB;
	Celda* primeroB;
	Celda* auxR;
	Celda* primeroR;
	Validacion* validacion;

	HWND btnMedio[4];
	HWND btnVectorA[7];
	HWND btnVectorB[5];
	HWND btnResultado;

	const int defineBtnMedio[4] = { BTN_SUMARV, BTN_RESTARV, BTN_MULTIPLICARV, BTN_REGRESARV };
	const int defineBtnVectorA[7] = { BTN_LIMPIARAV, BTN_LONGITUDAV, BTN_NORMALIZACIONAV, BTN_ESCALARAV, BTN_VECTORAV, BTN_NEGARAV, BTN_UNITARIOAV };
	const int defineBtnVectorB[5] = { BTN_LIMPIARBV, BTN_LONGITUDBV, BTN_NORMALIZACIONBV, BTN_NEGARBV, BTN_UNITARIOBV };
	const int defineBtnResultado = { BTN_LIMPIARRV };

	const char* textoBtnMedio[4] = {"Sumar", "Restar", "Multiplicar", "Regresar"};
	const char* textoBtnVectorA[7] = { "Limpiar", "Longitud", "Normalizar", "Escalar", "Vector", "Negar", "¿Es unitario?" };
	const char* textoBtnVectorB[5] = { "Limpiar", "Longitud", "Normalizar", "Negar", "¿Es unitario?" };
	const char* textoBtnResultado = { "Limpiar" };

	int anchoCajaMatriz;
	int altoCajaMatriz;

	const int anchoBtnMedio = 100;
	const int altoBtn = 20;

	bool esEscalarA;
	bool esEscalarR;

public:
	Vectores(Ventana* _ventana);

	void CrearBotones();
	void MostrarBotones();
	void OcultarBotones();
	void MostrarBotonResultado();
	void OcultarBotonResultado();
	void GenerarNodos(char* _tipo);
	void EliminarNodos(char* _tipo);
	void CrearVector(char* _tipo);
	void DestruirVector(char*  _tipo);
	void HabilitarBotones();
	void DeshabilitarBotones();
	void SetValoresVector(char* _tipo);
	void GetValoresVector(char* _tipo);
	void LimpiarVector(char* _tipo);
	void Longitud(char* _tipo);
	void Normalizar(char* _tipo);
	void LimpiarResultado();
	void LimpiarNodosVector(char* _tipo);
	void Escalar();
	void Vector();
	void EstadoIncialEscalarVector();
	void Suma();
	void Restar();
	void Multiplicar();
	void Negar(char* _tipo);
	void EsUnitario(char* _tipo);
};

#endif // !PANTALLA_VECTORES
