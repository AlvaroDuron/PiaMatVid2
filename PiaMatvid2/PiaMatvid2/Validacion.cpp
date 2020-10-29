#include "Validacion.h"

bool Validacion::CeldasVacias(Celda* _primero, Celda* _aux) 
{
	_aux = _primero;
	char texto[MAXCHAR] = { "" };
	bool celdasVacias = false;
	ZeroMemory(texto, sizeof(texto));
	while (_aux->sig != NULL)
	{
		GetWindowText(_aux->celda, texto, sizeof(texto));
		strlen(texto) == 0 ? celdasVacias = true : NULL;
		ZeroMemory(texto, sizeof(texto));
		_aux = _aux->sig;
	}
	GetWindowText(_aux->celda, texto, sizeof(texto));
	strlen(texto) == 0 ? celdasVacias = true : NULL;
	ZeroMemory(texto, sizeof(texto));

	return celdasVacias;
}

bool Validacion::ValidarFormato(Celda* _primero, Celda* _aux) 
{
	_aux = _primero;
	char texto[MAXCHAR] = { "" };
	int largo = 0;
	bool formatoErroneo = false;
	int contador = 0;

	int cantidad = 0;
	while (_aux->sig != NULL) 
	{
		cantidad++;
		_aux = _aux->sig;
	}
	cantidad++;
	_aux = _primero;
	for (int i = 0; i < cantidad; i++)
	{
		GetWindowText(_aux->celda, texto, sizeof(texto));
		largo = strlen(texto);
		for (int j = 0; j < largo; j++)
		{
			texto[j] != '0' &&
				texto[j] != '1' &&
				texto[j] != '2' &&
				texto[j] != '3' &&
				texto[j] != '4' &&
				texto[j] != '5' &&
				texto[j] != '6' &&
				texto[j] != '7' &&
				texto[j] != '8' &&
				texto[j] != '9' &&
				texto[j] != '-' &&
				texto[j] != '.' ? formatoErroneo = true : NULL;
			texto[j] == '-' && j != 0 ? formatoErroneo = true : NULL;
			texto[j] == '-' && largo == 1 ? formatoErroneo = true : NULL;
			texto[j] == '.' && j == 0 ? formatoErroneo = true : NULL;
			texto[j] == '.' ? contador++ : NULL;
			contador > 1 ? formatoErroneo = true : NULL;
		}
		contador = 0;
		_aux->sig != NULL ? _aux = _aux->sig : NULL;
	}

	return formatoErroneo;
}