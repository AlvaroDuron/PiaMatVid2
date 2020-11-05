#include "PantallaTransformaciones.h"

Transformaciones::Transformaciones(Ventana* _ventana)
{
	this->ventana = _ventana;

	this->esRotacionA = -1;
	this->esRotacionB = -1;
	this->auxA = NULL;
	this->primeroA = NULL;
	this->auxB = NULL;
	this->primeroB = NULL;
	this->auxR = NULL;
	this->primeroR = NULL;

	this->btnResultado = NULL;

	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		this->btnMedio[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
		this->btnMatrizA[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
		this->btnMatrizB[i] = NULL;

	this->anchoCajaMatriz = (this->ventana->getMitadAncho()) - (this->anchoBtnMedio / 2) - 10;
	this->altoCajaMatriz = 40 * 4;

	this->enPunto = false;
}

void Transformaciones::CrearBotones()
{
	//Botones medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
	{
		this->btnMedio[i] = CreateWindowEx
		(
			0,
			"BUTTON",
			this->textoBtnMedio[i],
			BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			(this->ventana->getMitadAncho()) - (this->anchoBtnMedio / 2),
			(5) + ((i) * (this->altoBtn)),
			this->anchoBtnMedio,
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineBtnMedio[i],
			this->ventana->gethInstance(),
			NULL
		);
	}

	//Botones Matriz A
	int contador = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++) {
			if (i == 0)
			{
				this->btnMatrizA[contador] = CreateWindowEx
				(
					0,
					"BUTTON",
					this->textoBtnMatrizA[contador],
					BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
					(5) + ((j) * (this->anchoCajaMatriz / 4)),
					(5) + this->altoCajaMatriz + 5 + ((i)*this->altoBtn),
					this->anchoCajaMatriz / 4,
					this->altoBtn,
					this->ventana->getHwnd(),
					(HMENU)this->defineBtnMatrizA[contador],
					this->ventana->gethInstance(),
					NULL
				);

			}
			else if (i == 1 && j < 2)
			{
				this->btnMatrizA[contador] = CreateWindowEx
				(
					0,
					"BUTTON",
					this->textoBtnMatrizA[contador],
					BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
					(5) + ((j) * (this->anchoCajaMatriz / 4)),
					(5) + this->altoCajaMatriz + 5 + ((i)*this->altoBtn),
					this->anchoCajaMatriz / 4,
					this->altoBtn,
					this->ventana->getHwnd(),
					(HMENU)this->defineBtnMatrizA[contador],
					this->ventana->gethInstance(),
					NULL
				);

			}
			contador++;
		}
	}

	contador = 0;

	////Botones MatrizB
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++) {
			this->btnMatrizB[contador] = CreateWindowEx
			(
				0,
				"BUTTON",
				this->textoBtnMatrizB[contador],
				BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				(this->ventana->getMitadAncho()) + (this->anchoBtnMedio / 2) + (5) + ((j) * (this->anchoCajaMatriz / 4)),
				(5) + this->altoCajaMatriz + 5 + ((i)*this->altoBtn),
				this->anchoCajaMatriz / 4,
				this->altoBtn,
				this->ventana->getHwnd(),
				(HMENU)this->defineBtnMatrizB[contador],
				this->ventana->gethInstance(),
				NULL
			);
			if (contador == 0 || contador == 7)
				EnableWindow(this->btnMatrizB[contador], true);
			else
				EnableWindow(this->btnMatrizB[contador], false);

			contador++;
		}
	}

	//Boton Matriz Resultado
	this->btnResultado = CreateWindowEx
	(
		0,
		"BUTTON",
		this->textoBtnResultado,
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		this->ventana->getMitadAncho() + (this->anchoCajaMatriz / 2) + 5,
		(5) + this->altoCajaMatriz + 5 + ((2) * (this->altoBtn)) + 20,
		this->anchoCajaMatriz / 2,
		this->altoBtn,
		this->ventana->getHwnd(),
		(HMENU)this->defineBtnResultado,
		this->ventana->gethInstance(),
		NULL
	);
}

