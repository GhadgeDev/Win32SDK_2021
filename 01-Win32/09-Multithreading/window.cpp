#include <windows.h>
#include "Window.h"
#include<tchar.h>

//global function decalration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

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
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	RegisterClassEx(&wndClass);

	//create window in memory
	hwnd = CreateWindow(szAppName,
						TEXT("DRG:Multi Threading"),
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
	static HANDLE hThread1 = NULL;
	static HANDLE hThread2 = NULL;

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProcOne,(LPVOID)hwnd,0,NULL);	//to create thread ani returns handle
		// para1 : security parameter NULL means default
		// para2 : size of stack because every thread has own stack..0 means mala size tharvata yet nai aahe os tu main thread la jo detes to mala de Os tu tharav
		// para3 : Every thread has its associated function.Ya thread cha callback function LPTHREAD_START_ROUTINE ya pointer la typecast kara..
		// para4 : 4th parameter 4th para n manta to 3rd para madhe lihilelya function cha parameter mana
		// para5 : Tumhala thread kasa pahije hawa..0 mhnje lgech suru ho
		// para6 : Thread cha id till win97 
		/***here should be error checking for hThread1***/
		
		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		/***here should be error checking for hThread2***/
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("I am thread4"), TEXT("Message"),MB_OK);
		break;
	case WM_DESTROY:
		//CloseHandle(hThread1);			//to close thread
		CloseHandle(hThread2);
		PostQuitMessage(0);
		break;
	
	default :
		break;
	}
	
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
DWORD WINAPI ThreadProcOne(LPVOID param)
{
	//Variable Declaration
	HDC hdc = NULL;
	TCHAR str[255];
	long i;

	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0,255,0));

	for ( i = 0; i < 2147483648; i++)
	{
		wsprintf(str,TEXT("Incrementing Order : %ld"),i);
		TextOut(hdc,5,5,str,(int)_tcslen(str));			//special para,x,y,string,tchar valya string chi length kadhnyasathi
	}

	ReleaseDC((HWND)param, hdc);
	return(0);
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	//Variable Declaration
	HDC hdc = NULL;
	TCHAR str[255];
	long i;

	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 0, 0));

	for (i = 2147483647; i >= 0; i--)
	{
		wsprintf(str, TEXT("Decrementing Order : %ld"), i);
		TextOut(hdc, 5, 25, str, (int)_tcslen(str));			//special para,x,y,string,tchar valya string chi length kadhnyasathi
	}

	ReleaseDC((HWND)param, hdc);
	return(0);
}

