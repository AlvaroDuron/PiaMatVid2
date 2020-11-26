#include "PantallaMatrices.h"

Matrices::Matrices(Ventana* _ventana, int _filas, int _columnas)
{
	//Establecer en Null los botones
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		this->btnMedio[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
		this->btnMatrizA[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
		this->btnMatrizB[i] = NULL;

	for (int i = 0; i < (sizeof(this->btnResultado) / sizeof(this->btnResultado[0])); i++)
		this->btnResultado[i] = NULL;

	for (int i = 0; i < (sizeof(this->edtMatrizA) / sizeof(this->edtMatrizA[0])); i++)
		this->edtMatrizA[i] = NULL;

	for (int i = 0; i < (sizeof(this->edtMatrizB) / sizeof(this->edtMatrizB[0])); i++)
		this->edtMatrizB[i] = NULL;

	//Caja matriz
	this->ventana = _ventana;
	this->anchoCajaMatriz = (this->ventana->getMitadAncho()) - (this->anchoBtnMedio / 2) - 10;
	this->altoCajaMatriz = (this->ventana->getMitadAlto()) - (2 * this->altoBtn) - 10;

	//Celda
	this->primeroA = NULL;
	this->auxA = NULL;
	this->primeroB = NULL;
	this->auxB = NULL;
	this->primeroR = NULL;
	this->auxR = NULL;

	this->filasR = 0;
	this->columnasR = 0;
	this->filasA = _filas;
	this->columnasA = _columnas;
	this->filasB = _filas;
	this->columnasB = _columnas;

	this->anchoCeldaR = 0;
	this->anchoCeldaA = (this->anchoCajaMatriz / this->columnasA);
	this->anchoCeldaB = this->anchoCeldaA;
	this->altoCeldaR = 0;
	this->altoCeldaA = (this->altoCajaMatriz / this->filasA);
	this->altoCeldaB = this->altoCeldaA;
}

void Matrices::CrearBotones()
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
			(5) + (i * this->altoBtn) + ((i) * (((this->altoCajaMatriz) / (sizeof(this->btnMedio) / sizeof(this->btnMedio[0]))) - (this->altoBtn))),
			this->anchoBtnMedio,
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineBtnMedio[i],
			this->ventana->gethInstance(),
			NULL
		);

	//Botones MatrizA
	for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
		this->btnMatrizA[i] = CreateWindowEx
		(
			0,
			"BUTTON",
			this->textoBtnMatriz[i],
			BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			i == 1 ? (5) + ((this->anchoCajaMatriz) - ((this->anchoCajaMatriz / 2) / 3)) : 5,
			i == 2 ? (this->altoCajaMatriz + 10) + (this->altoBtn) : (this->altoCajaMatriz + 10),
			i == 1 ? ((this->anchoCajaMatriz / 2) / 3) : this->anchoCajaMatriz / 2,
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineBtnMatrizA[i],
			this->ventana->gethInstance(),
			NULL
		);

	//Botones MatrizB
	for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
		this->btnMatrizB[i] = CreateWindowEx
		(
			0,
			"BUTTON",
			this->textoBtnMatriz[i],
			BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			i == 1 ? ((this->ventana->getMitadAncho()) + (this->anchoBtnMedio / 2)) + (5) + ((this->anchoCajaMatriz) - ((this->anchoCajaMatriz / 2) / 3))
			: ((this->ventana->getMitadAncho()) + (this->anchoBtnMedio / 2)) + (5),
			i == 2 ? (this->altoCajaMatriz + 10) + (this->altoBtn) : (this->altoCajaMatriz + 10),
			i == 1 ? ((this->anchoCajaMatriz / 2) / 3) : this->anchoCajaMatriz / 2,
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineBtnMatrizB[i],
			this->ventana->gethInstance(),
			NULL
		);

	//Botones Resultado
	for (int i = 0; i < (sizeof(this->btnResultado) / sizeof(this->btnResultado[0])); i++)
		this->btnResultado[i] = CreateWindowEx
		(
			0,
			"BUTTON",
			this->textoBtnResultado[i],
			BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			((ventana->getMitadAncho()) + (this->anchoCajaMatriz / 2) + 5),
			(this->altoCajaMatriz + 5 + 5 + (2 * this->altoBtn) + 5) + (i * this->altoBtn),
			100,
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineBtnResultado[i],
			this->ventana->gethInstance(),
			NULL
		);

	//Edt matriz A
	for (int i = 0; i < (sizeof(this->edtMatrizA) / sizeof(this->edtMatrizA[0])); i++)
		this->edtMatrizA[i] = CreateWindowEx
		(
			0,
			"EDIT",
			"",
			ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			(5) + (this->anchoCajaMatriz / 2) + ((i) * ((this->anchoCajaMatriz / 2) / (3))),
			(this->altoCajaMatriz + 10),
			((this->anchoCajaMatriz / 2) / (3)),
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineEdtMatrizA[i],
			this->ventana->gethInstance(),
			NULL
		);

	//Edt matriz B
	for (int i = 0; i < (sizeof(this->edtMatrizB) / sizeof(this->edtMatrizB[0])); i++)
		this->edtMatrizB[i] = CreateWindowEx
		(
			0,
			"EDIT",
			"",
			ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			((this->ventana->getMitadAncho()) + (this->anchoBtnMedio / 2)) + (5) + (this->anchoCajaMatriz / 2) + ((i) * ((this->anchoCajaMatriz / 2) / (3))),
			(this->altoCajaMatriz + 10),
			((this->anchoCajaMatriz / 2) / (3)),
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->defineEdtMatrizB[i],
			this->ventana->gethInstance(),
			NULL
		);
}

