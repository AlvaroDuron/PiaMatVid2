#include "PantallaBresenham.h"

Bresenham::Bresenham(Ventana* bresenham)
{
	this->primeroA = NULL;
	this->auxA = NULL;
	this->primeroR = NULL;
	this->auxR = NULL;
	this->ventana = NULL;
	this->ventana = bresenham;

	for (int i = 0; i < (sizeof(this->btnPuntos) / sizeof(this->btnPuntos[0])); i++)
		this->btnPuntos[i] = NULL;

	this->xI = 0;
	this->yI = 0;
	this->xF = 0;
	this->yF = 0;
	this->deltaX = 0;
	this->deltaY = 0;
	this->A = 0;
	this->B = 0;
	this->P = NULL;
	this->anchoCelda = 60;
	this->altoCelda = 40;

	this->editResultado = NULL;
}

void Bresenham::CrearBotones()
{
	for (int i = 0; i < (sizeof(this->btnPuntos) / sizeof(this->btnPuntos[0])); i++)
		this->btnPuntos[i] = CreateWindowEx
		(
			0,
			"BUTTON",
			this->textoBtnPuntos[i],
			BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			i == 2 ? ventana->getMitadAncho() - ((2) * this->anchoCelda) : ventana->getMitadAncho() - ((2) * this->anchoCelda) + ((i) * (2 * this->anchoCelda)),
			i == 2 ? 5 + 40 + 5 + 20 : 5 + 40 + 5,
			i == 2 ? (4 * this->anchoCelda) : (2 * this->anchoCelda),
			this->altoBtn,
			this->ventana->getHwnd(),
			(HMENU)this->definesBtnPuntos[i],
			this->ventana->gethInstance(),
			NULL
		);
}

void Bresenham::MostrarBotones()
{
	for (int i = 0; i < (sizeof(this->btnPuntos) / sizeof(this->btnPuntos[0])); i++)
		ShowWindow(this->btnPuntos[i], true);
}

void Bresenham::OcultarBotones()
{
	for (int i = 0; i < (sizeof(this->btnPuntos) / sizeof(this->btnPuntos[0])); i++)
		ShowWindow(this->btnPuntos[i], false);
}

void Bresenham::GenerarNodos(char* _tipo)
{
	if (_tipo == "A")
	{
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
	}
}

void Bresenham::EliminarNodos(char* _tipo)
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
}

void Bresenham::DestruirCeldas(char* _tipo)
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
}

void Bresenham::HabilitarBotones()
{
	for (int i = 0; i < (sizeof(this->btnPuntos) / sizeof(this->btnPuntos[0])); i++)
		EnableWindow(this->btnPuntos[i], true);
}

void Bresenham::DeshabilitarBotones()
{
	for (int i = 0; i < (sizeof(this->btnPuntos) / sizeof(this->btnPuntos[0])); i++)
		EnableWindow(this->btnPuntos[i], false);
}

void Bresenham::GetValoresCeldas(char* _tipo)
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
}

void Bresenham::SetValoresCeldas(char* _tipo)
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
}

void Bresenham::CrearCeldas(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		for (int i = 0; i < 4; i++)
		{
			this->auxA->celda = CreateWindowEx
			(
				0,
				"EDIT",
				"",
				ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				(this->ventana->getMitadAncho()) - (2 * this->anchoCelda) + ((i) * (this->anchoCelda)),
				5,
				this->anchoCelda,
				40,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);
			this->auxA = this->auxA->sig;
		}
	}
	else if(_tipo == "R")
	{
		this->editResultado = CreateWindowEx
		(
			0,
			"LISTBOX",
			"",
			LBS_STANDARD | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 
			9, 19,          
			104, 99,        
			this->ventana->getHwnd(),            
			(HMENU)604,
			this->ventana->gethInstance(),
			NULL
		);
	}
}

void Bresenham::LimpiarCeldas() 
{
	this->auxA = this->primeroA;
	for (int i = 0; i < 4; i++) 
	{
		SetWindowText(this->auxA->celda, "");
		this->auxA = this->auxA->sig;
	}
}

