#include "PantallaBresenham.h"

Bresenham::Bresenham(Ventana* bresenham)
{
	this->primeroA = NULL;
	this->auxA = NULL;
	this->primeroR = NULL;
	this->auxR = NULL;
	this->ventana = NULL;
	this->ventana = bresenham;
	this->validacion = new Validacion();

	for (int i = 0; i < (sizeof(this->btnPuntos) / sizeof(this->btnPuntos[0])); i++)
		this->btnPuntos[i] = NULL;

	for (int i = 0; i < 4; i++)
		this->lbl[i] = NULL;


	this->anchoCelda = 60;
	this->altoCelda = 40;
	this->pendiente = 0;

	this->editResultado = NULL;
	this->btnResultado = NULL;

	this->estadoBresenham = 0;
}

void Bresenham::CrearBotones()
{
	int contador = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			this->btnPuntos[contador] = CreateWindowEx
			(
				0,
				"BUTTON",
				this->textoBtnPuntos[contador],
				BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				(this->ventana->getMitadAncho()) - (this->anchoCelda * 2) + ((j) * (2 * this->anchoCelda)),
				(5 + 40 + 5 + 25 + (i * this->altoBtn)),
				(2 * this->anchoCelda),
				this->altoBtn,
				this->ventana->getHwnd(),
				(HMENU)this->definesBtnPuntos[contador],
				this->ventana->gethInstance(),
				NULL
			);
			contador++;
		}
	}

	this->btnResultado = CreateWindowEx
	(
		0,
		"BUTTON",
		this->textoBtnResultado,
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		(this->ventana->getMitadAncho()) + (4 * this->anchoCelda) + 5,
		5 + 40 + 5 + 25 + (3 * this->altoBtn) + 5,
		100,
		this->altoBtn,
		this->ventana->getHwnd(),
		(HMENU)this->definesBtnResultado,
		this->ventana->gethInstance(),
		NULL
	);

	for (int i = 0; i < 4; i++) 
	{
		this->lbl[i] = CreateWindowEx
		(
		    0,
			"STATIC",
			this->textoLblRecta[i],
			SS_SIMPLE |
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			(this->ventana->getMitadAncho()) - (2 * this->anchoCelda) + (this->anchoCelda / 2) - 5 +(i * this->anchoCelda),
			5,
			this->anchoCelda,
			this->altoBtn,
			this->ventana->getHwnd(),
			NULL,
			this->ventana->gethInstance(),
			NULL
		);
	}
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

	for (int i = 0; i < (sizeof(this->lbl) / sizeof(this->lbl[0])); i++)
		ShowWindow(this->lbl[i], false);
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
	else if (_tipo == "C")
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

		this->auxA = this->primeroA;
		int i = 0;
	}
}

void Bresenham::EliminarNodos(char* _tipo)
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
		this->primeroA = this->primeroA->sig;
		delete this->auxA;
		this->auxA = this->primeroA;
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
		this->primeroR = this->primeroR->sig;
		delete this->auxR;
		this->auxR = this->primeroR;
	}
}

