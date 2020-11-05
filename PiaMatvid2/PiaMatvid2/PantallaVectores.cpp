#include "PantallaVectores.h"

Vectores::Vectores(Ventana* _ventana)
{
	this->ventana = _ventana;

	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		this->btnMedio[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnVectorA) / sizeof(this->btnVectorA[0])); i++)
		this->btnVectorA[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnVectorB) / sizeof(this->btnVectorB[0])); i++)
		this->btnVectorB[i] = NULL;

	this->btnResultado = NULL;

	this->anchoCajaMatriz = (this->ventana->getMitadAncho()) - (this->anchoBtnMedio / 2) - 10;
	this->altoCajaMatriz = 40;

	this->auxA = NULL;
	this->primeroA = NULL;
	this->auxB = NULL;
	this->primeroB = NULL;
	this->auxR = NULL;
	this->primeroR = NULL;

	this->esEscalarA = false;
	this->esEscalarR = false;
}

void Vectores::CrearBotones()
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

	//Botones Vector A
	int contador = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (contador < 5)
				this->btnVectorA[contador] = CreateWindowEx
				(
					0,
					"BUTTON",
					this->textoBtnVectorA[contador],
					BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
					(5) + ((j) * (this->anchoCajaMatriz / 3)),
					(5) + (40) + (5) + ((i) * (this->altoBtn)),
					(this->anchoCajaMatriz / 3),
					this->altoBtn,
					this->ventana->getHwnd(),
					(HMENU)this->defineBtnVectorA[contador],
					this->ventana->gethInstance(),
					NULL
				);

			contador++;
		}
	}

	//Botones Vector B
	for (int i = 0; i < 3; i++)
	{
		this->btnVectorB[i] = CreateWindowEx
		(
			0,
			"BUTTON",
			this->textoBtnVectorB[i],
			BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			(this->ventana->getMitadAncho()) + (this->anchoBtnMedio / 2) + (5) + ((i) * (this->anchoCajaMatriz / 3)),
			(5) + (40) + (5),
			(this->anchoCajaMatriz / 3),
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineBtnVectorB[i],
			this->ventana->gethInstance(),
			NULL
		);
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

void Vectores::MostrarBotones()
{
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		ShowWindow(this->btnMedio[i], TRUE);

	for (int i = 0; i < (sizeof(this->btnVectorA) / sizeof(this->btnVectorA[0])); i++)
		ShowWindow(this->btnVectorA[i], TRUE);

	for (int i = 0; i < (sizeof(this->btnVectorB) / sizeof(this->btnVectorB[0])); i++)
		ShowWindow(this->btnVectorB[i], TRUE);
}

void Vectores::OcultarBotones()
{
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		ShowWindow(this->btnMedio[i], FALSE);

	for (int i = 0; i < (sizeof(this->btnVectorA) / sizeof(this->btnVectorA[0])); i++)
		ShowWindow(this->btnVectorA[i], FALSE);

	for (int i = 0; i < (sizeof(this->btnVectorB) / sizeof(this->btnVectorB[0])); i++)
		ShowWindow(this->btnVectorB[i], FALSE);
}

void Vectores::MostrarBotonResultado()
{
	ShowWindow(this->btnResultado, TRUE);
}

void Vectores::OcultarBotonResultado()
{
	ShowWindow(this->btnResultado, FALSE);
}

void Vectores::GenerarNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		for (int i = 0; i < 3; i++)
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
		for (int i = 0; i < 3; i++)
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
	else if (_tipo == "E")
	{
		this->primeroA = new Celda;
		this->auxA = this->primeroA;
	}
	else if (_tipo == "R")
	{
		for (int i = 0; i < 3; i++)
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
	else if (_tipo == "RE")
	{
		this->primeroR = new Celda;
		this->auxR = this->primeroR;
	}
}

void Vectores::EliminarNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		while (this->auxA->sig != NULL)
		{
			this->primeroA = this->primeroA->sig;
			delete this->auxA;
			this->auxA = this->primeroA;
		}
		this->primeroA = NULL;
		delete this->auxA;
		this->auxA = NULL;
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

void Vectores::CrearVector(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 3; i++)
		{
			this->auxA->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				(5) + ((i) * (this->anchoCajaMatriz / 3)),
				5,
				this->anchoCajaMatriz / 3,
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
		this->auxB = this->primeroB;
		for (int i = 0; i < 3; i++)
		{
			this->auxB->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				(this->ventana->getMitadAncho()) + (this->anchoBtnMedio / 2) + 5 + ((i) * (this->anchoCajaMatriz / 3)),
				5,
				this->anchoCajaMatriz / 3,
				40,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);

			this->auxB = this->auxB->sig;
		}
	}
	else if (_tipo == "E")
	{
		this->auxA->celda = CreateWindowEx
		(
			0,
			"EDIT",
			"",
			ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			5,
			5,
			this->anchoCajaMatriz,
			this->altoCajaMatriz,
			this->ventana->getHwnd(),
			NULL,
			this->ventana->gethInstance(),
			NULL
		);
	}
	else if (_tipo == "R")
	{
		this->auxR = this->primeroR;
		for (int i = 0; i < 3; i++)
		{
			this->auxR->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				(this->ventana->getMitadAncho()) - (this->anchoCajaMatriz / 2) + ((i) * (this->anchoCajaMatriz / 3)),
				(5) + (this->altoCajaMatriz) + (5) + (2 * this->altoBtn) + 5,
				this->anchoCajaMatriz / 3,
				(40),
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);

			this->auxR = this->auxR->sig;
		}
	}
	else if (_tipo == "RE")
	{
		this->auxR = this->primeroR;

		this->auxR->celda = CreateWindowEx
		(
			0,
			"EDIT",
			"",
			ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			(this->ventana->getMitadAncho()) - (this->anchoCajaMatriz / 2),
			(5) + (this->altoCajaMatriz) + (5) + (2 * this->altoBtn) + 5,
			this->anchoCajaMatriz / 4,
			(40) + (10) + (2 * this->altoBtn) + 5,
			this->ventana->getHwnd(),
			NULL,
			this->ventana->gethInstance(),
			NULL
		);
	}
}

