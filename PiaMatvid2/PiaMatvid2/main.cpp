#include <Windows.h>
#include "Matvid2.h"

HINSTANCE hInst;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	hInst = hInstance;
	HWND hwnd;
	MSG mensaje;
	WNDCLASSEX wincl;

	wincl.hInstance = hInstance;
	wincl.lpszClassName = "ClaseVentana";
	wincl.lpfnWndProc = WindowProcedure;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof(WNDCLASSEX);

	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = (HBRUSH)COLOR_BTNFACE;

	if (!RegisterClassEx(&wincl)) return 0;

	hwnd = CreateWindowEx(
		0,
		"ClaseVentana",
		"Matematicas para videojuegos 2",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_SHOWDEFAULT);

	while (TRUE == GetMessage(&mensaje, 0, 0, 0))
	{
		TranslateMessage(&mensaje);
		DispatchMessage(&mensaje);
	}

	return mensaje.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static Ventana* ventana = new Ventana(785, 585, hwnd, hInst);
	static Menu* menu = new Menu(ventana);
	static Matrices* matrices = new Matrices(ventana, 3, 3);
	static Cuaterniones* cuaterniones = new Cuaterniones(ventana);
	static Transformaciones* transformaciones = new Transformaciones(ventana);
	static Vectores* vectores = new Vectores(ventana);
	static Bresenham* bresenham = new Bresenham(ventana);

	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			//---------------------------------------------------------------------------------------------------
			//|                                          Matrices                                                |
			//---------------------------------------------------------------------------------------------------
		case BTN_MULTIPLICARM:
		{
			matrices->Multiplicar();
		}
		break;
		case BTN_RESTARM:
		{
			matrices->Restar();
		}
		break;
		case BTN_MOVERAM:
		{
			matrices->MandarResultado((char*)"A");
		}
		break;
		case BTN_MOVERBM:
		{
			matrices->MandarResultado((char*)"B");
		}
		break;
		case BTN_LIMPIARRM:
		{
			matrices->LimpiarResultado();
		}
		break;
		case BTN_SUMARM:
		{
			matrices->Sumar();
		}
		break;
		case BTN_INTERCAMBIARM:
		{
			matrices->Intercambiar();
		}
		break;
		case BTN_TRANSPUESTABM:
		{
			matrices->Transpuesta((char*)"B");
		}
		break;
		case BTN_TRANSPUESTAAM:
		{
			matrices->Transpuesta((char*)"A");
		}
		break;
		case BTN_OKAM:
		{
			matrices->DestruirMatriz((char*)"A");
			matrices->EliminarNodos((char*)"A");
			matrices->CambiarDimensiones((char*)"A");
			matrices->GenerarNodos((char*)"A");
			matrices->CrearCeldas((char*)"A");
		}
		break;
		case BTN_OKBM:
		{
			matrices->DestruirMatriz((char*)"B");
			matrices->EliminarNodos((char*)"B");
			matrices->CambiarDimensiones((char*)"B");
			matrices->GenerarNodos((char*)"B");
			matrices->CrearCeldas((char*)"B");
		}
		break;
		case BTN_REGRESARM:
		{
			matrices->OcultarBotones();
			matrices->DestruirMatriz((char*)"A");
			matrices->DestruirMatriz((char*)"B");
			matrices->EliminarNodos((char*)"A");
			matrices->EliminarNodos((char*)"B");
			menu->MostarBotones();
		}
		break;
		case BTN_LIMPIARAM:
		{
			matrices->LimpiarMatriz((char*)"A");
		}
		break;
		case BTN_LIMPIARBM:
		{
			matrices->LimpiarMatriz((char*)"B");
		}
		break;
		case BTN_MATRICES:
		{
			menu->OcultarBotones();
			matrices->MostrarBotones();

			matrices->GenerarNodos((char*)"A");
			matrices->GenerarNodos((char*)"B");
			matrices->CrearCeldas((char*)"A");
			matrices->CrearCeldas((char*)"B");
		}
		break;
		//---------------------------------------------------------------------------------------------------
		//|                                          Cuaterniones                                            |
		//---------------------------------------------------------------------------------------------------
		case BTN_CUATERNIONES:
		{
			menu->OcultarBotones();
			cuaterniones->MostrarBotones();

			cuaterniones->CrearCuaternio((char*)"A");
			cuaterniones->CrearCuaternio((char*)"B");
		}
		break;
		case BTN_REGRESARC:
		{
			cuaterniones->OcultarBotones();
			cuaterniones->DestruirVentanas((char*)"A");
			cuaterniones->DestruirVentanas((char*)"B");
			cuaterniones->DestruirCuaternio((char*)"A");
			cuaterniones->DestruirCuaternio((char*)"B");
			menu->MostarBotones();
		}
		break;
		case BTN_LIMPIARRC:
		{
			cuaterniones->LimpiarResultado();
		}
		break;
		case BTN_LIMPIARAC:
		{
			cuaterniones->LimpiarCuaternio((char*)"A");
		}
		break;
		case BTN_LIMPIARBC:
		{
			cuaterniones->LimpiarCuaternio((char*)"B");
		}
		break;
		case BTN_NULOAC:
		{
			cuaterniones->Nulo((char*)"A");
		}
		break;
		case BTN_NULOBC:
		{
			cuaterniones->Nulo((char*)"B");
		}
		break;
		case BTN_CONJUGADOAC:
		{
			cuaterniones->Conjugado((char*)"A");
		}
		break;
		case BTN_CONJUGADOBC:
		{
			cuaterniones->Conjugado((char*)"B");
		}
		break;
		case BTN_OPUESTOAC:
		{
			cuaterniones->Opuesto((char*)"A");
		}
		break;
		case BTN_OPUESTOBC:
		{
			cuaterniones->Opuesto((char*)"B");
		}
		break;
		case BTN_ABSOLUTOAC:
		{
			cuaterniones->ValorAbsoluto((char*)"A");
		}
		break;
		case BTN_ABSOLUTOBC:
		{
			cuaterniones->ValorAbsoluto((char*)"B");
		}
		break;
		case BTN_NORMALIZADOAC:
		{
			cuaterniones->Normalizacion((char*)"A");
		}
		break;
		case BTN_NORMALIZADOBC:
		{
			cuaterniones->Normalizacion((char*)"B");
		}
		break;
		case BTN_INVERSOAC:
		{
			cuaterniones->Inverso((char*)"A");
		}
		break;
		case BTN_INVERSOBC:
		{
			cuaterniones->Inverso((char*)"B");
		}
		break;
		case BTN_MULTIPLICARC:
		{
			cuaterniones->Multiplicar();
		}
		break;
		case BTN_GRASSMAN:
		{
			cuaterniones->Grassman();
		}
		break;
		case BTN_RESTARC:
		{
			cuaterniones->Restar();
		}
		break;
		case BTN_SUMARC:
		{
			cuaterniones->Sumar();
		}
		break;
		case BTN_INTERCAMBIARC:
		{
			cuaterniones->Intercambiar();
		}
		break;
		case BTN_MOVERAC:
		{
			cuaterniones->Mandar((char*)"A");
		}
		break;
		case BTN_UNITARIOAC: 
		{
			cuaterniones->EsUnitario((char*)"A");
		}
		break;
		case BTN_UNITARIOBC:
		{
			cuaterniones->EsUnitario((char*)"B");
		}
		break;
		case BTN_MOVERBC:
		{
			cuaterniones->Mandar((char*)"B");
		}
		break;
		//---------------------------------------------------------------------------------------------------
		//|                                       Transformacion matrices                                   |
		//---------------------------------------------------------------------------------------------------
		case BTN_TRANSFORMACIONES:
		{
			menu->OcultarBotones();
			transformaciones->MostrarBotones();
			transformaciones->GenerarNodos((char*)"A");
			transformaciones->GenerarNodos((char*)"BP");
			transformaciones->CrearMatriz((char*)"A");
			transformaciones->CrearMatriz((char*)"BP");
			transformaciones->setPunto(false);
			transformaciones->setRotacionA(-1);
			transformaciones->setRotacionB(-1);
		}
		break;
		case BTN_REGRESART:
		{
			transformaciones->OcultarBotones();
			transformaciones->DestruirMatriz((char*)"A");
			transformaciones->DestruirMatriz((char*)"B");
			transformaciones->EliminarNodos((char*)"A");
			transformaciones->EliminarNodos((char*)"B");
			menu->MostarBotones();
		}
		break;
		case BTN_LIMPIARAT:
		{
			transformaciones->LimpiarMatriz((char*)"A");
			transformaciones->setRotacionA(-1);
		}
		break;
		case BTN_LIMPIARBT:
		{
			transformaciones->LimpiarMatriz((char*)"B");
			transformaciones->setRotacionB(-1);
		}
		break;
		case BTN_TRANSLADARAT:
		{
			transformaciones->Transladar((char*)"A");
		}
		break;
		case BTN_TRANSLADARBT:
		{
			transformaciones->Transladar((char*)"B");
		}
		break;
		case BTN_ESCALARAT:
		{
			transformaciones->Escalar((char*)"A");
		}
		break;
		case BTN_ESCALARBT:
		{
			transformaciones->Escalar((char*)"B");
		}
		break;
		case BTN_ROTARXAT:
		{
			transformaciones->Rotar((char*)"X", (char*)"A");
		}
		break;
		case BTN_ROTARXBT:
		{
			transformaciones->Rotar((char*)"X", (char*)"B");
		}
		break;
		case BTN_ROTARYAT:
		{
			transformaciones->Rotar((char*)"Y", (char*)"A");
		}
		break;
		case BTN_ROTARYBT:
		{
			transformaciones->Rotar((char*)"Y", (char*)"B");
		}
		break;
		case BTN_ROTARZAT:
		{
			transformaciones->Rotar((char*)"Z", (char*)"A");
		}
		break;
		case BTN_ROTARZBT:
		{
			transformaciones->Rotar((char*)"Z", (char*)"B");
		}
		break;
		case BTN_MULTIPLICART:
		{
			transformaciones->Multiplicar();
		}
		break;
		case BTN_LIMPIARRT:
		{
			transformaciones->LimpiarResultado();
		}
		break;
		case BTN_MATRIZT:
		{
			transformaciones->DestruirMatriz((char*)"B");
			transformaciones->EliminarNodos((char*)"B");

			transformaciones->GenerarNodos((char*)"B");
			transformaciones->CrearMatriz((char*)"B");

			transformaciones->setPunto(TRUE);
		}
		break;
		case BTN_PUNTOT:
		{
			transformaciones->DestruirMatriz((char*)"B");
			transformaciones->EliminarNodos((char*)"B");

			transformaciones->GenerarNodos((char*)"BP");
			transformaciones->CrearMatriz((char*)"BP");
			transformaciones->setPunto(FALSE);
			transformaciones->setRotacionB(-1);
		}
		break;
		//---------------------------------------------------------------------------------------------------
		//|                                              Vectores                                           |
		//---------------------------------------------------------------------------------------------------
		case BTN_VECTORES:
		{
			menu->OcultarBotones();
			vectores->MostrarBotones();
			vectores->GenerarNodos((char*)"A");
			vectores->GenerarNodos((char*)"B");
			vectores->CrearVector((char*)"A");
			vectores->CrearVector((char*)"B");
			vectores->EstadoIncialEscalarVector();
		}
		break;
		case BTN_LIMPIARAV:
		{
			vectores->LimpiarVector((char*)"A");
		}
		break;
		case BTN_LIMPIARBV:
		{
			vectores->LimpiarVector((char*)"B");
		}
		break;
		case BTN_LONGITUDAV:
		{
			vectores->Longitud((char*)"A");
		}
		break;
		case BTN_LONGITUDBV:
		{
			vectores->Longitud((char*)"B");
		}
		break;
		case BTN_NORMALIZACIONAV:
		{
			vectores->Normalizar((char*)"A");
		}
		break;
		case BTN_NORMALIZACIONBV:
		{
			vectores->Normalizar((char*)"B");
		}
		break;
		case BTN_LIMPIARRV:
		{
			vectores->LimpiarResultado();
		}
		break;
		case BTN_REGRESARV:
		{
			vectores->OcultarBotones();
			vectores->DestruirVector((char*)"A");
			vectores->DestruirVector((char*)"B");
			vectores->EliminarNodos((char*)"A");
			vectores->EliminarNodos((char*)"B");
			menu->MostarBotones();
		}
		break;
		case BTN_ESCALARAV:
		{
			vectores->Escalar();
		}
		break;
		case BTN_VECTORAV:
		{
			vectores->Vector();
		}
		break;
		case BTN_SUMARV:
		{
			vectores->Suma();
		}
		break;
		case BTN_RESTARV:
		{
			vectores->Restar();
		}
		break;
		case BTN_MULTIPLICARV:
		{
			vectores->Multiplicar();
		}
		break;
		case BTN_NEGARAV:
		{
			vectores->Negar((char*)"A");
		}
		break;
		case BTN_NEGARBV:
		{
			vectores->Negar((char*)"B");
		}
		break;
		case BTN_UNITARIOAV:
		{
			vectores->EsUnitario((char*)"A");
		}
		break;
		case BTN_UNITARIOBV:
		{
			vectores->EsUnitario((char*)"B");
		}
		break;
		//---------------------------------------------------------------------------------------------------
		//|                                              Bresenham                                          |
		//---------------------------------------------------------------------------------------------------
		case BTN_BRESENHAM:
		{
			menu->OcultarBotones();

			bresenham->CrearBotones();
			bresenham->MostrarLblRecta();
			bresenham->OcultarBotonResultado();
			bresenham->GenerarNodos((char*)"A");
			bresenham->CrearCeldas((char*)"A");
		}
		break;
		case BTN_REGRESARB:
		{

			bresenham->OcultarBotones();
			bresenham->DestruirCeldas((char*)"A");
			bresenham->EliminarNodos((char*)"A");

			menu->MostarBotones();
		}
		break;
		case BTN_LIMPIARB:
		{
			bresenham->LimpiarCeldas();
		}
		break;
		case BTN_BRESENHAMB:
		{
			bresenham->MostrarLblRecta();
			bresenham->setEstadoBresenham(0);
			bresenham->DestruirCeldas((char*)"A");
			bresenham->EliminarNodos((char*)"A");
			bresenham->GenerarNodos((char*)"A");
			bresenham->CrearCeldas((char*)"A");
		}
		break;
		case BTN_RESULTADOB:
		{
			bresenham->OcultarBotonResultado();
			bresenham->LimpiarResultado();
		}
		break;
		case BTN_CIRCUNFERENCIAB:
		{
			bresenham->MostrarLblCircunferencia();
			bresenham->setEstadoBresenham(1);
			bresenham->DestruirCeldas((char*)"A");
			bresenham->EliminarNodos((char*)"A");
			bresenham->GenerarNodos((char*)"C");
			bresenham->CrearCeldas((char*)"C");
		}
		break;
		case BTN_ELIPSEB:
		{
			bresenham->MostrarLblElipse();
			bresenham->setEstadoBresenham(2);
			bresenham->DestruirCeldas((char*)"A");
			bresenham->EliminarNodos((char*)"A");
			bresenham->GenerarNodos((char*)"A");
			bresenham->CrearCeldas((char*)"A");
		}
		break;
		case BTN_GENERARPUNTOSB:
		{
			if (bresenham->getEstadoBresenham() == 0)
				bresenham->RealizarBresenham();
			else if (bresenham->getEstadoBresenham() == 1)
				bresenham->Circunfernecia();
			else if (bresenham->getEstadoBresenham() == 2)
				bresenham->Elipse();
		}
		break;
		case BTN_SAIR:
		{
			delete bresenham;
			delete cuaterniones;
			delete menu;
			delete ventana;
			delete matrices;
			DestroyWindow(hwnd);
		}
		break;
		default:
			break;
		}
	}
	break;
	case WM_CREATE:
	{
		menu->crearBotones();
		matrices->CrearBotones();
		matrices->OcultarBotones();
		matrices->OcultarBotonesResultado();

		cuaterniones->CrearBotones();
		cuaterniones->OcultarBotones();
		cuaterniones->OcultarBotonesResultado();

		transformaciones->CrearBotones();
		transformaciones->OcultarBotones();
		transformaciones->OcultarBotonResultado();

		vectores->CrearBotones();
		vectores->OcultarBotones();
		vectores->OcultarBotonResultado();

		bresenham->CrearBotones();
		bresenham->OcultarBotones();
		bresenham->OcultarBotonResultado();
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}