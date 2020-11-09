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

void Cuaterniones::DeshabilitarBotones()
{
	for (int i = 0; i < 6; i++)
		EnableWindow(this->btnMedio[i], FALSE);

	for (int i = 0; i < 7; i++)
		EnableWindow(this->btnCuaternionA[i], FALSE);

	for (int i = 0; i < 7; i++)
		EnableWindow(this->btnCuaternionB[i], FALSE);
}

void Cuaterniones::HabilitarBotones()
{
	for (int i = 0; i < 6; i++)
		EnableWindow(this->btnMedio[i], TRUE);

	for (int i = 0; i < 7; i++)
		EnableWindow(this->btnCuaternionA[i], TRUE);

	for (int i = 0; i < 7; i++)
		EnableWindow(this->btnCuaternionB[i], TRUE);
}

void Cuaterniones::DestruirCuaternio(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			this->primeroA = this->primeroA->sig;
			delete this->auxA;
			this->auxA = this->primeroA;
		}
	}
	else if (_tipo == "B")
	{
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{

			this->primeroB = this->primeroB->sig;
			delete this->auxB;
			this->auxB = this->primeroB;
		}
	}
}

void Cuaterniones::LimpiarResultado()
{
	EnableWindow(this->btnResultado[1], TRUE);
	EnableWindow(this->btnResultado[2], TRUE);
	this->DestruirVentanas((char*)"R");
	this->EliminarResultado();
	this->HabilitarBotones();
	this->OcultarBotonesResultado();
}

void Cuaterniones::CrearNodosResultado(char* _tipo)
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
	}
	else if (_tipo == "unitario")
	{
		this->primeroR = new Celda;

	}
}

void Cuaterniones::CrearVentanasResultado(char* _tipo)
{
	if (_tipo == "cuaternio")
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
				this->ventana->getMitadAncho() - (this->anchoCajaMatriz / 2) + ((i) * (this->anchoCajaMatriz / 4)),
				5 + 40 + 5 + (3 * this->altoBtn) + 20,
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
	else if (_tipo == "unitario")
	{
		this->auxR = this->primeroR;

		this->auxR->celda = CreateWindowEx
		(
			0,
			"EDIT",
			"",
			ES_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			this->ventana->getMitadAncho() - (this->anchoCajaMatriz / 2),
			5 + this->altoCajaMatriz + 5 + (3 * this->altoBtn) + 20,
			this->anchoCajaMatriz,
			this->altoCajaMatriz,
			this->ventana->getHwnd(),
			NULL,
			this->ventana->gethInstance(),
			NULL
		);
	}
}

