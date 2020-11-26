#ifndef PANTALLA_MATRICES_H
#define PANTALLA_MATRICES_H

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "Ventana.h"
#include "Defines.h"
#include "Nodo.h"
#include "Validacion.h"

class Matrices
{
private:
	Celda* primeroA;
	Celda* auxA;
	Celda* primeroB;
	Celda* auxB;
	Celda* primeroR;
	Celda* auxR;

	int filasA;
	int columnasA;
	int filasB;
	int columnasB;
	int filasR;
	int columnasR;

	int anchoCeldaA;
	int altoCeldaA;
	int anchoCeldaB;
	int altoCeldaB;
	int anchoCeldaR;
	int altoCeldaR;

	Ventana* ventana;

	HWND btnMedio[5];
	HWND btnMatrizA[3];
	HWND btnMatrizB[4];
	HWND btnResultado[3];
	HWND edtMatrizA[2];
	HWND edtMatrizB[2];
	int anchoCajaMatriz;
	int altoCajaMatriz;

	const int anchoBtnMedio = 100;
	const int altoBtn = 20;
	const int defineBtnMedio[5] = { BTN_INTERCAMBIARM, BTN_SUMARM, BTN_RESTARM, BTN_MULTIPLICARM, BTN_REGRESARM };
	const int defineBtnMatrizA[3] = { BTN_LIMPIARAM, BTN_OKAM, BTN_TRANSPUESTAAM };
	const int defineBtnMatrizB[3] = { BTN_LIMPIARBM, BTN_OKBM, BTN_TRANSPUESTABM };
	const int defineEdtMatrizA[2] = { EDT_FILASAM, EDT_COLUMNASAM };
	const int defineEdtMatrizB[2] = { EDT_FILASBM, EDT_COLUMNASBM };
	const int defineBtnResultado[3] = { BTN_LIMPIARRM, BTN_MOVERAM, BTN_MOVERBM };

	const char* textoBtnMedio[5] = { "Cambiar", "Sumar", "Restar", "Multiplicar", "Regresar" };
	const char* textoBtnMatriz[3] = { "Limpiar", "Ok", "Transpuesta" };
	const char* textoBtnResultado[3] = { "Limpiar", "Mandar a A", "Mandar a B" };

public:

	Matrices(Ventana* _ventana, int _filas, int _columnas);

	void CrearBotones();
	void MostrarBotones();
	void OcultarBotones();
	int getAnchoCajaMatrices();
	int getAltoCajaMatrices();

	//Celdas
	void GenerarNodos(char* _tipo);
	void EliminarNodos(char* _tipo);
	void CrearCeldas(char* _tipo);
	void LimpiarMatriz(char* _tipo);
	void DestruirMatriz(char* _tipo);
	void CambiarDimensiones( char* _tipo);
	void setDimensiones(int _filas, int _columnas, char* _tipo);
	void Transpuesta(char* _tipo);
	void setValoresCeldas(char* _tipo);
	void getValoresCeldas(char* _tipo);
	void LimpiarValoresNodos(char* _tipo);
	void DeshabilitarBotones();
	void HabilitarBotones();
	void MostrarBotonesResultado();
	void OcultarBotonesResultado();
	void LimpiarResultado();
	void MandarResultado(char* _tipo);
	void Intercambiar();
	void Sumar();
	void Restar();
	void Multiplicar();
};

#endif // !PANTALLA_MATRICES_H
