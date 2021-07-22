/*automatic Painting*/
#include <windows.h>
#define ID_TIMER_ONE 101

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
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
	//variable declaration
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	HBRUSH hBrush;
	static int iPaintFlag = 0;
	

	switch (iMsg)
	{
		case WM_CREATE:
			SetTimer(hwnd,ID_TIMER_ONE,1000,NULL);
			break;

		case WM_TIMER:
			KillTimer(hwnd,ID_TIMER_ONE);
			iPaintFlag = iPaintFlag + 1;
			
			if (iPaintFlag >= 8)
			{
				iPaintFlag = 0;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER_ONE, 1000, NULL);
			
			break;

		case WM_PAINT:
			GetClientRect(hwnd,&rc);
			hdc = BeginPaint(hwnd,&ps);
			if (iPaintFlag == 1)
			{
				hBrush = CreateSolidBrush(RGB(255,0,0));
		
			}
			else if (iPaintFlag == 2)
			{
				hBrush = CreateSolidBrush(RGB(0,255,0));
			
			}
			else if (iPaintFlag == 3)
			{
				hBrush = CreateSolidBrush(RGB(0, 0, 255));
			}
			else if (iPaintFlag == 4)
			{
				hBrush = CreateSolidBrush(RGB(0, 255, 255));
			}
			else if (iPaintFlag == 5)
			{
				hBrush = CreateSolidBrush(RGB(255, 0, 255));
			}
			else if (iPaintFlag == 6)
			{
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
			}
			else if (iPaintFlag == 7)
			{
				hBrush = CreateSolidBrush(RGB(0, 0, 0));
			}
			else if (iPaintFlag == 8)
			{
				hBrush = CreateSolidBrush(RGB(255, 255, 255));
			}
			else
			{
			
				hBrush = CreateSolidBrush(RGB(0, 0, 0));
			}

			SelectObject(hdc, hBrush);
			FillRect(hdc,&rc,hBrush);
			DeleteObject(hBrush);
			EndPaint(hwnd,&ps);

			break;


		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	
		default :
			break;
	}
	
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