void Matrices::MostrarBotones()
{

	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		ShowWindow(this->btnMedio[i], TRUE);

	//Botones MatrizA
	for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
		ShowWindow(this->btnMatrizA[i], TRUE);

	//Botones MatrizB
	for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
		ShowWindow(this->btnMatrizB[i], TRUE);

	//Edt matriz A
	for (int i = 0; i < (sizeof(this->edtMatrizA) / sizeof(this->edtMatrizA[0])); i++)
		ShowWindow(this->edtMatrizA[i], TRUE);

	char texto[MAXCHAR];
	ZeroMemory(texto, sizeof(texto));
	_itoa_s(this->filasA, texto, sizeof(texto), 10);
	SetWindowText(this->edtMatrizA[0], texto);

	ZeroMemory(texto, sizeof(texto));
	_itoa_s(this->columnasA, texto, sizeof(texto), 10);
	SetWindowText(this->edtMatrizA[1], texto);

	//Edt matriz B
	for (int i = 0; i < (sizeof(this->edtMatrizB) / sizeof(this->edtMatrizB[0])); i++)
		ShowWindow(this->edtMatrizB[i], TRUE);

	ZeroMemory(texto, sizeof(texto));
	_itoa_s(this->filasB, texto, sizeof(texto), 10);
	SetWindowText(this->edtMatrizB[0], texto);

	ZeroMemory(texto, sizeof(texto));
	_itoa_s(this->columnasB, texto, sizeof(texto), 10);
	SetWindowText(this->edtMatrizB[1], texto);
}

void Matrices::OcultarBotones()
{

	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnMedio) / sizeof(this->btnMedio[0])); i++)
		ShowWindow(this->btnMedio[i], FALSE);

	//Botones MatrizA
	for (int i = 0; i < (sizeof(this->btnMatrizA) / sizeof(this->btnMatrizA[0])); i++)
		ShowWindow(this->btnMatrizA[i], FALSE);

	//Botones MatrizB
	for (int i = 0; i < (sizeof(this->btnMatrizB) / sizeof(this->btnMatrizB[0])); i++)
		ShowWindow(this->btnMatrizB[i], FALSE);

	//Edt matriz A
	for (int i = 0; i < (sizeof(this->edtMatrizA) / sizeof(this->edtMatrizA[0])); i++)
		ShowWindow(this->edtMatrizA[i], FALSE);

	//Edt matriz B
	for (int i = 0; i < (sizeof(this->edtMatrizB) / sizeof(this->edtMatrizB[0])); i++)
		ShowWindow(this->edtMatrizB[i], FALSE);
}

int Matrices::getAnchoCajaMatrices() { return this->anchoCajaMatriz; }

int Matrices::getAltoCajaMatrices() { return this->altoCajaMatriz; }

void Matrices::GenerarNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		for (int i = 0; i < this->filasA * this->columnasA; i++)
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
		for (int i = 0; i < this->filasB * this->columnasB; i++)
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
		for (int i = 0; i < this->filasR * this->columnasR; i++)
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

