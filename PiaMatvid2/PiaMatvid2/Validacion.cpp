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

bool Validacion::validarFormatoRotar(Celda* _primero, Celda* _aux, int _esRotado)
{
	_aux = _primero;
	double valores[4] = {NULL};
	bool formatoErroneo = false;
	int contador = 0;
	if (_esRotado == 0)
	{
		for (int i = 0; i < 16; i++)
		{
			if (i == 5 || i == 6 || i == 9 || i == 10)
			{
				valores[contador] = _aux->valor;
				contador++;
			}

			_aux = _aux->sig;
		}
		valores[1] = valores[1] * -1;
		valores[0] == valores[3] ? formatoErroneo = false : formatoErroneo = true;

		valores[1] == valores[2] && formatoErroneo == false ? formatoErroneo = false : formatoErroneo = true;
	}
	else if (_esRotado == 1)
	{
		for (int i = 0; i < 16; i++)
		{
			if (i == 0 || i == 2 || i == 8 || i == 10)
			{
				valores[contador] = _aux->valor;
				contador++;
			}

			_aux = _aux->sig;
		}
		valores[2] = valores[2] * -1;
		valores[0] == valores[3] ? formatoErroneo = false : formatoErroneo = true;
		valores[1] == valores[2] && formatoErroneo == false ? formatoErroneo = false : formatoErroneo = true;
	}
	else if (_esRotado == 2)
	{
		for (int i = 0; i < 16; i++)
		{
			if (i == 0 || i == 1 || i == 4 || i == 5)
			{
				valores[contador] = _aux->valor;
				contador++;
			}

			_aux = _aux->sig;
		}
		valores[1] = valores[1] * -1;
		valores[0] == valores[3] ? formatoErroneo = false : formatoErroneo = true;
		valores[1] == valores[2] && formatoErroneo == false ? formatoErroneo = false : formatoErroneo = true;
	}
	

	return formatoErroneo;
}

bool Validacion::NoDecimales(Celda* _primero, Celda* _aux) 
{
	_aux = _primero;
	char texto[MAXCHAR];
	bool tieneDecimales = false;
	while (_aux->sig != NULL) 
	{
		ZeroMemory(texto, sizeof(texto));
		GetWindowText(_aux->celda, texto, sizeof(texto));

		for (int i = 0; i < strlen(texto); i++) 
			texto[i] == '.' ? tieneDecimales = true : NULL;

		_aux = _aux->sig;
	}

	ZeroMemory(texto, sizeof(texto));
	GetWindowText(_aux->celda, texto, sizeof(texto));

	for (int i = 0; i < strlen(texto); i++)
		texto[i] == '.' ? tieneDecimales = true : NULL;

	return tieneDecimales;
}

bool Validacion::validarCeros(Celda* _primero, Celda* _aux) 
{
	int ceros = 0;

	_aux = _primero;

	for (int i = 0; i < 4; i++) 
	{
		_aux->valor == 0.0f ? ceros++ : NULL;
		_aux = _aux->sig;
	}

	if (ceros == 4) return true;
	if (ceros != 4) return false;
}