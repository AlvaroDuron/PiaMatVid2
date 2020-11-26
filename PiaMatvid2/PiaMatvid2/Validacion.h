#ifndef VALIDACION_H
#define VALIDACION_H
#include "Nodo.h"
class Validacion 
{
public:
	bool CeldasVacias(Celda* _primero, Celda* _aux);
	bool ValidarFormato(Celda* _primero, Celda* aux);
	bool validarFormatoRotar(Celda* _primero, Celda* aux, int _esRotado);
	bool NoDecimales(Celda* _primero, Celda* _aux);
	bool validarCeros(Celda* _primero, Celda* _aux);
};

#endif // !VALIDACION_H
