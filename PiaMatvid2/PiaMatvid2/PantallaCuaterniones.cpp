#include "PantallaCuaterniones.h"

Cuaterniones::Cuaterniones(Ventana* _ventana)
{
	//Establecer en Null los botones
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		this->btnMedio[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnCuaternionA) / sizeof(this->btnCuaternionA[0])); i++)
		this->btnCuaternionA[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnCuaternionB) / sizeof(this->btnCuaternionB[0])); i++)
		this->btnCuaternionB[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnResultado) / sizeof(this->btnResultado[0])); i++)
		this->btnResultado[i] = NULL;

	//Caja matriz
	this->ventana = _ventana;
	this->anchoCajaMatriz = (this->ventana->getMitadAncho()) - (this->anchoBtnMedio / 2) - 10;
	this->altoCajaMatriz = 40;

	//Celda
	this->primeroA = NULL;
	this->auxA = NULL;
	this->primeroB = NULL;
	this->auxB = NULL;
	this->primeroR = NULL;
	this->auxR = NULL;
}

void Cuaterniones::CrearResultado(char* _tipo) 
{
	if (_tipo == "cuaternio") 
	{
		//Generar nodos resultado
		for (int i = 0; i < 4; i++) 
		{
			if (this->primeroR == NULL) 
			{
				this->primeroR = new Celda;
				this->auxR = this->primeroR;
			}
			else
			{
				this->auxR->sig = new Celda;
				this->auxR = this->auxR->sig;
			}
		}

		this->auxR = this->primeroR;

		for (int i = 0; i < 4; i++) 
		{
			this->auxR->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				this->ventana->getMitadAncho() - (this->anchoCajaMatriz / 2) + ((i) * (this->anchoCajaMatriz / 4)),
				5 + this->altoCajaMatriz + 5 + (3 * this->altoBtn) + 5,
				this->anchoCajaMatriz / 4,
				this->altoCajaMatriz,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);

			this->auxR = this->auxR->sig;
		}
	}
	else if (_tipo == "unitario")
	{
		this->primeroR = new Celda;
		this->auxR = this->primeroR;

			this->auxR->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				this->ventana->getMitadAncho() - (this->anchoCajaMatriz / 2),
				5 + this->altoCajaMatriz + 5 + (3 * this->altoBtn) + 5,
				this->anchoCajaMatriz,
				this->altoCajaMatriz,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);
	}
}

void Cuaterniones::EliminarResultado(char* _tipo) 
{
	if (_tipo == "cuaternio") 
	{
		this->auxR = this->primeroR;
		for (int i = 0; i < 4; i++) 
		{
			this->primeroR = this->primeroR->sig;
			delete this->auxR;
			this->auxR = this->primeroR;
		}
	}
	else if (_tipo == "unitario") 
	{
		delete primeroR;
		this->auxR = NULL;
		this->primeroR = NULL;
	}
}

void Cuaterniones::DestruirVentanas(char* _tipo) 
{
	if (_tipo == "A") 
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++) 
		{
			DestroyWindow(this->auxA->celda);
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			DestroyWindow(this->auxB->celda);
			this->auxB = this->auxB->sig;
		}
	}
	else if (_tipo == "R")
	{
		this->auxR = this->primeroR;
		for (int i = 0; i < 4; i++)
		{
			DestroyWindow(this->auxR->celda);
			this->auxR = this->auxR->sig;
		}
	}
}

