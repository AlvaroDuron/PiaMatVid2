#ifndef CUATERNIONES_H
#define CUATERNIONES_H

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Nodo.h"
#include "Ventana.h"
#include "Defines.h"
#include "Validacion.h"

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

	HWND btnMedio[6];
	HWND btnCuaternionA[8];
	HWND btnCuaternionB[8];
	HWND btnResultado[3];
	int anchoCajaMatriz;
	int altoCajaMatriz;

	const int anchoBtnMedio = 100;
	const int altoBtn = 20;
	const int defineBtnMedio[6] = { BTN_INTERCAMBIARC, BTN_SUMARC, BTN_RESTARC, BTN_MULTIPLICARC, BTN_GRASSMAN , BTN_REGRESARC };
	const int defineBtnCuaternionA[8] = { BTN_LIMPIARAC, BTN_NULOAC, BTN_CONJUGADOAC, BTN_OPUESTOAC, BTN_ABSOLUTOAC, BTN_NORMALIZADOAC, BTN_INVERSOAC, BTN_UNITARIOAC };
	const int defineBtnCuaternionB[8] = { BTN_LIMPIARBC, BTN_NULOBC, BTN_CONJUGADOBC, BTN_OPUESTOBC, BTN_ABSOLUTOBC, BTN_NORMALIZADOBC, BTN_INVERSOBC, BTN_UNITARIOBC };
	const int defineBtnResultado[3] = { BTN_LIMPIARRC, BTN_MOVERAC, BTN_MOVERBC };

	const char* textoBtnMedio[6] = { "Itercambiar", "Sumar", "Restar", "Multiplicar", "Grassman" , "Regresar" };
	const char* textoBtnCuaternion[8] = { "Limpiar", "Nulo", "Conjugado", "Opuesto", "Valor absoluto", "Normalizacion", "Inverso", "¿Es unitario?" };
	const char* textoBtnResultado[3] = { "Limpiar", "Mandar a A", "Mandar a B" };
public:

	Cuaterniones(Ventana* ventana);

	void DeshabilitarBotones();
	void HabilitarBotones();
	void LimpiarResultado();
	void CrearNodosResultado(char* _tipo);
	void CrearVentanasResultado(char* _tipo);
	void EliminarResultado();
	void DestruirVentanas(char* _tipo);
	void CrearBotones();
	void MostrarBotones();
	void OcultarBotones();
	void CrearCuaternio(char* _tipo);
	void DestruirCuaternio(char* _tipo);
	void MostrarBotonesResultado();
	void OcultarBotonesResultado();
	void getValoresCuaternio(char* _tipo);
	void LimpiarValoresNodos(char* _tipo);
	void setValoresCuaternio(char* _tipo);
	void LimpiarCuaternio(char* _tipo);
	void Nulo(char* _tipo);
	void Conjugado(char* _tipo);
	void Opuesto(char* _tipo);
	void ValorAbsoluto(char* _tipo);
	void Normalizacion(char* _tipo);
	void Inverso(char* _tipo);
	void Multiplicar();
	void Grassman();
	void Restar();
	void Sumar();
	void Intercambiar();
	void EsUnitario(char* _tipo);
	void Mandar(char* _tipo);
};

#endif // !CUATERNIONES_H