void Transformaciones::OcultarBotones()
{
	//Botones medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		ShowWindow(this->btnMedio[i], false);


	//Botones Matriz A
	for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
		ShowWindow(this->btnMatrizA[i], false);

	//Botones Matriz B
	for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
		ShowWindow(this->btnMatrizB[i], false);
}

void Transformaciones::OcultarBotonResultado()
{
	ShowWindow(this->btnResultado, false);
}

void Transformaciones::MostrarBotones()
{
	//Botones medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		ShowWindow(this->btnMedio[i], true);


	//Botones Matriz A
	for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
		ShowWindow(this->btnMatrizA[i], true);

	//Botones Matriz B
	for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
		ShowWindow(this->btnMatrizB[i], true);
}

void Transformaciones::MostrarBotonResultado()
{
	ShowWindow(this->btnResultado, true);
}

void Transformaciones::GenerarNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		for (int i = 0; i < 16; i++)
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
	}
	else if (_tipo == "B")
	{
		for (int i = 0; i < 16; i++)
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
	}
	else if (_tipo == "BP")
	{
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
	}
	else if (_tipo == "R")
	{
		for (int i = 0; i < 16; i++)
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
	}
	else if (_tipo == "RP")
	{
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
	}
}

void Transformaciones::EliminarNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 16; i++)
		{
			this->primeroA = this->primeroA->sig;
			delete this->auxA;
			this->auxA = this->primeroA;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		while (this->auxB->sig != NULL)
		{
			this->primeroB = this->primeroB->sig;
			delete this->auxB;
			this->auxB = this->primeroB;
		}
		this->primeroB = NULL;
		delete this->auxB;
		this->auxB = NULL;
	}
	else if (_tipo == "R")
	{
		this->auxR = this->primeroR;
		while (this->auxR->sig != NULL)
		{
			this->primeroR = this->primeroR->sig;
			delete this->auxR;
			this->auxR = this->primeroR;
		}
		this->primeroR = NULL;
		delete this->auxR;
		this->auxR = NULL;
	}
}

void Transformaciones::CrearMatriz(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->auxA->celda = CreateWindowEx
				(
					0,
					"EDIT",
					"",
					ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
					(5) + ((j) * (this->anchoCajaMatriz / 4)),
					(5) + ((i) * (40)),
					this->anchoCajaMatriz / 4,
					40,
					this->ventana->getHwnd(),
					NULL,
					this->ventana->gethInstance(),
					NULL
				);
				EnableWindow(this->auxA->celda, false);
				this->auxA = this->auxA->sig;
			}
		}
	}
	else if (_tipo == "BP")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			this->auxB->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				(this->ventana->getMitadAncho()) + (this->anchoBtnMedio / 2) + (5),
				(5) + ((i) * (40)),
				this->anchoCajaMatriz / 4,
				40,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);
			i == 3 ? EnableWindow(this->auxB->celda, false) : NULL;
			i == 3 ? SetWindowText(this->auxB->celda, "1") : NULL;

			this->auxB = this->auxB->sig;

		}

		this->DeshabilitarBotonesMatriz((char*)"B");
		EnableWindow(this->btnMatrizB[0], true);
		EnableWindow(this->btnMatrizB[7], true);
	}
	else if (_tipo == "RP")
	{
		this->auxR = this->primeroR;
		for (int i = 0; i < 4; i++)
		{
			this->auxR->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				(this->ventana->getMitadAncho()) - ((this->anchoCajaMatriz / 4) / 2),
				(5) + this->altoCajaMatriz + ((2) * (this->altoBtn)) + 10 + ((i) * 40),
				this->anchoCajaMatriz / 4,
				40,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);
			EnableWindow(this->auxR->celda, false);
			this->auxR = this->auxR->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		int contador = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->auxB->celda = CreateWindowEx
				(
					0,
					"EDIT",
					"",
					ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
					(this->ventana->getMitadAncho()) + (this->anchoBtnMedio / 2) + (5) + ((j) * (this->anchoCajaMatriz / 4)),
					(5) + ((i) * (40)),
					this->anchoCajaMatriz / 4,
					40,
					this->ventana->getHwnd(),
					NULL,
					this->ventana->gethInstance(),
					NULL
				);
				EnableWindow(this->auxB->celda, false);

				if (contador == 7)
					EnableWindow(this->btnMatrizB[contador], false);
				else
					EnableWindow(this->btnMatrizB[contador], true);

				this->auxB = this->auxB->sig;
				contador++;
			}
		}
	}
	else if (_tipo == "R")
	{
		this->auxR = this->primeroR;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->auxR->celda = CreateWindowEx
				(
					0,
					"EDIT",
					"",
					ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
					(this->ventana->getMitadAncho()) - (this->anchoCajaMatriz / 2) + ((j) * (this->anchoCajaMatriz / 4)),
					(5) + this->altoCajaMatriz + ((2) * (this->altoBtn)) + 10 + ((i) * (40)),
					this->anchoCajaMatriz / 4,
					40,
					this->ventana->getHwnd(),
					NULL,
					this->ventana->gethInstance(),
					NULL
				);
				EnableWindow(this->auxR->celda, false);
				this->auxR = this->auxR->sig;
			}
		}
	}
}