void Vectores::DestruirVector(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 3; i++)
		{
			DestroyWindow(this->auxA->celda);

			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 3; i++)
		{
			DestroyWindow(this->auxB->celda);

			this->auxB = this->auxB->sig;
		}
	}
	else if (_tipo == "E")
	{
		DestroyWindow(this->auxA->celda);
	}
	else if (_tipo == "R")
	{
		this->auxR = this->primeroR;
		for (int i = 0; i < 3; i++)
		{
			DestroyWindow(this->auxR->celda);

			this->auxR = this->auxR->sig;
		}
	}
	else if (_tipo == "RE")
	{
		DestroyWindow(this->auxR->celda);
	}
}

void Vectores::HabilitarBotones()
{
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		EnableWindow(this->btnMedio[i], TRUE);

	for (int i = 0; i < (sizeof(this->btnVectorA) / sizeof(this->btnVectorA[0])); i++)
		EnableWindow(this->btnVectorA[i], TRUE);

	for (int i = 0; i < (sizeof(this->btnVectorB) / sizeof(this->btnVectorB[0])); i++)
		EnableWindow(this->btnVectorB[i], TRUE);
}

void Vectores::DeshabilitarBotones()
{
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		EnableWindow(this->btnMedio[i], FALSE);

	for (int i = 0; i < (sizeof(this->btnVectorA) / sizeof(this->btnVectorA[0])); i++)
		EnableWindow(this->btnVectorA[i], FALSE);

	for (int i = 0; i < (sizeof(this->btnVectorB) / sizeof(this->btnVectorB[0])); i++)
		EnableWindow(this->btnVectorB[i], FALSE);
}