void Bresenham::DestruirCeldas(char* _tipo)
{
	if (_tipo == "A")
	{
		this->auxA = this->primeroA;
		while (this->auxA->sig != NULL)
		{
			DestroyWindow(this->auxA->celda);
			this->auxA = this->auxA->sig;
		}
		DestroyWindow(this->auxA->celda);
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

		while (this->auxA->sig != NULL)
		{
			ZeroMemory(texto, sizeof(texto));
			GetWindowText(this->auxA->celda, texto, sizeof(texto));
			this->auxA->valor = atof(texto);
			this->auxA = this->auxA->sig;
		}
		ZeroMemory(texto, sizeof(texto));
		GetWindowText(this->auxA->celda, texto, sizeof(texto));
		this->auxA->valor = atof(texto);
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
				25,
				this->anchoCelda,
				40,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);
			this->auxA = this->auxA->sig;
		}
		if (this->estadoBresenham == 0)
		{
			EnableWindow(this->btnPuntos[1], false);
			EnableWindow(this->btnPuntos[2], true);
			EnableWindow(this->btnPuntos[3], true);
		}
		else
		{
			EnableWindow(this->primeroA->sig->sig->celda, false);
			SetWindowText(this->primeroA->sig->sig->celda, "0");
			EnableWindow(this->primeroA->sig->sig->sig->celda, false);
			SetWindowText(this->primeroA->sig->sig->sig->celda, "0");

			EnableWindow(this->btnPuntos[1], true);
			EnableWindow(this->btnPuntos[2], true);
			EnableWindow(this->btnPuntos[3], false);
		}
	}
	else if (_tipo == "C")
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
				(this->ventana->getMitadAncho()) - (2 * this->anchoCelda)  + ((i) * (this->anchoCelda)),
				25,
				this->anchoCelda,
				40,
				this->ventana->getHwnd(),
				NULL,
				this->ventana->gethInstance(),
				NULL
			);
			this->auxA = this->auxA->sig;
		}

		EnableWindow(this->primeroA->celda, false);
		SetWindowText(this->primeroA->celda, "0");
		EnableWindow(this->primeroA->sig->celda, false);
		SetWindowText(this->primeroA->sig->celda, "0");

		EnableWindow(this->btnPuntos[1], true);
		EnableWindow(this->btnPuntos[2], false);
		EnableWindow(this->btnPuntos[3], true);
	}
	else if (_tipo == "R")
	{
		this->editResultado = CreateWindowEx
		(
			0,
			"LISTBOX",
			"",
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_CAPTION | LBS_HASSTRINGS,
			(this->ventana->getMitadAncho()) - ((4) * (this->anchoCelda)), 5 + 40 + 5 + (3 * this->altoBtn) + 5,
			(4 * this->anchoCelda) * (2), 200 + 25,
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
	int contador = 0;
	while (this->auxA->sig != NULL)
	{
		if((this->estadoBresenham == 0) || (this->estadoBresenham == 2 && contador > 1))
		    SetWindowText(this->auxA->celda, "");
		
		this->auxA = this->auxA->sig;
		contador++;
	}
	SetWindowText(this->auxA->celda, "");
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
	if (!this->validacion->CeldasVacias(this->primeroA, this->auxA))
	{
		if (!this->validacion->ValidarFormato(this->primeroA, this->auxA))
		{
			if (!this->validacion->NoDecimales(this->primeroA, this->auxA))
			{
				this->GetValoresCeldas((char*)"A");
				int contador = 0;
				int x0 = this->primeroA->valor;
				int x1 = this->primeroA->sig->sig->valor;
				int y0 = this->primeroA->sig->valor;
				int y1 = this->primeroA->sig->sig->sig->valor;
				int x, y, dx, dy, p, incE, incNE, stepx, stepy;
				dx = (x1 - x0);
				dy = (y1 - y0);
				/* determinar que punto usar para empezar, cual para terminar */
				if (dy < 0) {
					dy = -dy;
					stepy = -1;
				}
				else
					stepy = 1;
				if (dx < 0) {
					dx = -dx;
					stepx = -1;
				}
				else
					stepx = 1;
				x = x0;
				y = y0;
				/* se cicla hasta llegar al extremo de la línea */

				this->CrearCeldas((char*)"R");

				char XI[MAXCHAR];
				char YI[MAXCHAR];
				char XF[MAXCHAR];
				char YF[MAXCHAR];
				char PK[MAXCHAR];
				char In[MAXCHAR];
				char Punto[MAXCHAR];

				if (dx > dy) {
					p = (2 * dy) - dx;
					incE = 2 * dy;
					incNE = 2 * (dy - dx);
					while (x != x1) {
						x = x + stepx;
						if (p < 0) {
							ZeroMemory(XI, sizeof(XI));
							ZeroMemory(YI, sizeof(YI));
							ZeroMemory(XF, sizeof(XF));
							ZeroMemory(YF, sizeof(YF));
							ZeroMemory(PK, sizeof(PK));
							ZeroMemory(In, sizeof(In));
							ZeroMemory(Punto, sizeof(Punto));

							sprintf_s(XI, "%d", x);
							sprintf_s(YI, "%d", y);
							sprintf_s(XF, "%d", x1);
							sprintf_s(YF, "%d", y1);
							sprintf_s(PK, "%d", p);
							sprintf_s(In, "%d", contador);

							sprintf_s(Punto, "%s%s", Punto, In);
							sprintf_s(Punto, "%s%s", Punto, "    ");
							sprintf_s(Punto, "%s%s", Punto, PK);
							sprintf_s(Punto, "%s%s", Punto, "    ");
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

							SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
							contador++;
							p = p + incE;
						}
						else {
							y = y + stepy;
							ZeroMemory(XI, sizeof(XI));
							ZeroMemory(YI, sizeof(YI));
							ZeroMemory(XF, sizeof(XF));
							ZeroMemory(YF, sizeof(YF));
							ZeroMemory(PK, sizeof(PK));
							ZeroMemory(In, sizeof(In));
							ZeroMemory(Punto, sizeof(Punto));

							sprintf_s(XI, "%d", x);
							sprintf_s(YI, "%d", y);
							sprintf_s(XF, "%d", x1);
							sprintf_s(YF, "%d", y1);
							sprintf_s(PK, "%d", p);
							sprintf_s(In, "%d", contador);

							sprintf_s(Punto, "%s%s", Punto, In);
							sprintf_s(Punto, "%s%s", Punto, "    ");
							sprintf_s(Punto, "%s%s", Punto, PK);
							sprintf_s(Punto, "%s%s", Punto, "    ");
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

							SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
							contador++;
							p = p + incNE;
						}
					}
				}
				else {
					p = 2 * dx - dy;
					incE = 2 * dx;
					incNE = 2 * (dx - dy);
					while (y != y1) {
						y = y + stepy;
						if (p < 0) {
							ZeroMemory(XI, sizeof(XI));
							ZeroMemory(YI, sizeof(YI));
							ZeroMemory(XF, sizeof(XF));
							ZeroMemory(YF, sizeof(YF));
							ZeroMemory(PK, sizeof(PK));
							ZeroMemory(In, sizeof(In));
							ZeroMemory(Punto, sizeof(Punto));

							sprintf_s(XI, "%d", x);
							sprintf_s(YI, "%d", y);
							sprintf_s(XF, "%d", x1);
							sprintf_s(YF, "%d", y1);
							sprintf_s(PK, "%d", p);
							sprintf_s(In, "%d", contador);

							sprintf_s(Punto, "%s%s", Punto, In);
							sprintf_s(Punto, "%s%s", Punto, "    ");
							sprintf_s(Punto, "%s%s", Punto, PK);
							sprintf_s(Punto, "%s%s", Punto, "    ");
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

							SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
							contador++;
							p = p + incE;
						}
						else {
							x = x + stepx;
							ZeroMemory(XI, sizeof(XI));
							ZeroMemory(YI, sizeof(YI));
							ZeroMemory(XF, sizeof(XF));
							ZeroMemory(YF, sizeof(YF));
							ZeroMemory(PK, sizeof(PK));
							ZeroMemory(In, sizeof(In));
							ZeroMemory(Punto, sizeof(Punto));

							sprintf_s(XI, "%d", x);
							sprintf_s(YI, "%d", y);
							sprintf_s(XF, "%d", x1);
							sprintf_s(YF, "%d", y1);
							sprintf_s(PK, "%d", p);
							sprintf_s(In, "%d", contador);

							sprintf_s(Punto, "%s%s", Punto, In);
							sprintf_s(Punto, "%s%s", Punto, "    ");
							sprintf_s(Punto, "%s%s", Punto, PK);
							sprintf_s(Punto, "%s%s", Punto, "    ");
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

							SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
							contador++;
							p = p + incNE;
						}
					}
				}
				this->MostrarBotonResultado();
				this->DeshabilitarBotones();
			}
			else
				MessageBox(NULL, "No se permiten decimales", "Mensaje", 0);
		}
		else
			MessageBox(NULL, "Formato incorrecto", "Mensaje", 0);
	}
	else
		MessageBox(NULL, "Falta de rellenar campos", "Mensaje", 0);

	this->LimpiarValoresNodos((char*)"A");
}

void Bresenham::MostrarBotonResultado()
{
	ShowWindow(this->btnResultado, true);
}

void Bresenham::OcultarBotonResultado()
{
	ShowWindow(this->btnResultado, false);
}

void Bresenham::LimpiarValoresNodos(char* _tipo)
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
	else if (_tipo == "R")
	{
		this->auxR = this->primeroR;
		while (this->auxR->sig != NULL)
		{
			this->auxR->valor = 0;
			this->auxR = this->auxR->sig;
		}
		this->auxR->valor = 0;
	}
}