void Transformaciones::DestruirMatriz(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 16; i++)
		{
			DestroyWindow(this->auxA->celda);
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		while (this->auxB->sig != NULL)
		{
			DestroyWindow(this->auxB->celda);
			this->auxB = this->auxB->sig;
		}
		DestroyWindow(this->auxB->celda);
	}
	else if (_tipo == "R")
	{
		this->auxR = this->primeroR;
		while (this->auxR->sig != NULL)
		{
			DestroyWindow(this->auxR->celda);
			this->auxR = this->auxR->sig;
		}
		DestroyWindow(this->auxR->celda);
	}
}

void Transformaciones::LimpiarMatriz(char* _tipo)
{
	if (_tipo == "A")
	{
		this->esRotacionA = 0;
		this->auxA = this->primeroA;
		for (int i = 0; i < 16; i++)
		{
			EnableWindow(this->auxA->celda, false);
			SetWindowText(this->auxA->celda, "");
			this->auxA = this->auxA->sig;
		}
		this->HabilitarBotonesMatriz((char*)"A");
	}
	else if (_tipo == "B")
	{
		this->esRotacionB = 0;
		this->auxB = this->primeroB;
		int contador = 0;
		while (this->auxB->sig != NULL)
		{
			EnableWindow(this->auxB->celda, false);
			SetWindowText(this->auxB->celda, "");
			this->auxB = this->auxB->sig;
			contador++;
		}
		contador++;
		EnableWindow(this->auxB->celda, false);
		contador > 4 ? SetWindowText(this->auxB->celda, "") : NULL;
	}
}

void Transformaciones::Transladar(char* _tipo)
{
	if (_tipo == "A")
	{
		this->esRotacionA = -1;
		this->auxA = this->primeroA;

		for (int i = 0; i < 16; i++)
		{
			EnableWindow(this->auxA->celda, false);
			this->auxA = this->auxA->sig;
		}

		this->auxA = this->primeroA;
		int contador = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (contador == 0 || contador == 5 || contador == 10 || contador == 15)
					SetWindowText(this->auxA->celda, "1");
				else if (contador == 3 || contador == 7 || contador == 11)
				{
					EnableWindow(this->auxA->celda, true);
					SetWindowText(this->auxA->celda, "");
				}
				else
					SetWindowText(this->auxA->celda, "0");

				this->auxA = this->auxA->sig;
				contador++;
			}
		}
		this->DeshabilitarBotonesMatriz((char*)"A");
		EnableWindow(this->btnMatrizA[0], true);
	}
	if (_tipo == "B")
	{
		this->esRotacionB = -1;
		this->auxB = this->primeroB;

		for (int i = 0; i < 16; i++)
		{
			EnableWindow(this->auxB->celda, false);
			this->auxB = this->auxB->sig;
		}

		this->auxB = this->primeroB;
		int contador = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (contador == 0 || contador == 5 || contador == 10 || contador == 15)
					SetWindowText(this->auxB->celda, "1");
				else if (contador == 3 || contador == 7 || contador == 11)
				{
					EnableWindow(this->auxB->celda, true);
					SetWindowText(this->auxB->celda, "");
				}
				else
					SetWindowText(this->auxB->celda, "0");

				this->auxB = this->auxB->sig;
				contador++;
			}
		}
	}
}