void Vectores::SetValoresVector(char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;
		for (int i = 0; i < 3; i++)
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
		for (int i = 0; i < 3; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			sprintf_s(texto, "%f", this->auxB->valor);
			SetWindowText(this->auxB->celda, texto);
			this->auxB = this->auxB->sig;
		}
	}
	else if (_tipo == "E")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;
		ZeroMemory(texto, sizeof(texto));
		sprintf_s(texto, "%f", this->auxA->valor);
		SetWindowText(this->auxA->celda, texto);
	}
	else if (_tipo == "R")
	{
		char texto[MAXCHAR];
		this->auxR = this->primeroR;
		for (int i = 0; i < 3; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			sprintf_s(texto, "%f", this->auxR->valor);
			SetWindowText(this->auxR->celda, texto);
			this->auxR = this->auxR->sig;
		}
	}
	else if (_tipo == "RE")
	{
		char texto[MAXCHAR];
		this->auxR = this->primeroR;
		ZeroMemory(texto, sizeof(texto));
		sprintf_s(texto, "%f", this->auxR->valor);
		SetWindowText(this->auxR->celda, texto);
	}
}

void Vectores::GetValoresVector(char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;

		for (int i = 0; i < 3; i++)
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

		for (int i = 0; i < 3; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			GetWindowText(this->auxB->celda, texto, sizeof(texto));
			this->auxB->valor = atof(texto);

			this->auxB = this->auxB->sig;
		}

	}
	else if (_tipo == "E")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;

		ZeroMemory(texto, sizeof(texto));
		GetWindowText(this->auxA->celda, texto, sizeof(texto));
		this->auxA->valor = atof(texto);
	}
}

void Vectores::LimpiarVector(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		while (this->auxA->sig != NULL)
		{
			SetWindowText(this->auxA->celda, "");
			this->auxA = this->auxA->sig;
		}
		SetWindowText(this->auxA->celda, "");
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 3; i++)
		{
			SetWindowText(this->auxB->celda, "");
			this->auxB = this->auxB->sig;
		}

	}
}

void Vectores::LimpiarNodosVector(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		while (this->auxA->sig != NULL)
		{
			this->auxA->valor = 0;
			this->auxA = this->auxA->sig;
		}
		this->auxA->valor = 0;
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 3; i++)
		{
			this->auxB->valor = 0;
			this->auxB = this->auxB->sig;
		}

	}
}

void Vectores::Longitud(char* _tipo)
{
	if (_tipo == "A")
	{
		this->esEscalarR = true;
		this->GetValoresVector((char*)"A");

		double longitud = 0.0;

		//Longitud
		this->auxA = this->primeroA;
		for (int i = 0; i < 3; i++)
		{
			longitud = longitud + pow(this->auxA->valor, 2);

			this->auxA = this->auxA->sig;
		}

		longitud = sqrt(longitud);

		this->GenerarNodos((char*)"RE");
		this->CrearVector((char*)"RE");

		this->primeroR->valor = longitud;

		this->SetValoresVector((char*)"RE");

		this->LimpiarNodosVector((char*)"A");

		this->MostrarBotonResultado();
		this->DeshabilitarBotones();

	}
	else if (_tipo == "B")
	{
		this->esEscalarR = true;
		this->GetValoresVector((char*)"B");

		double longitud = 0.0;

		//Longitud
		this->auxB = this->primeroB;
		for (int i = 0; i < 3; i++)
		{
			longitud = longitud + pow(this->auxB->valor, 2);

			this->auxB = this->auxB->sig;
		}

		longitud = sqrt(longitud);

		this->GenerarNodos((char*)"RE");
		this->CrearVector((char*)"RE");

		this->primeroR->valor = longitud;

		this->SetValoresVector((char*)"RE");

		this->LimpiarNodosVector((char*)"B");

		this->MostrarBotonResultado();
		this->DeshabilitarBotones();
	}
}

