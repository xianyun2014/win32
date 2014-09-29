#include<windows.h>
#include<math.h>
#define TWO_PI (2.0 * 3.14159)
void DrawLine(HWND hwnd);	
 int cxClient, cyClient;
 HRGN hRgnClip;
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
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);	
			DispatchMessage(&msg);	
		}
		else 
			DrawLine(hwnd);
	}

	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	HRGN hRgnTemp[6];
	HCURSOR  hCursor;
	int i;
	

	switch(message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		hCursor = SetCursor (LoadCursor (NULL, IDC_WAIT));
		ShowCursor (FALSE);
		
		if (hRgnClip)
			DeleteObject (hRgnClip);
		hRgnTemp[0] = CreateEllipticRgn (0, cyClient / 3, cxClient / 2, 2 * cyClient / 3);
		hRgnTemp[1] = CreateEllipticRgn (cxClient / 2, cyClient / 3, cxClient, 2* cyClient / 3);
		hRgnTemp[2] = CreateEllipticRgn (cxClient / 3, 0, 2 * cxClient / 3, cyClient / 2);
		hRgnTemp[3] = CreateEllipticRgn (cxClient / 3, cyClient / 2, 2 * cxClient / 3, cyClient);

		hRgnTemp[4] = CreateRectRgn (0, 0, 1, 1);
		hRgnTemp[5] = CreateRectRgn (0, 0, 1, 1);
		hRgnClip = CreateRectRgn (0, 0, 1, 1);

		CombineRgn (hRgnTemp[4], hRgnTemp[0], hRgnTemp[1], RGN_OR);
		CombineRgn (hRgnTemp[5], hRgnTemp[2], hRgnTemp[3], RGN_OR);
		CombineRgn (hRgnClip, hRgnTemp[4], hRgnTemp[5], RGN_XOR);

		for (i = 0; i < 6; i++)
			DeleteObject (hRgnTemp[i]);
		SetCursor (hCursor);
		ShowCursor (TRUE);

		return 0;

	case WM_DESTROY:
		DeleteObject (hRgnClip);
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}

void DrawLine (HWND hwnd)
{
	double fAngle, fRadius;
	HDC hdc;
	hdc = GetDC(hwnd) ;
	static ix = 0, iy = 0, num = 0;

	SelectClipRgn (hdc, hRgnClip);
	/*
	InvalidateRect (hwnd, NULL, TRUE);
	

	if (ix < cxClient && iy <= 0)
		num = 0;
	else if (ix >= cxClient && iy < cyClient)
		num = 1;
	else if (ix >= 0 && iy >= cyClient)
		num = 2;
	else 
		num = 3;

	switch (num)
	{
	case 0:
		SetViewportOrgEx (hdc, ix++, 0, NULL);
		break;
	case 1:
		SetViewportOrgEx (hdc, ix, iy++, NULL);
		break;
	case 2:
		SetViewportOrgEx (hdc, ix--, iy, NULL);
		break;
	case 3:
		SetViewportOrgEx (hdc, ix, iy--, NULL);
		break;
	default:
		ix = 0;
		iy = 0;
		num = 0;
	}
	*/
	fRadius = _hypot (cxClient , cyClient );

	ix+=10;
	SelectObject(hdc, GetStockObject(WHITE_PEN));		
	for (fAngle = 0.0; fAngle < TWO_PI ; fAngle += TWO_PI / 100)
	{
		MoveToEx (hdc, ix-10, 0, NULL);
		
		LineTo (hdc, (int) (fRadius * cos (fAngle) + 0.5),
					(int) (-fRadius * sin (fAngle) + 0.5));
	}

	SelectObject(hdc, GetStockObject(BLACK_PEN));
	for (fAngle = 0.0; fAngle < TWO_PI ; fAngle += TWO_PI / 100)
	{
		MoveToEx (hdc, ix, 0, NULL);

		LineTo (hdc, (int) (fRadius * cos (fAngle) + 0.5),
					(int) (-fRadius * sin (fAngle) + 0.5));
	}

	ReleaseDC (hwnd , hdc);
	Sleep(20);

}