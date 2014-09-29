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
	POINT pt;
	static POINT apt[4];
	static int cxClient, cyClient;
	char szBuffer[30];

	switch(message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:

		hdc = BeginPaint (hwnd, &ps) ;
		
		/*�໭�ʣ��޻�ˢ*/
		SelectObject (hdc, CreatePen(PS_SOLID, 0, RGB(0,255,255)));
		SelectObject (hdc, GetStockObject (NULL_BRUSH));
		
		SetTextColor (hdc, RGB(0,0,255));
		/*��һ�����÷���*/
		
		SetViewportOrgEx (hdc, cxClient / 2, cyClient / 2, NULL);  //�豸��ӳ�䵽�߼���
		
		GetViewportOrgEx (hdc, &pt);
		TextOut (hdc, 0, 0, szBuffer, wsprintf (szBuffer, "����ԭ�� %d,%d", pt.x, pt.y));
		MoveToEx (hdc, -cxClient / 2, 0, NULL);
		LineTo (hdc, cxClient / 2, 0);
		
		MoveToEx (hdc, 0, cyClient / 2, NULL);
		LineTo (hdc, 0, -cyClient / 2);

		Ellipse(hdc, 0, 0, 100, 100);

		/*�ڶ������÷���*/
		SetWindowOrgEx (hdc, -120, -120 , NULL); //���õ��߼���ӳ�䵽�豸��(0,0)

		GetWindowOrgEx (hdc, &pt);
		TextOut (hdc, 0, 0, szBuffer, wsprintf (szBuffer, "����ԭ�� %d,%d,  %d", pt.x, pt.y, GetDeviceCaps(hdc, HORZSIZE)));
		MoveToEx (hdc, -cxClient / 2, 0, NULL);
		LineTo (hdc, cxClient / 2, 0);
		
		MoveToEx (hdc, 0, cyClient / 2, NULL);
		LineTo (hdc, 0, -cyClient / 2);

		Ellipse(hdc, 0, 0, 100, 100);

		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
