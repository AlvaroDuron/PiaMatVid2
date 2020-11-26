#ifndef PANTALLA_TRANSFORMACIONES
#define PANTALLA_TRANSFORMACIONES

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Ventana.h"
#include "Nodo.h"
#include "Defines.h"
#include "Validacion.h"

class Transformaciones
{
private:
	Celda* primeroA;
	Celda* auxA;
	Celda* primeroB;
	Celda* auxB;
	Celda* primeroR;
	Celda* auxR;

	Ventana* ventana;

	HWND btnMedio[2];
	HWND btnMatrizA[6];
	HWND btnMatrizB[8];
	HWND btnResultado;
	int anchoCajaMatriz;
	int altoCajaMatriz;
	int esRotacionA;
	int esRotacionB;
	bool enPunto;

	const int anchoBtnMedio = 100;
	const int altoBtn = 20;
	const int defineBtnMedio[2] = { BTN_MULTIPLICART, BTN_REGRESART };
	const int defineBtnMatrizA[6] = { BTN_LIMPIARAT, BTN_TRANSLADARAT, BTN_ESCALARAT, BTN_ROTARXAT, BTN_ROTARYAT, BTN_ROTARZAT };
	const int defineBtnMatrizB[8] = { BTN_LIMPIARBT, BTN_TRANSLADARBT, BTN_ESCALARBT, BTN_ROTARXBT, BTN_ROTARYBT, BTN_ROTARZBT, BTN_PUNTOT, BTN_MATRIZT };
	const int defineBtnResultado = { BTN_LIMPIARRT };

	const char* textoBtnMedio[2] = { "Multiplicar", "Regresar" };
	const char* textoBtnMatrizA[6] = { "Limpiar", "Transladar", "Escalar", "RotarX", "RotarY", "RotarZ" };
	const char* textoBtnMatrizB[8] = { "Limpiar", "Transladar", "Escalar", "RotarX", "RotarY", "RotarZ", "Punto", "Matriz" };
	const char* textoBtnResultado = { "Limpiar resultado" };


public:

	Transformaciones(Ventana* _ventana);

	void CrearBotones();
	void OcultarBotones();
	void OcultarBotonResultado();
	void MostrarBotones();
	void MostrarBotonResultado();
	void GenerarNodos(char* _tipo);
	void EliminarNodos(char* _tipo);
	void CrearMatriz(char* _tipo);
	void DestruirMatriz(char* _tipo);
	void LimpiarMatriz(char* _tipo);
	void Transladar(char* _tipo);
	void Escalar(char* _tipo);
	void Rotar(char *Rotacion, char* _tipo);
	void GetValoresNodos(char* _tipo);
	void LimpiarValoresNodos(char* _tipo);
	void SetValoresMatriz(char* _tipo);
	void DeshabilitarBotones();
	void DeshabilitarBotonesMatriz(char* _tipo);
	void HabilitarBotones();
	void HabilitarBotonesMatriz(char* _tipo);
	void Multiplicar();
	void setRotacionA(int _estado);
	void setRotacionB(int _estado);
	void LimpiarResultado();
	void setPunto(bool _punto) { this->enPunto = _punto; }
};

#endif // !PANTALLA_TRANSFORMACIONES