void Cuaterniones::CrearBotones()
{
	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		this->btnMedio[i] = CreateWindowEx
		(
			0,
			"BUTTON",
			this->textoBtnMedio[i],
			BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			(this->ventana->getMitadAncho()) - (this->anchoBtnMedio / 2),
			(5) + (i * this->altoBtn),
			this->anchoBtnMedio,
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineBtnMedio[i],
			this->ventana->gethInstance(),
			NULL
		);

	//Botones CuaternionA
	int contador = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->btnCuaternionA[contador] = CreateWindowEx
			(
				0,
				"BUTTON",
				this->textoBtnCuaternion[contador],
				BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				5 + ((j) * (this->anchoCajaMatriz / 3)),
				5 + this->altoCajaMatriz + 5 + (i * this->altoBtn),
				this->anchoCajaMatriz / 3,
				this->altoBtn,
				this->ventana->getHwnd(),
				(HMENU)this->defineBtnCuaternionA[contador],
				this->ventana->gethInstance(),
				NULL
			);
			i == 2 ? j = 3 : NULL;
			contador++;
		}
	}

	//Botones CuaternionB
	contador = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->btnCuaternionB[contador] = CreateWindowEx
			(
				0,
				"BUTTON",
				this->textoBtnCuaternion[contador],
				BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				(this->ventana->getMitadAncho() + (this->anchoBtnMedio / 2) + 5) + ((j) * (this->anchoCajaMatriz / 3)),
				5 + this->altoCajaMatriz + 5 + (i * this->altoBtn),
				this->anchoCajaMatriz / 3,
				this->altoBtn,
				this->ventana->getHwnd(),
				(HMENU)this->defineBtnCuaternionB[contador],
				this->ventana->gethInstance(),
				NULL
			);
			i == 2 ? j = 3 : NULL;
			contador++;
		}
	}

	//Botones Resultado
	for (int i = 0; i < (sizeof(this->btnResultado) / sizeof(this->btnResultado[0])); i++)
		this->btnResultado[i] = CreateWindowEx
		(
			0,
			"BUTTON",
			this->textoBtnResultado[i],
			BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			((ventana->getMitadAncho()) + (this->anchoCajaMatriz / 2) + 5),
			5 + 40 + 5 + (3 * this->altoBtn) + 5 + (i * this->altoBtn),
			100,
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineBtnResultado[i],
			this->ventana->gethInstance(),
			NULL
		);

}

void Cuaterniones::MostrarBotones()
{
    
	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		ShowWindow(this->btnMedio[i], TRUE);

	//Botones MatrizA
	for (int i = 0; i < (sizeof(this->btnCuaternionA) / sizeof(this->btnCuaternionA[0])); i++)
		ShowWindow(this->btnCuaternionA[i], TRUE);

	//Botones MatrizB
	for (int i = 0; i < (sizeof(this->btnCuaternionB) / sizeof(this->btnCuaternionB[0])); i++)
		ShowWindow(this->btnCuaternionB[i], TRUE);
}

void Cuaterniones::OcultarBotones()
{

	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		ShowWindow(this->btnMedio[i], FALSE);

	//Botones MatrizA
	for (int i = 0; i < (sizeof(this->btnCuaternionA) / sizeof(this->btnCuaternionA[0])); i++)
		ShowWindow(this->btnCuaternionA[i], FALSE);

	//Botones MatrizB
	for (int i = 0; i < (sizeof(this->btnCuaternionB) / sizeof(this->btnCuaternionB[0])); i++)
		ShowWindow(this->btnCuaternionB[i], FALSE);
}

void Cuaterniones::CrearCuaternio(char* _tipo)
{
	if (_tipo == "A")
	{
		//Generar nodos
		for (int i = 0; i < 4; i++)
		{
			if (this->primeroA == NULL)
			{
				this->primeroA = new Celda;
				this->auxA = this->primeroA;
			}
			else
			{
				this->auxA->sig = new Celda;
				this->auxA = this->auxA->sig;
			}
		}

		//Crear Celdas
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			this->auxA->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				5 + ((i) * (this->anchoCajaMatriz / 4)),
				5,
				this->anchoCajaMatriz / 4,
				40,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		//Generar nodos
		for (int i = 0; i < 4; i++)
		{
			if (this->primeroB == NULL)
			{
				this->primeroB = new Celda;
				this->auxB = this->primeroB;
			}
			else
			{
				this->auxB->sig = new Celda;
				this->auxB = this->auxB->sig;
			}
		}

		//Crear Celdas
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			this->auxB->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				this->ventana->getMitadAncho() + (this->anchoBtnMedio / 2) + 5 + ((i) * (this->anchoCajaMatriz / 4)),
				5,
				this->anchoCajaMatriz / 4,
				40,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);
			this->auxB = this->auxB->sig;
		}
	}
	else if (_tipo == "R")
	{
		//Generar nodos
		for (int i = 0; i < 4; i++)
		{
			if (this->primeroR == NULL)
			{
				this->primeroR = new Celda;
				this->auxR = this->primeroR;
			}
			else
			{
				this->auxR->sig = new Celda;
				this->auxR = this->auxR->sig;
			}
		}

		//Crear Celdas
		this->auxR = this->primeroR;
		for (int i = 0; i < 4; i++)
		{
			this->auxR->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				this->ventana->getMitadAncho() - (this->anchoCajaMatriz / 2) + ((i) * (this->anchoCajaMatriz / 4)),
				5 + 40 + 5 + (7 * this->altoBtn) + 5,
				this->anchoCajaMatriz / 4,
				40,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);
			this->auxR = this->auxR->sig;
		}
	}
}