void Cuaterniones::EliminarResultado()
{
	this->auxR = this->primeroR;

	while (this->auxR->sig != NULL)
	{
		this->primeroR = this->primeroR->sig;
		delete this->auxR;
		this->auxR = this->primeroR;
	}
	delete this->auxR;
	this->primeroR = NULL;
	this->auxR = NULL;
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
		while (this->auxR->sig != NULL)
		{
			DestroyWindow(this->auxR->celda);
			this->auxR = this->auxR->sig;
		}
		DestroyWindow(this->auxR->celda);
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
			((this->ventana->getMitadAncho()) + (this->anchoCajaMatriz / 2) + 5),
			5 + 40 + 5 + (3 * this->altoBtn) + 20 + (i * this->altoBtn),
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
	Validacion* validacion = new Validacion();
	if (_tipo == "A")
	{
		if (!validacion->CeldasVacias(this->primeroA, this->auxA))
		{
			if (!validacion->ValidarFormato(this->primeroA, this->auxA))
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
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}
	else if (_tipo == "B")
	{
		if (!validacion->CeldasVacias(this->primeroB, this->auxB))
		{
			if (!validacion->ValidarFormato(this->primeroB, this->auxB))
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
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}

	delete validacion;
}

void Cuaterniones::Opuesto(char* _tipo)
{
	Validacion* validacion = new Validacion();
	if (_tipo == "A")
	{
		if (!validacion->CeldasVacias(this->primeroA, this->auxA))
		{
			if (!validacion->ValidarFormato(this->primeroA, this->auxA))
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
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}
	else if (_tipo == "B")
	{
		if (!validacion->CeldasVacias(this->primeroB, this->auxB))
		{
			if (!validacion->ValidarFormato(this->primeroB, this->auxB))
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
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}

	delete validacion;
}

void Cuaterniones::ValorAbsoluto(char* _tipo)
{
	Validacion* validacion = new Validacion();
	if (_tipo == "A")
	{
		if (!validacion->CeldasVacias(this->primeroA, this->auxA))
		{
			if (!validacion->ValidarFormato(this->primeroA, this->auxA))
			{
				this->getValoresCuaternio((char*)"A");

				//Valor absoluto
				this->auxA = this->primeroA;
				double valorAbsoluto = 0;
				for (int i = 0; i < 4; i++)
				{
					valorAbsoluto = valorAbsoluto + pow(this->auxA->valor, 2);
					this->auxA = this->auxA->sig;
				}

				//Raiz cuadrada
				valorAbsoluto = sqrt(valorAbsoluto);

				this->LimpiarValoresNodos((char*)"A");

				//Crear celda resultado
				this->CrearNodosResultado((char*)"unitario");
				this->CrearVentanasResultado((char*)"unitario");


				//Enviar valor a la celda
				this->auxR = this->primeroR;

				char texto[MAXCHAR];
				ZeroMemory(texto, sizeof(texto));

				sprintf_s(texto, "%f", valorAbsoluto);
				SetWindowText(this->auxR->celda, texto);

				this->MostrarBotonesResultado();
				EnableWindow(this->btnResultado[1], FALSE);
				EnableWindow(this->btnResultado[2], FALSE);

				this->DeshabilitarBotones();
			}
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}
	else if (_tipo == "B")
	{
		if (!validacion->CeldasVacias(this->primeroB, this->auxB))
		{
			if (!validacion->ValidarFormato(this->primeroB, this->auxB))
			{
				this->getValoresCuaternio((char*)"B");

				//Valor absoluto
				this->auxB = this->primeroB;
				double valorAbsoluto = 0;
				for (int i = 0; i < 4; i++)
				{
					valorAbsoluto = valorAbsoluto + pow(this->auxB->valor, 2);
					this->auxB = this->auxB->sig;
				}

				//Raiz cuadrada
				valorAbsoluto = sqrt(valorAbsoluto);

				this->LimpiarValoresNodos((char*)"B");

				//Crear celda resultado
				this->CrearNodosResultado((char*)"unitario");
				this->CrearVentanasResultado((char*)"unitario");



				//Enviar valor a la celda
				this->auxR = this->primeroR;

				char texto[MAXCHAR];
				ZeroMemory(texto, sizeof(texto));

				sprintf_s(texto, "%f", valorAbsoluto);
				SetWindowText(this->auxR->celda, texto);

				this->MostrarBotonesResultado();
				EnableWindow(this->btnResultado[1], FALSE);
				EnableWindow(this->btnResultado[2], FALSE);

				this->DeshabilitarBotones();
			}
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}

	delete validacion;
}

void Cuaterniones::Normalizacion(char* _tipo)
{
	Validacion* validacion = new Validacion();
	if (_tipo == "A")
	{
		if (!validacion->CeldasVacias(this->primeroA, this->auxA))
		{
			if (!validacion->ValidarFormato(this->primeroA, this->auxA))
			{
				this->getValoresCuaternio((char*)"A");

				//Valor absoluto
				this->auxA = this->primeroA;
				double valorAbsoluto = 0;
				for (int i = 0; i < 4; i++)
				{
					valorAbsoluto = valorAbsoluto + pow(this->auxA->valor, 2);
					this->auxA = this->auxA->sig;
				}

				//Raiz cuadrada
				valorAbsoluto = sqrt(valorAbsoluto);

				this->CrearNodosResultado((char*)"cuaternio");
				this->CrearVentanasResultado((char*)"cuaternio");

				//Normalizar
				this->auxA = this->primeroA;
				this->auxR = this->primeroR;
				for (int i = 0; i < 4; i++)
				{
					this->auxR->valor = this->auxA->valor / valorAbsoluto;
					this->auxR = this->auxR->sig;
					this->auxA = this->auxA->sig;
				}

				this->setValoresCuaternio((char*)"R");

				this->LimpiarValoresNodos((char*)"A");

				this->MostrarBotonesResultado();

				this->DeshabilitarBotones();
			}
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}
	else if (_tipo == "B")
	{
		if (!validacion->CeldasVacias(this->primeroB, this->auxB))
		{
			if (!validacion->ValidarFormato(this->primeroB, this->auxB))
			{
				this->getValoresCuaternio((char*)"B");

				//Valor absoluto
				this->auxB = this->primeroB;
				double valorAbsoluto = 0;
				for (int i = 0; i < 4; i++)
				{
					valorAbsoluto = valorAbsoluto + pow(this->auxB->valor, 2);
					this->auxB = this->auxB->sig;
				}

				//Raiz cuadrada
				valorAbsoluto = sqrt(valorAbsoluto);

				this->CrearNodosResultado((char*)"cuaternio");
				this->CrearVentanasResultado((char*)"cuaternio");

				//Normalizar
				this->auxB = this->primeroB;
				this->auxR = this->primeroR;
				for (int i = 0; i < 4; i++)
				{
					this->auxR->valor = this->auxB->valor / valorAbsoluto;
					this->auxR = this->auxR->sig;
					this->auxB = this->auxB->sig;
				}

				this->setValoresCuaternio((char*)"R");

				this->LimpiarValoresNodos((char*)"B");

				this->MostrarBotonesResultado();

				this->DeshabilitarBotones();
			}
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}
	delete validacion;
}

void Cuaterniones::Inverso(char* _tipo)
{
	Validacion* validacion = new Validacion;
	if (_tipo == "A")
	{
		if (!validacion->CeldasVacias(this->primeroA, this->auxA))
		{
			if (!validacion->ValidarFormato(this->primeroA, this->auxA))
			{
				this->getValoresCuaternio((char*)"A");

				//Valor absoluto
				this->auxA = this->primeroA;
				double valorAbsoluto = 0;
				for (int i = 0; i < 4; i++)
				{
					valorAbsoluto = valorAbsoluto + pow(this->auxA->valor, 2);
					this->auxA = this->auxA->sig;
				}

				//Raiz cuadrada
				valorAbsoluto = sqrt(valorAbsoluto);
				valorAbsoluto = pow(valorAbsoluto, 2);

				this->CrearNodosResultado((char*)"cuaternio");
				this->CrearVentanasResultado((char*)"cuaternio");

				//Normalizar
				this->auxA = this->primeroA;
				this->auxR = this->primeroR;
				for (int i = 0; i < 4; i++)
				{
					this->auxR->valor = this->auxA->valor / valorAbsoluto;
					this->auxR = this->auxR->sig;
					this->auxA = this->auxA->sig;
				}

				this->setValoresCuaternio((char*)"R");

				this->LimpiarValoresNodos((char*)"A");

				this->MostrarBotonesResultado();

				this->DeshabilitarBotones();
			}
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}
	else if (_tipo == "B")
	{
		if (!validacion->CeldasVacias(this->primeroB, this->auxB))
		{
			if (!validacion->ValidarFormato(this->primeroB, this->auxB))
			{
				this->getValoresCuaternio((char*)"B");

				//Valor absoluto
				this->auxB = this->primeroB;
				double valorAbsoluto = 0;
				for (int i = 0; i < 4; i++)
				{
					valorAbsoluto = valorAbsoluto + pow(this->auxB->valor, 2);
					this->auxB = this->auxB->sig;
				}

				//Raiz cuadrada
				valorAbsoluto = sqrt(valorAbsoluto);
				valorAbsoluto = pow(valorAbsoluto, 2);

				this->CrearNodosResultado((char*)"cuaternio");
				this->CrearVentanasResultado((char*)"cuaternio");

				//Normalizar
				this->auxB = this->primeroB;
				this->auxR = this->primeroR;
				for (int i = 0; i < 4; i++)
				{
					this->auxR->valor = this->auxB->valor / valorAbsoluto;
					this->auxR = this->auxR->sig;
					this->auxB = this->auxB->sig;
				}

				this->setValoresCuaternio((char*)"R");

				this->LimpiarValoresNodos((char*)"B");

				this->MostrarBotonesResultado();

				this->DeshabilitarBotones();
			}
			else
				MessageBox(0, "Formato erroneo", "Mensaje", 0);
		}
		else
			MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);
	}

	delete validacion;
}

void Cuaterniones::Multiplicar()
{
	Validacion* validacion = new Validacion();
	if (!validacion->CeldasVacias(this->primeroA, this->auxA) && !validacion->CeldasVacias(this->primeroB, this->auxB))
	{
		if (!validacion->ValidarFormato(this->primeroA, this->auxA) && !validacion->ValidarFormato(this->primeroB, this->auxB))
		{
			this->getValoresCuaternio((char*)"A");
			this->getValoresCuaternio((char*)"B");

			this->CrearNodosResultado((char*)"cuaternio");

			//Multiplicar
			this->auxA = this->primeroA;
			this->auxB = this->primeroB;
			this->auxR = this->primeroR;
			for (int i = 0; i < 4; i++)
			{

				i == 0 ? this->auxR->valor = this->auxA->valor * this->auxB->valor : this->auxR->valor = (this->auxR->valor) - (this->auxA->valor * this->auxB->valor);

				this->auxA = this->auxA->sig;
				this->auxB = this->auxB->sig;
			}

			//i
			this->auxR = this->auxR->sig;
			this->auxA = this->primeroA;
			this->auxB = this->primeroB->sig;

			this->auxR->valor = this->auxA->valor * this->auxB->valor;

			this->auxA = this->auxA->sig;
			this->auxB = this->primeroB;

			this->auxR->valor = (this->auxR->valor) + (this->auxA->valor * this->auxB->valor);

			this->auxA = this->auxA->sig;
			this->auxB = this->primeroB->sig->sig->sig;

			this->auxR->valor = (this->auxR->valor) + (this->auxA->valor * this->auxB->valor);

			this->auxA = this->auxA->sig;
			this->auxB = this->primeroB->sig->sig;

			this->auxR->valor = (this->auxR->valor) - (this->auxA->valor * this->auxB->valor);

			//j
			this->auxR = this->auxR->sig;
			this->auxB = this->primeroB;
			this->auxA = this->primeroA->sig->sig;

			this->auxR->valor = this->auxA->valor * this->auxB->valor;

			this->auxA = this->primeroA;
			this->auxB = this->primeroB->sig->sig;

			this->auxR->valor = (this->auxR->valor) + (this->auxA->valor * this->auxB->valor);

			this->auxB = this->primeroB->sig;
			this->auxA = this->primeroA->sig->sig->sig;

			this->auxR->valor = (this->auxR->valor) + (this->auxA->valor * this->auxB->valor);

			this->auxB = this->primeroB->sig->sig->sig;
			this->auxA = this->primeroA->sig;

			this->auxR->valor = (this->auxR->valor) - (this->auxA->valor * this->auxB->valor);

			//K
			this->auxR = this->auxR->sig;
			this->auxB = this->primeroB;
			this->auxA = this->primeroA->sig->sig->sig;

			this->auxR->valor = this->auxA->valor * this->auxB->valor;

			this->auxA = this->primeroA;
			this->auxB = this->primeroB->sig->sig->sig;

			this->auxR->valor = (this->auxR->valor) + (this->auxA->valor * this->auxB->valor);

			this->auxA = this->primeroA->sig->sig;
			this->auxB = this->primeroB->sig;

			this->auxR->valor = (this->auxR->valor) - (this->auxA->valor * this->auxB->valor);

			this->auxB = this->primeroB->sig->sig;
			this->auxA = this->primeroA->sig;

			this->auxR->valor = (this->auxR->valor) + (this->auxA->valor * this->auxB->valor);

			this->CrearVentanasResultado((char*)"cuaternio");

			this->setValoresCuaternio((char*)"R");

			this->LimpiarValoresNodos((char*)"A");
			this->LimpiarValoresNodos((char*)"B");

			this->MostrarBotonesResultado();

			this->DeshabilitarBotones();

		}
		else
			MessageBox(0, "Formato erroneo", "Mensaje", 0);
	}
	else
		MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);

	delete validacion;
}

void Cuaterniones::Restar()
{
	Validacion* validacion = new Validacion();
	if (!validacion->CeldasVacias(this->primeroA, this->auxA) && !validacion->CeldasVacias(this->primeroB, this->auxB))
	{
		if (!validacion->ValidarFormato(this->primeroA, this->auxA) && !validacion->ValidarFormato(this->primeroB, this->auxB))
		{
			this->getValoresCuaternio((char*)"A");
			this->getValoresCuaternio((char*)"B");

			this->CrearNodosResultado((char*)"cuaternio");

			this->auxA = this->primeroA;
			this->auxB = this->primeroB;
			this->auxR = this->primeroR;

			for (int i = 0; i < 4; i++)
			{
				this->auxR->valor = this->auxA->valor - this->auxB->valor;

				this->auxA = this->auxA->sig;
				this->auxB = this->auxB->sig;
				this->auxR = this->auxR->sig;
			}

			this->CrearVentanasResultado((char*)"cuaternio");

			this->setValoresCuaternio((char*)"R");

			this->LimpiarValoresNodos((char*)"A");
			this->LimpiarValoresNodos((char*)"B");

			this->MostrarBotonesResultado();

			this->DeshabilitarBotones();
		}
		else
			MessageBox(0, "Formato erroneo", "Mensaje", 0);
	}
	else
		MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);

	delete validacion;
}

void Cuaterniones::Sumar()
{
	Validacion* validacion = new Validacion();

	if (!validacion->CeldasVacias(this->primeroA, this->auxA) && !validacion->CeldasVacias(this->primeroB, this->auxB))
	{
		if (!validacion->ValidarFormato(this->primeroA, this->auxA) && !validacion->ValidarFormato(this->primeroB, this->auxB))
		{
			this->getValoresCuaternio((char*)"A");
			this->getValoresCuaternio((char*)"B");

			this->CrearNodosResultado((char*)"cuaternio");

			this->auxA = this->primeroA;
			this->auxB = this->primeroB;
			this->auxR = this->primeroR;

			for (int i = 0; i < 4; i++)
			{
				this->auxR->valor = this->auxA->valor + this->auxB->valor;

				this->auxA = this->auxA->sig;
				this->auxB = this->auxB->sig;
				this->auxR = this->auxR->sig;
			}

			this->CrearVentanasResultado((char*)"cuaternio");

			this->setValoresCuaternio((char*)"R");

			this->LimpiarValoresNodos((char*)"A");
			this->LimpiarValoresNodos((char*)"B");

			this->MostrarBotonesResultado();

			this->DeshabilitarBotones();
		}
		else
			MessageBox(0, "Formato erroneo", "Mensaje", 0);
	}
	else
		MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);

	delete validacion;
}

void Cuaterniones::Intercambiar()
{
	Validacion* validacion = new Validacion();

	if (!validacion->CeldasVacias(this->primeroA, this->auxA) || !validacion->CeldasVacias(this->primeroB, this->auxB))
	{
		Celda* primeroC = NULL;
		Celda* auxC = NULL;

		this->getValoresCuaternio((char*)"A");
		this->getValoresCuaternio((char*)"B");

		this->auxA = this->primeroA;

		//Generar Celdas y copiar valores de A
		for (int i = 0; i < 4; i++)
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
		this->LimpiarCuaternio((char*)"A");

		//Obtener valores de B
		this->auxA = this->primeroA;
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			this->auxA->valor = this->auxB->valor;
			this->auxA = this->auxA->sig;
			this->auxB = this->auxB->sig;
		}

		this->setValoresCuaternio((char*)"A");
		this->LimpiarValoresNodos((char*)"A");

		//Matriz B
		this->LimpiarValoresNodos((char*)"B");
		this->LimpiarCuaternio((char*)"B");

		//Obtener valores de B
		this->auxB = this->primeroB;
		auxC = primeroC;
		for (int i = 0; i < 4; i++)
		{
			this->auxB->valor = auxC->valor;
			auxC = auxC->sig;
			this->auxB = this->auxB->sig;
		}

		this->setValoresCuaternio((char*)"B");
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
		MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);

	delete validacion;

}

void Cuaterniones::Mandar(char* _tipo)
{
	if (_tipo == "A")
	{
		//Pasar valores a A
		this->auxR = this->primeroR;
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			this->auxA->valor = this->auxR->valor;

			this->auxA = this->auxA->sig;
			this->auxR = this->auxR->sig;
		}

		this->setValoresCuaternio((char*)"A");

		this->LimpiarValoresNodos((char*)"A");

	}
	else if (_tipo == "B")
	{
		//Pasar valores a A
		this->auxR = this->primeroR;
		this->auxB = this->primeroB;
		for (int i = 0; i < 4; i++)
		{
			this->auxB->valor = this->auxR->valor;

			this->auxB = this->auxB->sig;
			this->auxR = this->auxR->sig;
		}

		this->setValoresCuaternio((char*)"B");

		this->LimpiarValoresNodos((char*)"B");

	}
}

void Cuaterniones::Grassman()
{
	Validacion* validacion = new Validacion();
	if (!validacion->CeldasVacias(this->primeroA, this->auxA) && !validacion->CeldasVacias(this->primeroB, this->auxB))
	{
		if (!validacion->ValidarFormato(this->primeroA, this->auxA) && !validacion->ValidarFormato(this->primeroB, this->auxB))
		{
			this->getValoresCuaternio((char*)"A");
			this->getValoresCuaternio((char*)"B");

			//Grassman

			this->auxA = this->primeroA;
			this->auxB = this->primeroB;
			double independiente[5] = { NULL };
			double I[4] = { NULL };
			double J[4] = { NULL };
			double k[4] = { NULL };

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i == 0 && j == 0)
						independiente[0] = this->auxA->valor * this->auxB->valor;
					else if ((i == 1 && j == 1) || (i == 2 && j == 2) || (i == 3 && j == 3))
						independiente[i] = (this->auxA->valor * this->auxB->valor) * (-1);
					else if ((i == 0 && j == 1) || (i == 1 && j == 0) || (i == 2 && j == 3))
						I[i] = this->auxA->valor * this->auxB->valor;
					else if (i == 3 && j == 2)
						I[i] = (this->auxA->valor * this->auxB->valor) * (-1);
					else if ((i == 0 && j == 2) || (i == 2 && j == 0) || (i == 3 && j == 1))
						J[i] = this->auxA->valor * this->auxB->valor;
					else if (i == 1 && j == 3)
						J[i] = (this->auxA->valor * this->auxB->valor) * (-1);
					else if ((i == 0 && j == 3) || (i == 1 && j == 2) || (i == 3 && j == 0))
						k[i] = this->auxA->valor * this->auxB->valor;
					else if (i == 2 && j == 1)
						k[i] = (this->auxA->valor * this->auxB->valor) * (-1);

					this->auxB = this->auxB->sig;
				}
				this->auxA = this->auxA->sig;
				this->auxB = this->primeroB;
			}

			this->CrearNodosResultado((char*)"cuaternio");

			//Operar valores
			this->auxR = this->primeroR;

			this->auxR->valor = independiente[0] + independiente[1] + independiente[2] + independiente[3];
			this->auxR->sig->valor = I[0] + I[1] + I[2] + I[3];
			this->auxR->sig->sig->valor = J[0] + J[1] + J[2] + J[3];
			this->auxR->sig->sig->sig->valor = k[0] + k[1] + k[2] + k[3];

			this->CrearVentanasResultado((char*)"cuaternio");

			this->setValoresCuaternio((char*)"R");

			this->LimpiarValoresNodos((char*)"A");
			this->LimpiarValoresNodos((char*)"B");

			this->MostrarBotonesResultado();

			this->DeshabilitarBotones();

		}
		else
			MessageBox(0, "Formato erroneo", "Mensaje", 0);
	}
	else
		MessageBox(0, "Faltan de rellenar campos", "Mensaje", 0);

	delete validacion;
}