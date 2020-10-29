#ifndef CUATERNIONES_H
#define CUATERNIONES_H

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "Nodo.h"
#include "Ventana.h"
#include "Defines.h"

class Cuaterniones 
{
private:
	Celda* primeroA;
	Celda* auxA;
	Celda* primeroB;
	Celda* auxB;
	Celda* primeroR;
	Celda* auxR;

	Ventana* ventana;

	HWND btnMedio[5];
	HWND btnCuaternionA[7];
	HWND btnCuaternionB[7];
	HWND btnResultado[3];
	int anchoCajaMatriz;
	int altoCajaMatriz;

	const int anchoBtnMedio = 100;
	const int altoBtn = 20;
	const int defineBtnMedio[5] = { BTN_INTERCAMBIARC, BTN_SUMARC, BTN_RESTARC, BTN_MULTIPLICARC, BTN_REGRESARC };
	const int defineBtnCuaternionA[7] = { BTN_LIMPIARAC, BTN_NULOAC, BTN_CONJUGADOAC, BTN_OPUESTOAC, BTN_ABSOLUTOAC, BTN_NORMALIZADOAC, BTN_INVERSOAC };
	const int defineBtnCuaternionB[7] = { BTN_LIMPIARBC, BTN_NULOBC, BTN_CONJUGADOBC, BTN_OPUESTOBC, BTN_ABSOLUTOBC, BTN_NORMALIZADOBC, BTN_INVERSOBC };
	const int defineBtnResultado[3] = { BTN_LIMPIARRC, BTN_MOVERAC, BTN_MOVERBC };

	const char* textoBtnMedio[5] = { "Cambiar", "Sumar", "Restar", "Multiplicar", "Regresar" };
	const char* textoBtnCuaternion[7] = { "Limpiar", "Nulo", "Conjugado", "Opuesto", "Valor absoluto", "Normalizacion", "Inverso" };
	const char* textoBtnResultado[3] = { "Limpiar", "Mandar a A", "Mandar a B" };
public:

	Cuaterniones(Ventana* ventana);

	void CrearResultado(char* _tipo);
	void EliminarResultado(char * _tipo);
	void DestruirVentanas(char* _tipo);
	void CrearBotones();
	void MostrarBotones();
	void OcultarBotones();
	void CrearCuaternio(char* _tipo);
	void MostrarBotonesResultado();
	void OcultarBotonesResultado();
	void getValoresCuaternio(char* _tipo);
	void LimpiarValoresNodos(char* _tipo);
	void setValoresCuaternio(char* _tipo);
	void LimpiarCuaternio(char* _tipo);
	void Nulo(char* _tipo);
	void Conjugado(char* _tipo);
	void Opuesto(char* _tipo);
};

#endif // !CUATERNIONES_H