void Bresenham::GenerarNodosP(int cantidad) 
{
	for (int i = 0; i < cantidad; i++) 
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

void Bresenham::RealizarBresenham() 
{
    //Variables iniciales
	this->GetValoresCeldas((char*)"A");

	this->xI = this->primeroA->valor;

	this->yI = this->primeroA->sig->valor;

	this->xF = this->primeroA->sig->sig->valor;

	this->yF = this->primeroA->sig->sig->sig->valor;

	this->deltaX = this->xF - this->xI;
	this->deltaY = this->yF - this->yI;

	this->A = 2 * deltaY;
	this->B = (2 * this->deltaY) - (2 * this->deltaX);

	this->P = (2 * deltaY) - (deltaX);

	this->GenerarNodosP(this->deltaX + 1);

	this->auxR = this->primeroR;
	this->auxR->valor = this->P;
	this->auxR = this->auxR->sig;

	this->CrearCeldas((char*)"R");

	char XI[MAXCHAR];
	char YI[MAXCHAR];
	char XF[MAXCHAR];
	char YF[MAXCHAR];
	char Punto[MAXCHAR];

	ZeroMemory(XI, sizeof(XI));
	ZeroMemory(YI, sizeof(YI));
	ZeroMemory(XF, sizeof(XF));
	ZeroMemory(YF, sizeof(YF));
	ZeroMemory(Punto, sizeof(Punto));

	sprintf_s(XI, "%d", this->xI);
	sprintf_s(YI, "%d", this->yI);
	sprintf_s(XF, "%d", this->xF);
	sprintf_s(YF, "%d", this->yF);

	sprintf_s(Punto, "%s%s", Punto, "(");
	sprintf_s(Punto, "%s%s", Punto, XI);
	sprintf_s(Punto, "%s%s", Punto, ",");
	sprintf_s(Punto, "%s%s", Punto, YI);
	sprintf_s(Punto, "%s%s", Punto, ")");
	sprintf_s(Punto, "%s%s", Punto, "(");
	sprintf_s(Punto, "%s%s", Punto, XF);
	sprintf_s(Punto, "%s%s", Punto, ",");
	sprintf_s(Punto, "%s%s", Punto, YF);
	sprintf_s(Punto, "%s%s", Punto, ")");

	SendMessage(this->editResultado, LB_ADDSTRING, 0, (LPARAM)Punto);

	for (int i = 0; i < this->deltaX; i++) 
	{
		if (this->P < 0) 
		{
		    //Dibujar pixel

			this->xI = this->xI + 1;
			this->yI = this->yI;

			ZeroMemory(Punto, sizeof(Punto));
			ZeroMemory(XI, sizeof(XI));
			ZeroMemory(YI, sizeof(YI));
			sprintf_s(XI, "%d", this->xI);
			sprintf_s(YI, "%d", this->yI);

			sprintf_s(Punto, "%s%s", Punto, "(");
			sprintf_s(Punto, "%s%s", Punto, XI);
			sprintf_s(Punto, "%s%s", Punto, ",");
			sprintf_s(Punto, "%s%s", Punto, YI);
			sprintf_s(Punto, "%s%s", Punto, ")");
			sprintf_s(Punto, "%s%s", Punto, "(");
			sprintf_s(Punto, "%s%s", Punto, XF);
			sprintf_s(Punto, "%s%s", Punto, ",");
			sprintf_s(Punto, "%s%s", Punto, YF);
			sprintf_s(Punto, "%s%s", Punto, ")");

			SendMessage(this->editResultado, LB_ADDSTRING, 0, (LPARAM)Punto);

			this->P = this->P + this->A;
		}
		else if (this->P >= 0) 
		{
			this->xI = this->xI + 1;
			this->yI = this->yI + 1;

			ZeroMemory(Punto, sizeof(Punto));
			ZeroMemory(XI, sizeof(XI));
			ZeroMemory(YI, sizeof(YI));
			sprintf_s(XI, "%d", this->xI);
			sprintf_s(YI, "%d", this->yI);

			sprintf_s(Punto, "%s%s", Punto, "(");
			sprintf_s(Punto, "%s%s", Punto, XI);
			sprintf_s(Punto, "%s%s", Punto, ",");
			sprintf_s(Punto, "%s%s", Punto, YI);
			sprintf_s(Punto, "%s%s", Punto, ")");
			sprintf_s(Punto, "%s%s", Punto, "(");
			sprintf_s(Punto, "%s%s", Punto, XF);
			sprintf_s(Punto, "%s%s", Punto, ",");
			sprintf_s(Punto, "%s%s", Punto, YF);
			sprintf_s(Punto, "%s%s", Punto, ")");

			SendMessage(this->editResultado, LB_ADDSTRING, 0, (LPARAM)Punto);

			this->P = this->P + this->B;
		}

		this->auxR->valor = this->P;
		this->auxR = this->auxR->sig;
	}
}