void Matrices::CrearCeldas(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < this->filasA; i++)
		{
			for (int j = 0; j < this->columnasA; j++)
			{
				this->auxA->celda = CreateWindowEx
				(
					0,
					"EDIT",
					"",
					ES_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
					(5) + ((j) * (this->anchoCeldaA)),
					(5) + ((i) * (this->altoCeldaA)),
					this->anchoCeldaA,
					this->altoCeldaA,
					this->ventana->getHwnd(),
					NULL,
					this->ventana->gethInstance(),
					NULL
				);
				this->auxA = this->auxA->sig;
			}
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < this->filasB; i++)
		{
			for (int j = 0; j < this->columnasB; j++)
			{
				this->auxB->celda = CreateWindowEx
				(
					0,
					"EDIT",
					"",
					ES_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
					(this->ventana->getMitadAncho() + this->anchoBtnMedio / 2) + (5) + ((j) * (this->anchoCeldaB)),
					(5) + ((i) * (this->altoCeldaB)),
					this->anchoCeldaB,
					this->altoCeldaB,
					this->ventana->getHwnd(),
					NULL,
					this->ventana->gethInstance(),
					NULL
				);
				this->auxB = this->auxB->sig;
			}
		}
	}
	else if (_tipo == "R")
	{
		this->auxR = this->primeroR;
		for (int i = 0; i < this->filasR; i++)
		{
			for (int j = 0; j < this->columnasR; j++)
			{
				this->auxR->celda = CreateWindowEx
				(
					0,
					"EDIT",
					"",
					ES_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
					((this->ventana->getMitadAncho()) - (this->anchoCajaMatriz / 2)) + ((j) * (this->anchoCeldaR)),
					(this->altoCajaMatriz + 5 + 5 + this->altoBtn + this->altoBtn + 5) + (i * this->altoCeldaR),
					this->anchoCeldaR,
					this->altoCeldaR,
					this->ventana->getHwnd(),
					NULL,
					this->ventana->gethInstance(),
					NULL
				);
				this->auxR = this->auxR->sig;
			}
		}
	}
}

void Matrices::LimpiarMatriz(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < this->filasA * this->columnasA; i++)
		{
			SetWindowText(this->auxA->celda, "");
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < this->filasB * this->columnasB; i++)
		{
			SetWindowText(this->auxB->celda, "");
			this->auxB = this->auxB->sig;
		}
	}
}

void Matrices::EliminarNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		for (int i = 0; i < this->filasA * this->columnasA; i++)
		{
			this->auxA = this->primeroA;
			this->primeroA = this->primeroA->sig;
			delete this->auxA;
		}
		this->auxA = NULL;
		this->primeroA = NULL;
	}
	else if (_tipo == "B")
	{
		for (int i = 0; i < this->filasB * this->columnasB; i++)
		{
			this->auxB = this->primeroB;
			this->primeroB = this->primeroB->sig;
			delete this->auxB;
		}
		this->auxB = NULL;
		this->primeroB = NULL;
	}
	else if (_tipo == "R")
	{
		for (int i = 0; i < this->filasR * this->columnasR; i++)
		{
			this->auxR = this->primeroR;
			this->primeroR = this->primeroR->sig;
			delete this->auxR;
		}
		this->auxR = NULL;
		this->primeroR = NULL;
	}
}

void Matrices::DestruirMatriz(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < this->filasA * this->columnasA; i++)
		{
			DestroyWindow(this->auxA->celda);
			this->auxA->celda = NULL;
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < this->filasB * this->columnasB; i++)
		{
			DestroyWindow(this->auxB->celda);
			this->auxB->celda = NULL;
			this->auxB = this->auxB->sig;
		}
	}
	else if (_tipo == "R")
	{
		this->auxR = this->primeroR;
		for (int i = 0; i < this->filasR * this->columnasR; i++)
		{
			DestroyWindow(this->auxR->celda);
			this->auxR->celda = NULL;
			this->auxR = this->auxR->sig;
		}
	}
}