void Transformaciones::Escalar(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		this->esRotacionA = -1;

		for (int i = 0; i < 16; i++)
		{
			EnableWindow(this->auxA->celda, false);
			this->auxA = this->auxA->sig;
		}

		this->auxA = this->primeroA;
		int contador = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (contador == 0 || contador == 5 || contador == 10)
				{
					EnableWindow(this->auxA->celda, true);
					SetWindowText(this->auxA->celda, "");
				}
				else if (contador == 15)
					SetWindowText(this->auxA->celda, "1");
				else
					SetWindowText(this->auxA->celda, "0");

				this->auxA = this->auxA->sig;
				contador++;
			}
		}
		this->DeshabilitarBotonesMatriz((char*)"A");
		EnableWindow(this->btnMatrizA[0], true);
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		this->esRotacionB = -1;

		for (int i = 0; i < 16; i++)
		{
			EnableWindow(this->auxB->celda, false);
			this->auxB = this->auxB->sig;
		}

		this->auxB = this->primeroB;
		int contador = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (contador == 0 || contador == 5 || contador == 10)
				{
					EnableWindow(this->auxB->celda, true);
					SetWindowText(this->auxB->celda, "");
				}
				else if (contador == 15)
					SetWindowText(this->auxB->celda, "1");
				else
					SetWindowText(this->auxB->celda, "0");

				this->auxB = this->auxB->sig;
				contador++;
			}
		}
	}
}

void Transformaciones::Rotar(char* _rotacion, char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 16; i++)
		{
			EnableWindow(this->auxA->celda, false);
			this->auxA = this->auxA->sig;
		}

		if (_rotacion == "X")
		{
			this->esRotacionA = 0;
			this->auxA = this->primeroA;

			for (int i = 0; i < 16; i++)
			{
				if (i == 0 || i == 15)
					SetWindowText(this->auxA->celda, "1");
				else if (i == 5 || i == 6 || i == 9 || i == 10)
				{
					EnableWindow(this->auxA->celda, true);
					SetWindowText(this->auxA->celda, "");
				}
				else
					SetWindowText(this->auxA->celda, "0");

				this->auxA = this->auxA->sig;
			}
		}
		else if (_rotacion == "Y")
		{
			this->esRotacionA = 1;
			this->auxA = this->primeroA;

			for (int i = 0; i < 16; i++)
			{
				if (i == 5 || i == 15)
					SetWindowText(this->auxA->celda, "1");
				else if (i == 0 || i == 2 || i == 8 || i == 10)
				{
					EnableWindow(this->auxA->celda, true);
					SetWindowText(this->auxA->celda, "");
				}
				else
					SetWindowText(this->auxA->celda, "0");

				this->auxA = this->auxA->sig;
			}
		}
		else if (_rotacion == "Z")
		{
			this->esRotacionA = 2;
			this->auxA = this->primeroA;

			for (int i = 0; i < 16; i++)
			{
				if (i == 10 || i == 15)
					SetWindowText(this->auxA->celda, "1");
				else if (i == 0 || i == 1 || i == 4 || i == 5)
				{
					EnableWindow(this->auxA->celda, true);
					SetWindowText(this->auxA->celda, "");
				}
				else
					SetWindowText(this->auxA->celda, "0");

				this->auxA = this->auxA->sig;
			}
		}

		this->DeshabilitarBotonesMatriz((char*)"A");
		EnableWindow(this->btnMatrizA[0], true);
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 16; i++)
		{
			EnableWindow(this->auxB->celda, false);
			this->auxB = this->auxB->sig;
		}

		if (_rotacion == "X")
		{
			this->esRotacionB = 0;
			this->auxB = this->primeroB;

			for (int i = 0; i < 16; i++)
			{
				if (i == 0 || i == 15)
					SetWindowText(this->auxB->celda, "1");
				else if (i == 5 || i == 6 || i == 9 || i == 10)
				{
					EnableWindow(this->auxB->celda, true);
					SetWindowText(this->auxB->celda, "");
				}
				else
					SetWindowText(this->auxB->celda, "0");

				this->auxB = this->auxB->sig;
			}
		}
		else if (_rotacion == "Y")
		{
			this->esRotacionB = 1;
			this->auxB = this->primeroB;

			for (int i = 0; i < 16; i++)
			{
				if (i == 5 || i == 15)
					SetWindowText(this->auxB->celda, "1");
				else if (i == 0 || i == 2 || i == 8 || i == 10)
				{
					EnableWindow(this->auxB->celda, true);
					SetWindowText(this->auxB->celda, "");
				}
				else
					SetWindowText(this->auxB->celda, "0");

				this->auxB = this->auxB->sig;
			}
		}
		else if (_rotacion == "Z")
		{
			this->esRotacionB = 2;
			this->auxB = this->primeroB;

			for (int i = 0; i < 16; i++)
			{
				if (i == 10 || i == 15)
					SetWindowText(this->auxB->celda, "1");
				else if (i == 0 || i == 1 || i == 4 || i == 5)
				{
					EnableWindow(this->auxB->celda, true);
					SetWindowText(this->auxB->celda, "");
				}
				else
					SetWindowText(this->auxB->celda, "0");

				this->auxB = this->auxB->sig;
			}
		}
	}
}