void Vectores::Normalizar(char* _tipo)
{
	if (_tipo == "A")
	{
		this->esEscalarR = false;
		this->GetValoresVector((char*)"A");

		double longitud = 0.0;

		//Longitud
		this->auxA = this->primeroA;
		for (int i = 0; i < 3; i++)
		{
			longitud = longitud + pow(this->auxA->valor, 2);

			this->auxA = this->auxA->sig;
		}

		longitud = sqrt(longitud);

		this->GenerarNodos((char*)"R");

		this->auxA = this->primeroA;
		this->auxR = this->primeroR;

		for (int i = 0; i < 3; i++)
		{
			this->auxR->valor = this->auxA->valor / longitud;

			this->auxA = this->auxA->sig;
			this->auxR = this->auxR->sig;
		}

		this->CrearVector((char*)"R");
		this->SetValoresVector((char*)"R");

		this->LimpiarNodosVector((char*)"A");

		this->MostrarBotonResultado();
		this->DeshabilitarBotones();

	}
	else if (_tipo == "B")
	{
		this->esEscalarR = false;
		this->GetValoresVector((char*)"B");

		double longitud = 0.0;

		//Longitud
		this->auxB = this->primeroB;
		for (int i = 0; i < 3; i++)
		{
			longitud = longitud + pow(this->auxB->valor, 2);

			this->auxB = this->auxB->sig;
		}

		longitud = sqrt(longitud);

		this->GenerarNodos((char*)"R");

		this->auxB = this->primeroB;
		this->auxR = this->primeroR;

		for (int i = 0; i < 3; i++)
		{
			this->auxR->valor = this->auxB->valor / longitud;

			this->auxB = this->auxB->sig;
			this->auxR = this->auxR->sig;
		}

		this->CrearVector((char*)"R");
		this->SetValoresVector((char*)"R");

		this->LimpiarNodosVector((char*)"A");

		this->MostrarBotonResultado();
		this->DeshabilitarBotones();
	}
}

void Vectores::LimpiarResultado()
{
	!this->esEscalarR ? this->DestruirVector((char*)"R") : this->DestruirVector((char*)"RE");
	!this->esEscalarR ? this->EliminarNodos((char*)"R") : this->EliminarNodos((char*)"RE");
	this->OcultarBotonResultado();
	this->HabilitarBotones();
}

void Vectores::Escalar()
{
	//Escalar
	this->DestruirVector((char*)"A");
	this->EliminarNodos((char*)"A");
	this->GenerarNodos((char*)"E");
	this->CrearVector((char*)"E");

	EnableWindow(this->btnVectorA[3], false);
	EnableWindow(this->btnVectorA[1], false);
	EnableWindow(this->btnVectorA[2], false);
	EnableWindow(this->btnVectorA[4], true);

	//Deshabilitar botones medios
	EnableWindow(this->btnMedio[0], false);
	EnableWindow(this->btnMedio[1], false);
}

void Vectores::Vector()
{
	//Escalar
	this->DestruirVector((char*)"E");
	this->EliminarNodos((char*)"A");
	this->GenerarNodos((char*)"A");
	this->CrearVector((char*)"A");

	this->auxA = this->primeroA;

	EnableWindow(this->btnVectorA[4], false);
	EnableWindow(this->btnVectorA[1], true);
	EnableWindow(this->btnVectorA[2], true);
	EnableWindow(this->btnVectorA[3], true);

	//Habilitar botones medio
	EnableWindow(this->btnMedio[0], true);
	EnableWindow(this->btnMedio[1], true);
}

void Vectores::EstadoIncialEscalarVector()
{
	EnableWindow(this->btnVectorA[4], false);
	EnableWindow(this->btnVectorA[3], true);
}