void Bresenham::LimpiarResultado()
{
	DestroyWindow(this->editResultado);
	this->editResultado = NULL;
	this->OcultarBotonResultado();
	this->HabilitarBotones();
	if (this->estadoBresenham == 0)
		EnableWindow(this->btnPuntos[1], false);
	else if (this->estadoBresenham == 1)
		EnableWindow(this->btnPuntos[2], false);
}

void Bresenham::Circunfernecia()
{
	if (!this->validacion->CeldasVacias(this->primeroA, this->auxA))
	{
		if (!this->validacion->ValidarFormato(this->primeroA, this->auxA))
		{
			if (!this->validacion->NoDecimales(this->primeroA, this->auxA))
			{
				this->GetValoresCeldas((char*)"A");

				int centroX, centroY, r, p, x, y;

				centroX = this->primeroA->valor;
				centroY = this->primeroA->sig->valor;
				r = this->primeroA->sig->sig->valor;
				x = centroX;
				y = r;

				this->CrearCeldas((char*)"R");

				char K[MAXCHAR];
				char PK[MAXCHAR];
				char X[MAXCHAR];
				char Y[MAXCHAR];
				char A[MAXCHAR];
				char B[MAXCHAR];
				char Punto[MAXCHAR];

				int contador = 0;
				p = 1 - r;
				while (x < y)
				{
					x = x + 1;
					if (p < 0)
					{
						ZeroMemory(X, sizeof(X));
						ZeroMemory(Y, sizeof(Y));
						ZeroMemory(K, sizeof(K));
						ZeroMemory(PK, sizeof(PK));
						ZeroMemory(A, sizeof(A));
						ZeroMemory(B, sizeof(B));
						ZeroMemory(Punto, sizeof(Punto));

						sprintf_s(X, "%d", x);
						sprintf_s(Y, "%d", y);
						sprintf_s(K, "%d", contador);
						sprintf_s(A, "%d", 2 * x);
						sprintf_s(B, "%d", 2 * y);
						sprintf_s(PK, "%d", p);

						sprintf_s(Punto, "%s%s", Punto, K);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, PK);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, "(");
						sprintf_s(Punto, "%s%s", Punto, X);
						sprintf_s(Punto, "%s%s", Punto, ",");
						sprintf_s(Punto, "%s%s", Punto, Y);
						sprintf_s(Punto, "%s%s", Punto, ")");
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, A);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, B);
						sprintf_s(Punto, "%s%s", Punto, "   ");

						SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
						contador++;
						p = p + (2 * x) + 1;
					}
					else
					{
						y = y - 1;
						ZeroMemory(X, sizeof(X));
						ZeroMemory(Y, sizeof(Y));
						ZeroMemory(K, sizeof(K));
						ZeroMemory(PK, sizeof(PK));
						ZeroMemory(A, sizeof(A));
						ZeroMemory(B, sizeof(B));
						ZeroMemory(Punto, sizeof(Punto));

						sprintf_s(X, "%d", x);
						sprintf_s(Y, "%d", y);
						sprintf_s(K, "%d", contador);
						sprintf_s(A, "%d", 2 * x);
						sprintf_s(B, "%d", 2 * y);
						sprintf_s(PK, "%d", p);

						sprintf_s(Punto, "%s%s", Punto, K);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, PK);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, "(");
						sprintf_s(Punto, "%s%s", Punto, X);
						sprintf_s(Punto, "%s%s", Punto, ",");
						sprintf_s(Punto, "%s%s", Punto, Y);
						sprintf_s(Punto, "%s%s", Punto, ")");
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, A);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, B);
						sprintf_s(Punto, "%s%s", Punto, "   ");

						SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
						contador++;
						p = p + (2 * x) + 1 - (2 * y);
					}
				}
				this->MostrarBotonResultado();
				this->DeshabilitarBotones();
			}
			else
				MessageBox(NULL, "No se permiten decimales", "Mensaje", 0);
		}
		else
			MessageBox(NULL, "Formato incorrecto", "Mensaje", 0);
	}
	else
		MessageBox(NULL, "Falta de rellenar campos", "Mensaje", 0);


	this->LimpiarValoresNodos((char*)"A");
}

