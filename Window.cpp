#include<windows.h>


#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")

//global functions declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations


//entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow_ap");

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);



	RegisterClassEx(&wndclass);

	//create window in memory
	hwnd = CreateWindow(szAppName,
		TEXT("AP:MyFirstWindow"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, //x
		CW_USEDEFAULT,  //y
		CW_USEDEFAULT,   //width
		CW_USEDEFAULT,  //height
		NULL, //child window
		NULL, //user defined menu
		hInstance,  //instance of window
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);


	//Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//eg:if WM_LBUTTONDOWN on close window-translate
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	//variable declaration
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	TCHAR str[] = TEXT("anup");


	//code
	switch (iMsg)
	{
		case WM_PAINT:
				GetClientRect(hwnd,&rc);
				hdc = BeginPaint(hwnd,&ps);
				SetBkColor(hdc,RGB(0, 0, 0));
				SetTextColor(hdc,RGB(0,255,0));
				DrawText(hdc,str,-1,&rc,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				EndPaint(hwnd,&ps); 
				break;



	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	 
	default:
		break;

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));//default Window proc

}

