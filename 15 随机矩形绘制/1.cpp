#include<windows.h>
void DrawRect (HWND hwnd);
int cxClient, cyClient;

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
			DrawRect(hwnd);
			
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
		return 0;

	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}

void DrawRect (HWND hwnd)
{
	RECT rect;
	HDC hdc;
	HBRUSH hBrush;
	char szBuffer[20];
	static long num = 0;
	int t;
	if (cxClient == 0 || cyClient == 0)
		return;
	t = rand()%cyClient;
	SetRect (&rect , 100, t, cxClient, t+100);
	//Sleep(10);

	hdc = GetDC (hwnd);
	hBrush = CreateSolidBrush (RGB(rand()%256, rand()%256, rand()%256));
	FillRect (hdc, &rect, hBrush);
	num++;
	TextOut (hdc, 0, 0, szBuffer, wsprintf (szBuffer, "�ѻ����"));
	TextOut (hdc, 0, 20, szBuffer, wsprintf (szBuffer, "%ld", num));
	ReleaseDC (hwnd, hdc);
	DeleteObject (hBrush);
}