void Bresenham::Elipse()
{
	if (!this->validacion->CeldasVacias(this->primeroA, this->auxA))
	{
		if (!this->validacion->ValidarFormato(this->primeroA, this->auxA))
		{
			if (!this->validacion->NoDecimales(this->primeroA, this->auxA))
			{
				this->GetValoresCeldas((char*)"A");

				double p1, p2, x, y, x0, y0, rx, ry;

				rx = this->primeroA->valor;
				ry = this->primeroA->sig->valor;
				x0 = this->primeroA->sig->sig->valor;
				y0 = this->primeroA->sig->sig->sig->valor;

				p1 = pow(ry, 2);
				p1 = p1 - (pow(rx, 2) * ry);
				p1 = p1 + (pow(rx, 2) / 4);
				x = x0;
				y = ry;

				this->CrearCeldas((char*)"R");

				char K[MAXCHAR];
				char PK[MAXCHAR];
				char Punto[MAXCHAR];
				char X[MAXCHAR];
				char Y[MAXCHAR];
				char CONDICIONAL_A[MAXCHAR];
				char CONDICIONAL_B[MAXCHAR];

				int contador = 0;
				while ((2 * pow(ry, 2) * x) < (2 * pow(rx, 2) * y))
				{
					if (p1 < 0)
					{
						x = x + 1;
						ZeroMemory(K, sizeof(K));
						ZeroMemory(PK, sizeof(PK));
						ZeroMemory(Punto, sizeof(Punto));
						ZeroMemory(X, sizeof(X));
						ZeroMemory(Y, sizeof(Y));
						ZeroMemory(CONDICIONAL_A, sizeof(CONDICIONAL_A));
						ZeroMemory(CONDICIONAL_B, sizeof(CONDICIONAL_B));

						sprintf_s(K, "%d", contador);
						sprintf_s(PK, "%f", p1);
						sprintf_s(X, "%f", x);
						sprintf_s(Y, "%f", y);
						sprintf_s(CONDICIONAL_A, "%f", ((2 * pow(ry, 2)) * (x)));
						sprintf_s(CONDICIONAL_B, "%f", ((2 * pow(rx, 2)) * (y)));

						sprintf_s(Punto, "%s%s", Punto, K);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, PK);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, "(");
						sprintf_s(Punto, "%s%s", Punto, X);
						sprintf_s(Punto, "%s%s", Punto, ",");
						sprintf_s(Punto, "%s%s", Punto, Y);
						sprintf_s(Punto, "%s%s", Punto, ")");
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, CONDICIONAL_A);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, CONDICIONAL_B);

						SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
						contador++;
						p1 = p1 + ((2) * (pow(ry, 2)) * (x)) + pow(ry, 2);
					}
					else
					{
						x = x + 1;
						y = y - 1;
						ZeroMemory(K, sizeof(K));
						ZeroMemory(PK, sizeof(PK));
						ZeroMemory(Punto, sizeof(Punto));
						ZeroMemory(X, sizeof(X));
						ZeroMemory(Y, sizeof(Y));
						ZeroMemory(CONDICIONAL_A, sizeof(CONDICIONAL_A));
						ZeroMemory(CONDICIONAL_B, sizeof(CONDICIONAL_B));

						sprintf_s(K, "%d", contador);
						sprintf_s(PK, "%f", p1);
						sprintf_s(X, "%f", x);
						sprintf_s(Y, "%f", y);
						sprintf_s(CONDICIONAL_A, "%f", ((2 * pow(ry, 2)) * (x)));
						sprintf_s(CONDICIONAL_B, "%f", ((2 * pow(rx, 2)) * (y)));

						sprintf_s(Punto, "%s%s", Punto, K);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, PK);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, "(");
						sprintf_s(Punto, "%s%s", Punto, X);
						sprintf_s(Punto, "%s%s", Punto, ",");
						sprintf_s(Punto, "%s%s", Punto, Y);
						sprintf_s(Punto, "%s%s", Punto, ")");
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, CONDICIONAL_A);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, CONDICIONAL_B);

						SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
						contador++;
						p1 = p1 + ((2) * (pow(ry, 2)) * (x)) - ((2) * (pow(rx, 2)) * (y)) + pow(ry, 2);
					}
				}

				p2 = pow(ry, 2);
				p2 = p2 * pow(((x)+(1.0 / 2.0)), 2);
				p2 = p2 + (pow(rx, 2) * pow((y - 1.0), 2));
				p2 = p2 - (pow(rx, 2) * pow(ry, 2));

				while (y != 0)
				{
					if (p2 > 0)
					{
						x = x;
						y = y - 1;
						ZeroMemory(K, sizeof(K));
						ZeroMemory(PK, sizeof(PK));
						ZeroMemory(Punto, sizeof(Punto));
						ZeroMemory(X, sizeof(X));
						ZeroMemory(Y, sizeof(Y));
						ZeroMemory(CONDICIONAL_A, sizeof(CONDICIONAL_A));
						ZeroMemory(CONDICIONAL_B, sizeof(CONDICIONAL_B));

						sprintf_s(K, "%d", contador);
						sprintf_s(PK, "%f", p2);
						sprintf_s(X, "%f", x);
						sprintf_s(Y, "%f", y);
						sprintf_s(CONDICIONAL_A, "%f", ((2 * pow(ry, 2)) * (x)));
						sprintf_s(CONDICIONAL_B, "%f", ((2 * pow(rx, 2)) * (y)));

						sprintf_s(Punto, "%s%s", Punto, K);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, PK);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, "(");
						sprintf_s(Punto, "%s%s", Punto, X);
						sprintf_s(Punto, "%s%s", Punto, ",");
						sprintf_s(Punto, "%s%s", Punto, Y);
						sprintf_s(Punto, "%s%s", Punto, ")");
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, CONDICIONAL_A);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, CONDICIONAL_B);

						SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
						contador++;
						p2 = p2 - ((2) * (pow(rx, 2)) * (y)) + pow(rx, 2);
					}
					else
					{
						x = x + 1;
						y = y - 1;
						ZeroMemory(K, sizeof(K));
						ZeroMemory(PK, sizeof(PK));
						ZeroMemory(Punto, sizeof(Punto));
						ZeroMemory(X, sizeof(X));
						ZeroMemory(Y, sizeof(Y));
						ZeroMemory(CONDICIONAL_A, sizeof(CONDICIONAL_A));
						ZeroMemory(CONDICIONAL_B, sizeof(CONDICIONAL_B));

						sprintf_s(K, "%d", contador);
						sprintf_s(PK, "%f", p2);
						sprintf_s(X, "%f", x);
						sprintf_s(Y, "%f", y);
						sprintf_s(CONDICIONAL_A, "%f", ((2 * pow(ry, 2)) * (x)));
						sprintf_s(CONDICIONAL_B, "%f", ((2 * pow(rx, 2)) * (y)));

						sprintf_s(Punto, "%s%s", Punto, K);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, PK);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, "(");
						sprintf_s(Punto, "%s%s", Punto, X);
						sprintf_s(Punto, "%s%s", Punto, ",");
						sprintf_s(Punto, "%s%s", Punto, Y);
						sprintf_s(Punto, "%s%s", Punto, ")");
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, CONDICIONAL_A);
						sprintf_s(Punto, "%s%s", Punto, "   ");
						sprintf_s(Punto, "%s%s", Punto, CONDICIONAL_B);

						SendMessage(this->editResultado, LB_INSERTSTRING, contador, (LPARAM)Punto);
						contador++;
						p2 = p2 + ((2) * (pow(ry, 2)) * (x)) - ((2) * (pow(rx, 2)) * (y)) + pow(rx, 2);
					}
				}
				this->MostrarBotonResultado();
				this->DeshabilitarBotones();
			}
			else
				MessageBox(NULL, "No se permiten decimales", "Mensaje", 0);
		}
		else
			MessageBox(NULL, "Formato incorrecto", "Mensaje", 0);
	}
	else
		MessageBox(NULL, "Falta de rellenar campos", "Mensaje", 0);

	this->LimpiarValoresNodos((char*)"A");
}

void Bresenham::MostrarLblRecta() 
{
	for (int i = 0; i < 4; i++) 
	{
		SetWindowText(this->lbl[i], this->textoLblRecta[i]);
	}
}

void Bresenham::MostrarLblCircunferencia()
{
	for (int i = 0; i < 4; i++)
	{
		SetWindowText(this->lbl[i], this->textoLblCircunferencia[i]);
	}
}

void Bresenham::MostrarLblElipse()
{
	for (int i = 0; i < 4; i++)
	{
		SetWindowText(this->lbl[i], this->textoLblElipse[i]);
	}
}