void Transformaciones::GetValoresNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;

		for (int i = 0; i < 16; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			GetWindowText(this->auxA->celda, texto, sizeof(texto));
			this->auxA->valor = atof(texto);

			//Rotacion en x
			if ((i == 5 || i == 10) && this->esRotacionA == 0)
				this->auxA->valor = cos(this->auxA->valor * (3.14159265 / 180.0));
			else if (i == 6 && this->esRotacionA == 0)
				this->auxA->valor = sin(this->auxA->valor * (3.14159265 / 180.0)) * -1;
			else if (i == 9 && this->esRotacionA == 0)
				this->auxA->valor = sin(this->auxA->valor * (3.14159265 / 180.0));

			//Rotacion en y
			if ((i == 0 || i == 10) && this->esRotacionA == 1)
				this->auxA->valor = cos(this->auxA->valor * (3.14159265 / 180.0));
			else if (i == 8 && this->esRotacionA == 1)
				this->auxA->valor = sin(this->auxA->valor * (3.14159265 / 180.0)) * -1;
			else if (i == 2 && this->esRotacionA == 1)
				this->auxA->valor = sin(this->auxA->valor * (3.14159265 / 180.0));

			//Rotacion en z
			if ((i == 0 || i == 5) && this->esRotacionA == 2)
				this->auxA->valor = cos(this->auxA->valor * (3.14159265 / 180.0));
			else if (i == 1 && this->esRotacionA == 2)
				this->auxA->valor = sin(this->auxA->valor * (3.14159265 / 180.0)) * -1;
			else if (i == 4 && this->esRotacionA == 2)
				this->auxA->valor = sin(this->auxA->valor * (3.14159265 / 180.0));

			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		char texto[MAXCHAR];
		this->auxB = this->primeroB;

		if (this->enPunto)
		{
			for (int i = 0; i < 16; i++)
			{
				ZeroMemory(texto, sizeof(texto));
				GetWindowText(this->auxB->celda, texto, sizeof(texto));
				this->auxB->valor = atof(texto);

				//Rotacion en x
				if ((i == 5 || i == 10) && this->esRotacionB == 0)
					this->auxB->valor = cos(this->auxB->valor * (3.14159265 / 180.0));
				else if (i == 6 && this->esRotacionB == 0)
					this->auxB->valor = sin(this->auxB->valor * (3.14159265 / 180.0)) * -1;
				else if (i == 9 && this->esRotacionB == 0)
					this->auxB->valor = sin(this->auxB->valor * (3.14159265 / 180.0));

				//Rotacion en y
				if ((i == 0 || i == 10) && this->esRotacionB == 1)
					this->auxB->valor = cos(this->auxB->valor * (3.14159265 / 180.0));
				else if (i == 8 && this->esRotacionB == 1)
					this->auxB->valor = sin(this->auxB->valor * (3.14159265 / 180.0)) * -1;
				else if (i == 2 && this->esRotacionB == 1)
					this->auxB->valor = sin(this->auxB->valor * (3.14159265 / 180.0));

				//Rotacion en z
				if ((i == 0 || i == 5) && this->esRotacionB == 2)
					this->auxB->valor = cos(this->auxB->valor * (3.14159265 / 180.0));
				else if (i == 1 && this->esRotacionB == 2)
					this->auxB->valor = sin(this->auxB->valor * (3.14159265 / 180.0)) * -1;
				else if (i == 4 && this->esRotacionB == 2)
					this->auxB->valor = sin(this->auxB->valor * (3.14159265 / 180.0));

				this->auxB = this->auxB->sig;
			}
		}
		else if (!this->enPunto)
		{
			for (int i = 0; i < 4; i++)
			{
				ZeroMemory(texto, sizeof(texto));
				GetWindowText(this->auxB->celda, texto, sizeof(texto));
				this->auxB->valor = atof(texto);
				this->auxB = this->auxB->sig;
			}
		}
	}
}

