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
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

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

	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
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
		case BTN_CUATERNIONES:
		{
			menu->OcultarBotones();
			cuaterniones->MostrarBotones();

			cuaterniones->CrearCuaternio((char*)"A");
			cuaterniones->CrearCuaternio((char*)"B");
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
	}
	break;
	case BTN_SAIR:
	{
		delete menu;
		delete ventana;
		delete matrices;
		DestroyWindow(hwnd);
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