void Cuaterniones::MostrarBotonesResultado()
{
	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnResultado) / sizeof(this->btnResultado[0])); i++)
		ShowWindow(this->btnResultado[i], TRUE);
}

void Cuaterniones::OcultarBotonesResultado()
{
	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnResultado) / sizeof(this->btnResultado[0])); i++)
		ShowWindow(this->btnResultado[i], FALSE);
}

void Cuaterniones::getValoresCuaternio(char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;

		for (int i = 0; i < 4; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			GetWindowText(this->auxA->celda, texto, sizeof(texto));
			this->auxA->valor = atof(texto);
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		char texto[MAXCHAR];
		this->auxB = this->primeroB;

		for (int i = 0; i < 4; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			GetWindowText(this->auxB->celda, texto, sizeof(texto));
			this->auxB->valor = atof(texto);
			this->auxB = this->auxB->sig;
		}
	}
	else if (_tipo == "R")
	{
		char texto[MAXCHAR];
		this->auxR = this->primeroR;

		for (int i = 0; i < 4; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			GetWindowText(this->auxR->celda, texto, sizeof(texto));
			this->auxR->valor = atof(texto);
			this->auxR = this->auxR->sig;
		}
	}
}

void Cuaterniones::LimpiarValoresNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			this->auxA->valor = 0;
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			this->auxB->valor = 0;
			this->auxB = this->auxB->sig;
		}
	}
}

void Cuaterniones::setValoresCuaternio(char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			sprintf_s(texto, "%f", this->auxA->valor);
			SetWindowText(this->auxA->celda, texto);
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		char texto[MAXCHAR];
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			sprintf_s(texto, "%f", this->auxB->valor);
			SetWindowText(this->auxB->celda, texto);
			this->auxB = this->auxB->sig;
		}
	}
	else if (_tipo == "R")
	{
		char texto[MAXCHAR];
		this->auxR = this->primeroR;
		for (int i = 0; i < 4; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			sprintf_s(texto, "%f", this->auxR->valor);
			SetWindowText(this->auxR->celda, texto);
			this->auxR = this->auxR->sig;
		}
	}
}

void Cuaterniones::LimpiarCuaternio(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			SetWindowText(this->auxA->celda, "");
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			SetWindowText(this->auxB->celda, "");
			this->auxB = this->auxB->sig;
		}
	}
}

void Cuaterniones::Nulo(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			SetWindowText(this->auxA->celda, "0");
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			SetWindowText(this->auxB->celda, "0");
			this->auxB = this->auxB->sig;
		}
	}
}

void Cuaterniones::Conjugado(char* _tipo) 
{
	if (_tipo == "A") 
	{
		this->getValoresCuaternio((char*)"A");

		//Conjugado
		this->auxA = this->primeroA->sig;
		for (int i = 0; i < 3; i++) 
		{
			this->auxA->valor = this->auxA->valor * -1;
			this->auxA = this->auxA->sig;
		}

		this->setValoresCuaternio((char*)"A");
		this->LimpiarValoresNodos((char*)"A");
	}
	else if (_tipo == "B")
	{
		this->getValoresCuaternio((char*)"B");

		//Conjugado
		this->auxB = this->primeroB->sig;
		for (int i = 0; i < 3; i++)
		{
			this->auxB->valor = this->auxB->valor * -1;
			this->auxB = this->auxB->sig;
		}

		this->setValoresCuaternio((char*)"B");
		this->LimpiarValoresNodos((char*)"B");
	}
}

void Cuaterniones::Opuesto(char* _tipo)
{
	if (_tipo == "A")
	{
		this->getValoresCuaternio((char*)"A");

		//Conjugado
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			this->auxA->valor = this->auxA->valor * -1;
			this->auxA = this->auxA->sig;
		}

		this->setValoresCuaternio((char*)"A");
		this->LimpiarValoresNodos((char*)"A");
	}
	else if (_tipo == "B")
	{
		this->getValoresCuaternio((char*)"B");

		//Conjugado
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			this->auxB->valor = this->auxB->valor * -1;
			this->auxB = this->auxB->sig;
		}

		this->setValoresCuaternio((char*)"B");
		this->LimpiarValoresNodos((char*)"B");
	}
}