void Transformaciones::LimpiarValoresNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;

		for (int i = 0; i < 16; i++)
		{
			this->auxA->valor = 0;
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;

		while (this->auxB->sig != NULL)
		{
			this->auxB->valor = 0;
			this->auxB = this->auxB->sig;
		}
		this->auxB->valor = 0;
	}
}

void Transformaciones::SetValoresMatriz(char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;
		for (int i = 0; i < 16; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			sprintf_s(texto, "%f", this->auxA->valor);
			SetWindowText(this->auxA->celda, texto);
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "BP")
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
	else if (_tipo == "B")
	{
		char texto[MAXCHAR];
		this->auxB = this->primeroB;
		for (int i = 0; i < 16; i++)
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
		while (this->auxR->sig != NULL)
		{
			ZeroMemory(texto, sizeof(texto));
			sprintf_s(texto, "%f", this->auxR->valor);
			SetWindowText(this->auxR->celda, texto);
			this->auxR = this->auxR->sig;
		}
		ZeroMemory(texto, sizeof(texto));
		sprintf_s(texto, "%f", this->auxR->valor);
		SetWindowText(this->auxR->celda, texto);
	}
}

void Transformaciones::DeshabilitarBotones()
{
	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		EnableWindow(this->btnMedio[i], FALSE);

	//Botones MatrizA
	for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
		EnableWindow(this->btnMatrizA[i], FALSE);

	//Botones MatrizB
	for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
		EnableWindow(this->btnMatrizB[i], FALSE);
}

void Transformaciones::HabilitarBotones()
{
	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		EnableWindow(this->btnMedio[i], TRUE);

	//Botones MatrizA
	for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
		EnableWindow(this->btnMatrizA[i], TRUE);

	//Botones MatrizB
	for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
		EnableWindow(this->btnMatrizB[i], TRUE);
}

