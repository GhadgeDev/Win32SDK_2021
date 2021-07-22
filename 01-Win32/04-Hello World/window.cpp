/*Hello world*/
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
	TCHAR str1[] = TEXT("India Pledge\n");
	TCHAR para1[] = TEXT("\nIndia is my country.\nAll Indians are my brothers and sisters.\nI love my country and I am proud of its rich and varied heritage.\nI shall always strive to be worthy of it.\nI shall pay respect to my parents, teachers and all elders, and treat everyone with courtesy.\nTo my country and my people, I pledge my devotion.\nIn their well being, prosperity alone, and lies my happiness.");
	TCHAR para2[] = TEXT("\nभारत माझा देश आहे ।\nसारे भारतीय माझे बांधव आहेत ।\nमाझ्या देशावर माझे प्रेम आहे ।\nमाझ्या देशातल्या समृद्ध आणि विविधतेने नटलेल्या परंपरांचा मला अभिमान आहे ।\nत्या परंपरांचा पाईक होण्याची पात्रता माझ्या अंगी यावी म्हणून मी सदैव प्रयत्न करीन ।\nमी माझ्या पालकांचा, गुरुजनांचा आणि वडीलधार्‍या माणसांचा मान ठेवीन आणि प्रत्येकाशी सौजन्याने वागेन ।\nमाझा देश आणि माझे देशबांधव यांच्याशी निष्ठा राखण्याची मी प्रतिज्ञा करीत आहे ।\nत्यांचे कल्याण आणि त्यांची समृद्धी ह्यांतच माझे सौख्य सामावले आहे ।\n");
	TCHAR para3[] = TEXT("\nभारत हमारा देश है ।\nहम सब भारत वासी भाई - बहन है ।\nहमें अपना देश प्राण से भी प्यारा है ।\nइसकी समृद्धि और विविध संस्कृति पर हमें गर्व है ।\nहम इसके सुयोग्य अधिकारी बनने का सदा प्रयत्न करते रहेंगे ।\nहम अपने माता - पिता, शिक्षको और गुरुजनों का सदा आदर करेंगे ।\nतथा सबके साथ शिष्टता का व्यवहार करेंगे।\nहम अपने देश और देशवासियों के प्रति वफादार रहने की प्रतिज्ञा करते है ।\nउनके कल्याण और समृद्धि में ही हमारा सुख निहित है ।\n");

	switch (iMsg)
	{
	case WM_PAINT:
		GetClientRect(hwnd,&rc);
		hdc = BeginPaint(hwnd,&ps);
		SetBkColor(hdc, RGB(0,0,0));

		SetTextColor(hdc, RGB(199, 97, 0));
		DrawText(hdc, para2, -1, &rc, DT_VCENTER|DT_LEFT);

		SetTextColor(hdc,RGB(255,255,255));
		DrawText(hdc,para1,-1,&rc,DT_CENTER|DT_VCENTER);
		
		SetTextColor(hdc, RGB(0, 255, 0));
		DrawText(hdc,para3,-1,&rc,DT_VCENTER|DT_RIGHT);
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
