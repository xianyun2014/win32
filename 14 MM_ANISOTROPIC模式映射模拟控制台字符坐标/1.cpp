#include<windows.h>

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
	SIZE lp;
	TEXTMETRIC tm;
	static POINT apt[4];
	static int cxClient, cyClient, cxChar, cyChar;
	char szBuffer[30];

	switch(message)
	{
	case WM_CREATE:
		hdc = GetDC (hwnd);
		GetTextMetrics (hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC (hwnd, hdc);

		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		return 0;

	case WM_PAINT:

		hdc = BeginPaint (hwnd, &ps) ;
		
		/*�໭�ʣ��޻�ˢ*/
		SelectObject (hdc, GetStockObject (NULL_BRUSH));
		
		SetTextColor (hdc, RGB(0,0,255));


		/* MM_ANISOTROPIC ģʽӳ��ģ�����̨�ַ�����  ��߿��Բ�ͬ����*/
		
		SetMapMode (hdc, MM_ANISOTROPIC);     
		SetWindowExtEx (hdc, 1, 1, NULL);    //ÿӢ���߼���λ�ĸ���
		SetViewportExtEx (hdc, cxChar, -cyChar, NULL);  //ÿӢ������λ(����)�ĸ���
		SetViewportOrgEx (hdc, cxClient/2, cyClient/2, NULL);  //����ԭ��
		
		SetBkMode (hdc, TRANSPARENT);
		SelectObject (hdc, GetStockObject (BLACK_PEN));
		MoveToEx (hdc, 0, -cyClient / 2, NULL);
		LineTo (hdc, 0, cyClient / 2);

		MoveToEx (hdc, -cxClient / 2, 0, NULL);
		LineTo (hdc, cxClient / 2, 0);

		GetWindowExtEx (hdc, &lp);
		TextOut (hdc, 1, 1, szBuffer, wsprintf (szBuffer, ": %d*%d", lp.cx, lp.cy));
		
		GetViewportExtEx (hdc, &lp);
		TextOut (hdc, 1, 2, szBuffer, wsprintf (szBuffer, ": %d*%d", lp.cx, lp.cy));
		GetViewportExtEx (hdc, &lp);
		TextOut (hdc, 1, 3, szBuffer, wsprintf (szBuffer, ": %d*%d", lp.cx, lp.cy));
		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
