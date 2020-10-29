#ifndef VALIDACION_H
#define VALIDACION_H
#include "Nodo.h"
class Validacion 
{
public:
	bool CeldasVacias(Celda* _primero, Celda* _aux);

	bool ValidarFormato(Celda* _primero, Celda* aux);
};

#endif // !VALIDACION_H