void Matrices::CambiarDimensiones(char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];

		int _filas;
		int _columnas;

		ZeroMemory(texto, sizeof(texto));
		GetWindowText(this->edtMatrizA[0], texto, sizeof(texto));
		_filas = atoi(texto);

		ZeroMemory(texto, sizeof(texto));
		GetWindowText(this->edtMatrizA[1], texto, sizeof(texto));
		_columnas = atoi(texto);


		if (_filas < 1 || _columnas < 1 || (_filas > 14 || _columnas > 27))
		{
			ZeroMemory(texto, sizeof(texto));
			_itoa_s(this->filasA, texto, sizeof(texto), 10);
			SetWindowText(this->edtMatrizA[0], texto);

			ZeroMemory(texto, sizeof(texto));
			_itoa_s(this->columnasA, texto, sizeof(texto), 10);
			SetWindowText(this->edtMatrizA[1], texto);

			MessageBox(this->ventana->getHwnd(), "Dimension de la matriz no valida", "Alerta", 0);
		}
		else
		{
			this->filasA = _filas;
			this->columnasA = _columnas;

			this->anchoCeldaA = (this->anchoCajaMatriz / this->columnasA);
			this->altoCeldaA = (this->altoCajaMatriz / this->filasA);

		}
	}
	else if (_tipo == "B")
	{
		char texto[MAXCHAR];

		int _filas;
		int _columnas;

		ZeroMemory(texto, sizeof(texto));
		GetWindowText(this->edtMatrizB[0], texto, sizeof(texto));
		_filas = atoi(texto);

		ZeroMemory(texto, sizeof(texto));
		GetWindowText(this->edtMatrizB[1], texto, sizeof(texto));
		_columnas = atoi(texto);

		if (_filas < 1 || _columnas < 1 || (_filas > 14 || _columnas > 27))
		{
			ZeroMemory(texto, sizeof(texto));
			_itoa_s(this->filasB, texto, sizeof(texto), 10);
			SetWindowText(this->edtMatrizB[0], texto);

			ZeroMemory(texto, sizeof(texto));
			_itoa_s(this->columnasB, texto, sizeof(texto), 10);
			SetWindowText(this->edtMatrizB[1], texto);

			MessageBox(this->ventana->getHwnd(), "Mensaje", "Dimension de la matriz no valida", 0);
		}
		else
		{
			this->filasB = _filas;
			this->columnasB = _columnas;

			this->anchoCeldaB = (this->anchoCajaMatriz / this->columnasB);
			this->altoCeldaB = (this->altoCajaMatriz / this->filasB);
		}
	}
}

void Matrices::setDimensiones(int _filas, int _columnas, char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];
		this->filasA = _filas;
		this->columnasA = _columnas;

		this->anchoCeldaA = (this->anchoCajaMatriz / this->columnasA);
		this->altoCeldaA = (this->altoCajaMatriz / this->filasA);

		ZeroMemory(texto, sizeof(texto));
		_itoa_s(this->filasA, texto, sizeof(texto), 10);
		SetWindowText(this->edtMatrizA[0], texto);

		ZeroMemory(texto, sizeof(texto));
		_itoa_s(this->columnasA, texto, sizeof(texto), 10);
		SetWindowText(this->edtMatrizA[1], texto);

	}
	else if (_tipo == "B")
	{
		char texto[MAXCHAR];
		this->filasB = _filas;
		this->columnasB = _columnas;

		this->anchoCeldaB = (this->anchoCajaMatriz / this->columnasB);
		this->altoCeldaB = (this->altoCajaMatriz / this->filasB);

		ZeroMemory(texto, sizeof(texto));
		_itoa_s(this->filasB, texto, sizeof(texto), 10);
		SetWindowText(this->edtMatrizB[0], texto);

		ZeroMemory(texto, sizeof(texto));
		_itoa_s(this->columnasB, texto, sizeof(texto), 10);
		SetWindowText(this->edtMatrizB[1], texto);
	}
	else if (_tipo == "R")
	{
		this->filasR = _filas;
		this->columnasR = _columnas;

		this->anchoCeldaR = (this->anchoCajaMatriz / this->columnasR);
		this->altoCeldaR = (this->altoCajaMatriz / this->filasR);
	}
}

void Matrices::setValoresCeldas(char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;
		for (int i = 0; i < this->filasA * this->columnasA; i++)
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
		for (int i = 0; i < this->filasB * this->columnasB; i++)
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
		for (int i = 0; i < this->filasR * this->columnasR; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			sprintf_s(texto, "%f", this->auxR->valor);
			SetWindowText(this->auxR->celda, texto);
			this->auxR = this->auxR->sig;
		}
	}
}

void Matrices::LimpiarValoresNodos(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < this->filasA * this->columnasA; i++)
		{
			this->auxA->valor = 0;
			this->auxA = this->auxA->sig;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < this->filasB * this->columnasB; i++)
		{
			this->auxB->valor = 0;
			this->auxB = this->auxB->sig;
		}
	}
}

