#include <Windows.h>
#include "BSP.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
	CBSP bsp;
	bsp.LoadFromFile(L"de_dust2.bsp");

	return EXIT_SUCCESS;
}