void Transformaciones::Multiplicar()
{
	Validacion* validacion = new Validacion();
	if (!validacion->CeldasVacias(this->primeroA, this->auxA) && !validacion->CeldasVacias(this->primeroB, this->auxB))
	{
		if (!validacion->ValidarFormato(this->primeroA, this->auxA) && !validacion->ValidarFormato(this->primeroB, this->auxB))
		{
			this->GetValoresNodos((char*)"A");
			this->GetValoresNodos((char*)"B");

			if (!validacion->validarFormatoRotar(this->primeroA, this->auxA, this->esRotacionA) && !validacion->validarFormatoRotar(this->primeroB, this->auxB, this->esRotacionB))
			{

				!this->enPunto ? this->GenerarNodos((char*)"RP") : this->GenerarNodos((char*)"R");

				//Multiplicar
				this->auxA = this->primeroA;
				this->auxB = this->primeroB;
				this->auxR = this->primeroR;
				Celda* _auxA = this->primeroA;
				Celda* _auxB = this->primeroB;
				if (!this->enPunto)
				{
					for (int i = 0; i < 4; i++)
					{
						for (int x = 0; x < 1; x++)
						{
							this->auxA = _auxA;
							for (int j = 0; j < 4; j++)
							{
								this->auxR->valor = this->auxR->valor + this->auxA->valor * this->auxB->valor;
								for (int h = 0; h < 1; h++)
								{
									this->auxB->sig != NULL ? this->auxB = this->auxB->sig : NULL;
								}

								this->auxA = this->auxA->sig;
							}
							this->auxR = this->auxR->sig;
							_auxB = _auxB->sig;
							this->auxB = _auxB;
						}

						for (int t = 0; t < 4; t++)
							_auxA->sig != NULL ? _auxA = _auxA->sig : NULL;
						_auxB = this->primeroB;
						this->auxB = this->primeroB;
					}
				}
				else if (this->enPunto)
				{
					for (int i = 0; i < 4; i++)
					{
						for (int x = 0; x < 4; x++)
						{
							this->auxA = _auxA;
							for (int j = 0; j < 4; j++)
							{
								this->auxR->valor = this->auxR->valor + this->auxA->valor * this->auxB->valor;
								for (int h = 0; h < 4; h++)
								{
									this->auxB->sig != NULL ? this->auxB = this->auxB->sig : NULL;
								}

								this->auxA = this->auxA->sig;
							}
							this->auxR = this->auxR->sig;
							_auxB = _auxB->sig;
							this->auxB = _auxB;
						}

						for (int t = 0; t < 4; t++)
							_auxA->sig != NULL ? _auxA = _auxA->sig : NULL;
						_auxB = this->primeroB;
						this->auxB = this->primeroB;
					}
				}

				this->LimpiarValoresNodos((char*)"A");
				this->LimpiarValoresNodos((char*)"B");

				!this->enPunto ? this->CrearMatriz((char*)"RP") : this->CrearMatriz((char*)"R");
				this->MostrarBotonResultado();
				this->SetValoresMatriz((char*)"R");

				//Pasar valores a la matriz compuesta
				if (this->enPunto)
				{
					this->auxA = this->primeroA;
					this->auxR = this->primeroR;
					for (int i = 0; i < 16; i++)
					{
						this->auxA->valor = this->auxR->valor;

						this->auxA = this->auxA->sig;
						this->auxR = this->auxR->sig;
					}

					this->SetValoresMatriz((char*)"A");
					this->LimpiarValoresNodos((char*)"A");
				}

				this->DeshabilitarBotones();
			}
			else
			{
				this->LimpiarValoresNodos((char*)"A");
				this->LimpiarValoresNodos((char*)"B");
				MessageBox(ventana->getHwnd(), "Debes poner el mismo angulo", "Mensaje", 0);
			}

			this->esRotacionA = -1;

		}
		else
			MessageBox(ventana->getHwnd(), "Formato incorrecto", "Mensaje", 0);
	}
	else
		MessageBox(this->ventana->getHwnd(), "Faltan de rellenar campos", "Mensaje", 0);

	delete validacion;
}

void Transformaciones::setRotacionA(int _estado) { this->esRotacionA = _estado; }

void Transformaciones::setRotacionB(int _estado) { this->esRotacionB = _estado; }

void Transformaciones::LimpiarResultado()
{
	this->DestruirMatriz((char*)"R");
	this->EliminarNodos((char*)"R");

	this->OcultarBotonResultado();
	this->HabilitarBotones();

	if (this->enPunto)
		EnableWindow(this->btnMatrizB[7], false);
	else if (!this->enPunto)
	{
		this->DeshabilitarBotonesMatriz((char*)"B");
		EnableWindow(this->btnMatrizB[0], true);
		EnableWindow(this->btnMatrizB[7], true);
	}
}

void Transformaciones::DeshabilitarBotonesMatriz(char* _tipo)
{
	if (_tipo == "A")
	{
		//Botones MatrizA
		for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
			EnableWindow(this->btnMatrizA[i], FALSE);
	}
	else if (_tipo == "B")
	{
		//Botones MatrizB
		for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
			EnableWindow(this->btnMatrizB[i], FALSE);
	}
}

void Transformaciones::HabilitarBotonesMatriz(char* _tipo)
{
	if (_tipo == "A")
	{
		//Botones MatrizA
		for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
			EnableWindow(this->btnMatrizA[i], TRUE);
	}
	else if (_tipo == "B")
	{
		//Botones MatrizB
		for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
			EnableWindow(this->btnMatrizB[i], TRUE);
	}
}