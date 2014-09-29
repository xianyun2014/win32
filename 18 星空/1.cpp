#include<windows.h>
#include<stdio.h>
const int StarNum = 300;

void DrawStar (HWND hwnd);
int cxClient, cyClient;
short arr[StarNum][3];
HDC hdc;
static int num= 0;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	static TCHAR szAppName[] = TEXT("wndclass by lxy");
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	wndclass;
	//�������ʼ��
	wndclass.style			= CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.hCursor		= LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hInstance		= hInstance;
	wndclass.lpszClassName	= szAppName;
	wndclass.lpszMenuName	= NULL;
	//ע�ᴰ����
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL,TEXT("���䴰����ʧ��!"),szAppName,MB_ICONERROR);
		return 0;
	}
	//��������
	hwnd = CreateWindow(szAppName,
						TEXT("��Ϣ��ʾ"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT,
						CW_USEDEFAULT, CW_USEDEFAULT,
						NULL, NULL, hInstance, NULL);
	
	ShowWindow(hwnd,nCmdShow);	
	UpdateWindow(hwnd);		
	
	while (TRUE)
	{
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			if ( msg.message == WM_QUIT)
				break;
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
		else
		{
			DrawStar(hwnd);
			
		}
	}

	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch(message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		int i;
		for (i = 0; i < StarNum; i++)
		{
			arr[i][0] = rand()%cxClient;
			arr[i][1] = rand()%cyClient;
			arr[i][2] = rand()%255;
		}
		return 0;
	case WM_DESTROY:
		
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}

void DrawStar (HWND hwnd)
{	
	int i;
	for (i = 0; i < StarNum; i++)
	{
		if (++arr[i][0] > cxClient)
		{
			arr[i][0] = rand()%cxClient/3;
			arr[i][1] = rand()%cyClient;
			arr[i][2] = rand()%255;
		}
	}

	hdc = GetDC (hwnd);

	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	Rectangle(hdc, 0, 0, cxClient, cyClient);
	SetBkMode(hdc, RGB(255,255,255));

	for (i = 0; i < StarNum; i++)
	{
		SetPixel(hdc, arr[i][0], arr[i][1], RGB(arr[i][2],arr[i][2],arr[i][2]));
	}
	ReleaseDC (hwnd, hdc);

	Sleep(10);

}

