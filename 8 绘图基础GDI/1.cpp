#include<windows.h>
#include<math.h>
#define NUM 1000
#define TWOPI 2*3.1415
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

	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);	
		DispatchMessage(&msg);	
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	TEXTMETRIC tm;	
	TCHAR szBuffer[40];
	POINT apt[NUM];
	static int cxChar, cyChar, cxCaps, cxClient, cyClient, cxScreen, cyScreen, iMaxWidth;
	
	int x, y, i;

	switch(message)
	{
	case WM_CREATE:
		//��ȡϵͳ����Ŀ�Ⱥ͸߶�
		hdc = GetDC (hwnd);		//��ȡ�ͻ������

		GetTextMetrics (hdc, &tm);		//��ȡ�ı��ߴ�
		cxChar = tm.tmAveCharWidth;			//ƽ���ַ����
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3:2) * cxChar/2;  //��д��ĸƽ����ȣ��ȿ��������cxChar���������Ϊ��1.5��
		cyChar = tm.tmHeight + tm.tmExternalLeading;	//�ַ��߶�+������
	
		ReleaseDC (hwnd, hdc);	//�ͷ��豸�������

		iMaxWidth =  40 * cxChar + 20 * cxCaps;
		
		cxScreen = GetSystemMetrics(SM_CXSCREEN);
		cyScreen = GetSystemMetrics(SM_CYSCREEN);
		
		DeleteDC(hdc);
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		MoveToEx (hdc, 0, cyClient / 2, NULL);
		LineTo (hdc, cxClient, cyClient / 2);
		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i*cxClient / NUM;
			apt[i].y = (int) (cyClient/2 * (1 - sin(TWOPI * i/NUM)));
		}
		Rectangle (hdc, 11,11,20,20);
		
		RoundRect (hdc, 50,50,80,70,4,12);
		Polyline (hdc, apt, NUM);
		Pie (hdc, 100,100,170,150,190,100,80,125);
		
		DeleteDC (hdc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