void Matrices::Transpuesta(char* _tipo)
{
	Validacion* validacion = new Validacion();
	if (_tipo == "A")
	{
		if (!validacion->CeldasVacias(this->primeroA, this->auxA))
		{
			if (!validacion->ValidarFormato(this->primeroA, this->auxA))
			{
				char texto[MAXCHAR];
				Celda* aux = this->primeroA;

				//Transpuesta
				for (int i = 0; i < this->columnasA; i++)
				{
					this->auxA = this->primeroA;
					for (int k = 0; k < i; k++)
						this->auxA = this->auxA->sig;

					for (int j = 0; j < this->filasA - 1; j++)
					{
						ZeroMemory(texto, sizeof(texto));
						GetWindowText(this->auxA->celda, texto, sizeof(texto));
						aux->valor = atof(texto);
						aux = aux->sig;
						for (int x = 0; x < this->columnasA; x++)
							this->auxA = this->auxA->sig;
					}
					ZeroMemory(texto, sizeof(texto));
					GetWindowText(this->auxA->celda, texto, sizeof(texto));
					aux->valor = atof(texto);
					aux = aux->sig;
				}
				delete aux;

				this->DestruirMatriz((char*)"A");
				this->setDimensiones(this->columnasA, this->filasA, (char*)"A");
				this->CrearCeldas((char*)"A");
				this->setValoresCeldas((char*)"A");
				this->LimpiarValoresNodos((char*)"A");
			}
			else
				MessageBox(this->ventana->getHwnd(), "Formato incorrecto", "Mensaje", 0);
		}
		else
			MessageBox(this->ventana->getHwnd(), "Faltan de rellenar campos", "Mensaje", 0);
	}
	else if (_tipo == "B")
	{
		if (!validacion->CeldasVacias(this->primeroB, this->auxB))
		{
			if (!validacion->ValidarFormato(this->primeroB, this->auxB))
			{

				char texto[MAXCHAR];
				Celda* aux = this->primeroB;

				//Transpuesta
				for (int i = 0; i < this->columnasB; i++)
				{
					this->auxB = this->primeroB;
					for (int k = 0; k < i; k++)
						this->auxB = this->auxB->sig;

					for (int j = 0; j < this->filasB - 1; j++)
					{
						ZeroMemory(texto, sizeof(texto));
						GetWindowText(this->auxB->celda, texto, sizeof(texto));
						aux->valor = atof(texto);
						aux = aux->sig;
						for (int x = 0; x < this->columnasB; x++)
							this->auxB = this->auxB->sig;
					}
					ZeroMemory(texto, sizeof(texto));
					GetWindowText(this->auxB->celda, texto, sizeof(texto));
					aux->valor = atof(texto);
					aux = aux->sig;
				}
				delete aux;

				//Cambiar Dimensiones
				this->DestruirMatriz((char*)"B");
				this->setDimensiones(this->columnasB, this->filasB, (char*)"B");
				this->CrearCeldas((char*)"B");
				this->setValoresCeldas((char*)"B");
				this->LimpiarValoresNodos((char*)"B");
			}
			else
				MessageBox(this->ventana->getHwnd(), "Formato incorrecto", "Mensaje", 0);
		}
		else
			MessageBox(this->ventana->getHwnd(), "Faltan de rellenar campos", "Mensaje", 0);
	}
	delete validacion;
}

void Matrices::getValoresCeldas(char* _tipo)
{
	if (_tipo == "A")
	{
		char texto[MAXCHAR];
		this->auxA = this->primeroA;

		for (int i = 0; i < this->filasA * this->columnasA; i++)
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

		for (int i = 0; i < this->filasB * this->columnasB; i++)
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

		for (int i = 0; i < this->filasR * this->columnasR; i++)
		{
			ZeroMemory(texto, sizeof(texto));
			GetWindowText(this->auxR->celda, texto, sizeof(texto));
			this->auxR->valor = atof(texto);
			this->auxR = this->auxR->sig;
		}
	}
}

void Matrices::DeshabilitarBotones()
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

	//Edt matriz A
	for (int i = 0; i < (sizeof(this->edtMatrizA) / sizeof(this->edtMatrizA[0])); i++)
		EnableWindow(this->edtMatrizA[i], FALSE);

	//Edt matriz B
	for (int i = 0; i < (sizeof(this->edtMatrizB) / sizeof(this->edtMatrizB[0])); i++)
		EnableWindow(this->edtMatrizB[i], FALSE);
}

void Matrices::HabilitarBotones()
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

	//Edt matriz A
	for (int i = 0; i < (sizeof(this->edtMatrizA) / sizeof(this->edtMatrizA[0])); i++)
		EnableWindow(this->edtMatrizA[i], TRUE);

	//Edt matriz B
	for (int i = 0; i < (sizeof(this->edtMatrizB) / sizeof(this->edtMatrizB[0])); i++)
		EnableWindow(this->edtMatrizB[i], TRUE);
}

