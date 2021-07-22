#include <windows.h>
//global function decalration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable decalaration

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declaration
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	//code
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndClass);

	//create window in memory
	hwnd = CreateWindow(szAppName,
						TEXT("DRG:MY First Window"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	//Message Loop
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam, LPARAM lParam)
{
	//code
	int num1, num2, num3;
	TCHAR str[255];
	switch (iMsg)
	{
	case WM_CREATE:
		num1 = 75;
		num2 = 25;
		num3 = num1 + num2;
		wsprintf(str,TEXT("Addition of %d and %d is %d."),num1,num2,num3);

		MessageBox(hwnd,str,TEXT("Addition"),MB_OK);
		break;

	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	default :
		break;
	}
	
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));

}
