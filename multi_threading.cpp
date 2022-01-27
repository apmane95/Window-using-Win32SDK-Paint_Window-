#include<windows.h>
#include<tchar.h>

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")

//global functions declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


DWORD WINAPI ThreadProcOne(LPVOID);

DWORD WINAPI ThreadProcTwo(LPVOID);

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
	static HANDLE hThread1=NULL;
	static HANDLE hThread2=NULL;


	//code
	switch (iMsg)
	{
		case WM_CREATE:
			hThread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProcOne,(LPVOID)hwnd,0,NULL);
			//error checking should be done
			hThread2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProcTwo,(LPVOID)hwnd,0,NULL);
			//error checking should be done for thread
			break;
		case WM_LBUTTONDOWN:

				MessageBox(hwnd,TEXT("im thread number 4"),TEXT("thread message"),MB_OK);
				
				break;
		case WM_DESTROY:
			CloseHandle(hThread1);
			CloseHandle(hThread2);
		PostQuitMessage(0);
		break;
	 
	 
	default:
		break;

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));//default Window proc

}

DWORD WINAPI ThreadProcOne(LPVOID param)
{  
	
	//variable declarations
	HDC hdc = NULL;
	TCHAR str[256];
	long i;

	//code
	hdc=GetDC((HWND)param);
	 SetBkColor(hdc,RGB(0,0,0));
	 SetTextColor(hdc,RGB(0,255,0));

	 for(i=0;i<2147483647;i++)
	 {
	 	wsprintf(str,TEXT("incrementing order=%ld"),i);
	 	TextOut(hdc,5,5,str,(int)_tcslen(str));


	 }

	 ReleaseDC((HWND)param,(HDC)hdc);
	 return 0;

}
DWORD WINAPI ThreadProcTwo(LPVOID param)
{

//variable declarations
	HDC hdc = NULL;
	TCHAR str[256];
	long i;

	//code
	hdc=GetDC((HWND)param);
	 SetBkColor(hdc,RGB(0,0,0));
	 SetTextColor(hdc,RGB(255,0,0));

	 for(i=2147483647;i>0;i--)
	 {
	 	wsprintf(str,TEXT("decrementing order=%ld"),i);
	 	TextOut(hdc,5,25,str,(int)_tcslen(str));


	 }

	 ReleaseDC((HWND)param,(HDC)hdc);
	 return 0;

}