void Matrices::Intercambiar()
{
	Validacion* validacion = new Validacion();
	if (!validacion->CeldasVacias(this->primeroA, this->auxA) || !validacion->CeldasVacias(this->primeroB, this->auxB))
	{

		int _filasB = this->filasA;
		int _columnasB = this->columnasA;
		Celda* primeroC = NULL;
		Celda* auxC = NULL;

		this->getValoresCeldas((char*)"A");
		this->getValoresCeldas((char*)"B");

		this->auxA = this->primeroA;

		//Generar Celdas y copiar valores de A
		for (int i = 0; i < this->filasA * this->columnasA; i++)
		{
			if (primeroC == NULL)
			{
				primeroC = new Celda;
				auxC = primeroC;
				auxC->valor = this->auxA->valor;
			}
			else
			{
				auxC->sig = new Celda;
				auxC = auxC->sig;
				auxC->valor = this->auxA->valor;
			}

			this->auxA = this->auxA->sig;
		}

		this->LimpiarValoresNodos((char*)"A");
		this->DestruirMatriz((char*)"A");
		this->EliminarNodos((char*)"A");
		this->setDimensiones(this->filasB, this->columnasB, (char*)"A");
		this->GenerarNodos((char*)"A");
		this->CrearCeldas((char*)"A");

		//Obtener valores de B
		this->auxA = this->primeroA;
		this->auxB = this->primeroB;
		for (int i = 0; i < this->filasA * this->columnasA; i++)
		{
			this->auxA->valor = this->auxB->valor;
			this->auxA = this->auxA->sig;
			this->auxB = this->auxB->sig;
		}

		this->setValoresCeldas((char*)"A");
		this->LimpiarValoresNodos((char*)"A");

		//Matriz B
		this->LimpiarValoresNodos((char*)"B");
		this->DestruirMatriz((char*)"B");
		this->EliminarNodos((char*)"B");
		this->setDimensiones(_filasB, _columnasB, (char*)"B");
		this->GenerarNodos((char*)"B");
		this->CrearCeldas((char*)"B");

		//Obtener valores de B
		this->auxB = this->primeroB;
		auxC = primeroC;
		for (int i = 0; i < this->filasB * this->columnasB; i++)
		{
			this->auxB->valor = auxC->valor;
			auxC = auxC->sig;
			this->auxB = this->auxB->sig;
		}

		this->setValoresCeldas((char*)"B");
		this->LimpiarValoresNodos((char*)"B");

		//Eliminar C
		auxC = primeroC;
		while (auxC != NULL)
		{
			primeroC = primeroC->sig;
			delete auxC;
			auxC = primeroC;
		}
	}
	else
		MessageBox(this->ventana->getHwnd(), "Faltan de rellenar campos", "Mensaje", 0);

	delete validacion;
}

void Matrices::MostrarBotonesResultado()
{
	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnResultado) / sizeof(this->btnResultado[0])); i++)
		ShowWindow(this->btnResultado[i], TRUE);
}

void Matrices::OcultarBotonesResultado()
{
	//Botones Medio
	for (int i = 0; i < (sizeof(this->btnResultado) / sizeof(this->btnResultado[0])); i++)
		ShowWindow(this->btnResultado[i], FALSE);
}

void Matrices::LimpiarResultado()
{
	this->DestruirMatriz((char*)"R");
	this->EliminarNodos((char*)"R");

	this->OcultarBotonesResultado();
	this->HabilitarBotones();
}

void Matrices::MandarResultado(char* _tipo)
{
	if (_tipo == "A")
	{
		this->DestruirMatriz((char*)"A");
		this->EliminarNodos((char*)"A");
		this->setDimensiones(this->filasR, this->columnasR, (char*)"A");
		this->GenerarNodos((char*)"A");
		this->CrearCeldas((char*)"A");

		this->auxA = this->primeroA;
		this->auxR = this->primeroR;
		for (int i = 0; i < this->filasA * this->columnasA; i++)
		{
			this->auxA->valor = this->auxR->valor;
			this->auxA = this->auxA->sig;
			this->auxR = this->auxR->sig;
		}

		this->setValoresCeldas((char*)"A");
		this->LimpiarValoresNodos((char*)"A");
	}
	else if (_tipo == "B")
	{
		this->DestruirMatriz((char*)"B");
		this->EliminarNodos((char*)"B");
		this->setDimensiones(this->filasR, this->columnasR, (char*)"B");
		this->GenerarNodos((char*)"B");
		this->CrearCeldas((char*)"B");

		this->auxB = this->primeroB;
		this->auxR = this->primeroR;
		for (int i = 0; i < this->filasB * this->columnasB; i++)
		{
			this->auxB->valor = this->auxR->valor;
			this->auxB = this->auxB->sig;
			this->auxR = this->auxR->sig;
		}

		this->setValoresCeldas((char*)"B");
		this->LimpiarValoresNodos((char*)"B");
	}
}