void Vectores::Suma()
{
	this->GetValoresVector((char*)"A");
	this->GetValoresVector((char*)"B");

	this->GenerarNodos((char*)"R");

	//Sumar
	this->auxA = this->primeroA;
	this->auxB = this->primeroB;
	this->auxR = this->primeroR;
	for (int i = 0; i < 3; i++)
	{
		this->auxR->valor = this->auxA->valor + this->auxB->valor;

		this->auxA = this->auxA->sig;
		this->auxB = this->auxB->sig;
		this->auxR = this->auxR->sig;
	}

	this->LimpiarNodosVector((char*)"A");
	this->LimpiarNodosVector((char*)"B");

	this->CrearVector((char*)"R");
	this->SetValoresVector((char*)"R");

	this->MostrarBotonResultado();
	this->DeshabilitarBotones();
}

void Vectores::Restar()
{
	this->GetValoresVector((char*)"A");
	this->GetValoresVector((char*)"B");

	this->GenerarNodos((char*)"R");

	//Sumar
	this->auxA = this->primeroA;
	this->auxB = this->primeroB;
	this->auxR = this->primeroR;
	for (int i = 0; i < 3; i++)
	{
		this->auxR->valor = this->auxA->valor - this->auxB->valor;

		this->auxA = this->auxA->sig;
		this->auxB = this->auxB->sig;
		this->auxR = this->auxR->sig;
	}

	this->LimpiarNodosVector((char*)"A");
	this->LimpiarNodosVector((char*)"B");

	this->CrearVector((char*)"R");
	this->SetValoresVector((char*)"R");

	this->MostrarBotonResultado();
	this->DeshabilitarBotones();
}

void Vectores::Multiplicar()
{
	//Obtener valores de los nodosde A manualmente

	int contador = 0;
	this->auxA = this->primeroA;
	while (this->auxA->sig != NULL)
	{

		contador++;
		this->auxA = this->auxA->sig;
	}
	contador++;

	if (contador == 3)
	{
		this->GetValoresVector((char*)"A");
		this->GetValoresVector((char*)"B");

		this->GenerarNodos((char*)"R");

		//Multiplicar

		this->auxA = this->primeroA;
		this->auxB = this->primeroB;
		this->auxR = this->primeroR;

		//i
		this->auxR->valor = (this->auxA->sig->valor * this->auxB->sig->sig->valor) - (this->auxA->sig->sig->valor * this->auxB->sig->valor);
		this->auxR = this->auxR->sig;
		
		//j
		this->auxR->valor = (this->auxA->sig->sig->valor * this->auxB->valor) - (this->auxA->valor * this->auxB->sig->sig->valor);
		this->auxR = this->auxR->sig;

		//k
		this->auxR->valor = (this->auxA->valor * this->auxB->sig->valor) - (this->auxA->sig->valor * this->auxB->valor);

		this->CrearVector((char*)"R");
		this->SetValoresVector((char*)"R");

		this->LimpiarNodosVector((char*)"A");
		this->LimpiarNodosVector((char*)"B");

		this->MostrarBotonResultado();
		this->DeshabilitarBotones();
	}
	else if (contador == 1)
	{
		this->GetValoresVector((char*)"E");
		this->GetValoresVector((char*)"B");

		this->GenerarNodos((char*)"R");

		//Multiplicar

		this->auxA = this->primeroA;
		this->auxB = this->primeroB;
		this->auxR = this->primeroR;

		for (int i = 0; i < 3; i++) 
		{
			this->auxR->valor = this->auxA->valor * this->auxB->valor;

			this->auxR = this->auxR->sig;
			this->auxB = this->auxB->sig;
		}

		this->CrearVector((char*)"R");
		this->SetValoresVector((char*)"R");

		this->LimpiarNodosVector((char*)"A");
		this->LimpiarNodosVector((char*)"B");

		this->MostrarBotonResultado();
		this->DeshabilitarBotones();
	}
}