void Matrices::Sumar()
{
	Validacion* validacion = new Validacion();
	if (!validacion->CeldasVacias(this->primeroA, this->auxA) && !validacion->CeldasVacias(this->primeroB, this->auxB))
	{
		if (!validacion->ValidarFormato(this->primeroA, this->auxA) && !validacion->ValidarFormato(this->primeroB, this->auxB))
		{
			if (this->filasA == this->filasB && this->columnasA == this->columnasB)
			{
				this->getValoresCeldas((char*)"A");
				this->getValoresCeldas((char*)"B");

				this->setDimensiones(this->filasA, this->columnasA, (char*)"R");
				this->GenerarNodos((char*)"R");

				//Sumar
				this->auxA = this->primeroA;
				this->auxB = this->primeroB;
				this->auxR = this->primeroR;
				for (int i = 0; i < this->filasA * this->columnasA; i++)
				{
					this->auxR->valor = this->auxA->valor + this->auxB->valor;

					this->auxA = this->auxA->sig;
					this->auxB = this->auxB->sig;
					this->auxR = this->auxR->sig;
				}

				this->LimpiarValoresNodos((char*)"A");
				this->LimpiarValoresNodos((char*)"B");

				this->CrearCeldas((char*)"R");
				this->MostrarBotonesResultado();
				this->setValoresCeldas((char*)"R");

				this->DeshabilitarBotones();

			}
			else
				MessageBox(ventana->getHwnd(), "Las matrices no son del mismo tamaño", "Mensaje", 0);
		}
		else
			MessageBox(ventana->getHwnd(), "Formato incorrecto", "Mensaje", 0);
	}
	else
		MessageBox(this->ventana->getHwnd(), "Faltan de rellenar campos", "Mensaje", 0);

	delete validacion;
}

void Matrices::Restar()
{
	Validacion* validacion = new Validacion();
	if (!validacion->CeldasVacias(this->primeroA, this->auxA) && !validacion->CeldasVacias(this->primeroB, this->auxB))
	{
		if (!validacion->ValidarFormato(this->primeroA, this->auxA) && !validacion->ValidarFormato(this->primeroB, this->auxB))
		{
			if (this->filasA == this->filasB && this->columnasA == this->columnasB)
			{
				this->getValoresCeldas((char*)"A");
				this->getValoresCeldas((char*)"B");

				this->setDimensiones(this->filasA, this->columnasA, (char*)"R");
				this->GenerarNodos((char*)"R");

				//Restar
				this->auxA = this->primeroA;
				this->auxB = this->primeroB;
				this->auxR = this->primeroR;
				for (int i = 0; i < this->filasA * this->columnasA; i++)
				{
					this->auxR->valor = this->auxA->valor - this->auxB->valor;

					this->auxA = this->auxA->sig;
					this->auxB = this->auxB->sig;
					this->auxR = this->auxR->sig;
				}

				this->LimpiarValoresNodos((char*)"A");
				this->LimpiarValoresNodos((char*)"B");

				this->CrearCeldas((char*)"R");
				this->MostrarBotonesResultado();
				this->setValoresCeldas((char*)"R");

				this->DeshabilitarBotones();

			}
			else
				MessageBox(ventana->getHwnd(), "Las matrices no son del mismo tamaño", "Mensaje", 0);
		}
		else
			MessageBox(ventana->getHwnd(), "Formato incorrecto", "Mensaje", 0);
	}
	else
		MessageBox(this->ventana->getHwnd(), "Faltan de relleanr campos", "Mensaje", 0);

	delete validacion;

}

void Matrices::Multiplicar()
{
	Validacion* validacion = new Validacion();
	if (!validacion->CeldasVacias(this->primeroA, this->auxA) && !validacion->CeldasVacias(this->primeroB, this->auxB))
	{
		if (!validacion->ValidarFormato(this->primeroA, this->auxA) && !validacion->ValidarFormato(this->primeroB, this->auxB))
		{
			if (this->columnasA == 1 && this->filasA == 1 && this->filasB >= 1 && this->columnasB >= 1)
			{
				this->getValoresCeldas((char*)"A");
				this->getValoresCeldas((char*)"B");

				this->setDimensiones(this->filasB, this->columnasB, (char*)"R");
				this->GenerarNodos((char*)"R");

				//Multiplicar
				this->auxA = this->primeroA;
				this->auxB = this->primeroB;
				this->auxR = this->primeroR;
				for (int i = 0; i < this->filasB * this->columnasB; i++)
				{
					this->auxR->valor = this->auxA->valor * this->auxB->valor;
					this->auxB = this->auxB->sig;
					this->auxR = this->auxR->sig;
				}

				this->LimpiarValoresNodos((char*)"A");
				this->LimpiarValoresNodos((char*)"B");

				this->CrearCeldas((char*)"R");
				this->MostrarBotonesResultado();
				this->setValoresCeldas((char*)"R");

				this->DeshabilitarBotones();

			}
			else if (this->columnasB == 1 && this->filasB == 1 && this->filasA >= 1 && this->columnasA >= 1)
			{
				this->getValoresCeldas((char*)"A");
				this->getValoresCeldas((char*)"B");

				this->setDimensiones(this->filasA, this->columnasA, (char*)"R");
				this->GenerarNodos((char*)"R");

				//Multiplicar
				this->auxA = this->primeroA;
				this->auxB = this->primeroB;
				this->auxR = this->primeroR;
				for (int i = 0; i < this->filasA * this->columnasA; i++)
				{
					this->auxR->valor = this->auxA->valor * this->auxB->valor;
					this->auxA = this->auxA->sig;
					this->auxR = this->auxR->sig;
				}

				this->LimpiarValoresNodos((char*)"A");
				this->LimpiarValoresNodos((char*)"B");

				this->CrearCeldas((char*)"R");
				this->MostrarBotonesResultado();
				this->setValoresCeldas((char*)"R");

				this->DeshabilitarBotones();

			}
			else if (this->columnasA == this->filasB)
			{
				this->getValoresCeldas((char*)"A");
				this->getValoresCeldas((char*)"B");

				this->setDimensiones(this->filasA, this->columnasB, (char*)"R");
				this->GenerarNodos((char*)"R");

				//Multiplicar
				this->auxA = this->primeroA;
				this->auxB = this->primeroB;
				this->auxR = this->primeroR;
				Celda* _auxA = this->primeroA;
				Celda* _auxB = this->primeroB;
				for (int i = 0; i < this->filasA; i++)
				{
					for (int x = 0; x < this->columnasB; x++)
					{
						this->auxA = _auxA;
						for (int j = 0; j < this->columnasA; j++)
						{
							this->auxR->valor = this->auxR->valor + this->auxA->valor * this->auxB->valor;
							for (int h = 0; h < this->columnasB; h++)
							{
								this->auxB->sig != NULL ? this->auxB = this->auxB->sig : NULL;
							}

							this->auxA = this->auxA->sig;
						}
						this->auxR = this->auxR->sig;
						_auxB = _auxB->sig;
						this->auxB = _auxB;
					}

					for (int t = 0; t < this->columnasA; t++)
						_auxA->sig != NULL ? _auxA = _auxA->sig : NULL;
					_auxB = this->primeroB;
					this->auxB = this->primeroB;
				}

				this->LimpiarValoresNodos((char*)"A");
				this->LimpiarValoresNodos((char*)"B");

				this->CrearCeldas((char*)"R");
				this->MostrarBotonesResultado();
				this->setValoresCeldas((char*)"R");

				this->DeshabilitarBotones();
			}
			else
			{
				MessageBox(ventana->getHwnd(), "Las matrices no son validas", "Mensaje", 0);
			}
		}
		else
			MessageBox(ventana->getHwnd(), "Formato incorrecto", "Mensaje", 0);
	}
	else
		MessageBox(this->ventana->getHwnd(), "Faltan de rellenar campos", "Mensaje", 0);

	delete validacion;
}

void CorregirEspaciosEnBlanco(Celda* auxPtr, Celda* ptr)
{
	auxPtr = ptr;

	char texto[MAXCHAR] = { "" };
	int largo = 0;

	for (int x = 0; x < 4; x++)
	{
		GetWindowText(auxPtr->celda, texto, sizeof(texto));
		largo = strlen(texto);
		if (largo > 0)
		{
			for (int i = 0; i < largo; i++)
			{
				if (texto[i] == 32)
				{
					for (int j = i; j < largo; j++)
					{
						j + 1 == largo ? texto[j] = NULL : texto[j] = texto[j + 1];
					}
					largo > 1 ? i-- : NULL;
				}
			}
		}
		SetWindowText(auxPtr->celda, texto);
		ZeroMemory(texto, sizeof(texto));
		auxPtr->sig != NULL ? auxPtr = auxPtr->sig : NULL;
	}
}
