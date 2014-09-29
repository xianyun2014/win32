#include<windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	static TCHAR szAppName[] = TEXT("���ڳ���");
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
						"The Windows!",
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);
	
	ShowWindow(hwnd,nCmdShow);		//��ʾ����
	UpdateWindow(hwnd);		

	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);		//ת����Ϣ
		DispatchMessage(&msg);		//Ͷ����Ϣ
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	TEXTMETRIC tm;		//�ı���Ϣ�ṹ
	static int cxChar, cyChar;		//����ַ��ߴ���Ϣ
	int iLength;		//����ı�����
	TCHAR szBuffer [40];	
	switch(message)
	{
	case WM_CREATE:
		//��ȡϵͳ����Ŀ�Ⱥ͸߶�
		hdc = GetDC (hwnd);		//��ȡ�ͻ������
		GetTextMetrics (hdc, &tm);		//��ȡ�ı��ߴ�
		cxChar = tm.tmAveCharWidth;			//ƽ���ַ����
		cyChar = tm.tmHeight + tm.tmExternalLeading;	//�ַ��߶�+������
		ReleaseDC (hwnd, hdc);	//�ͷ��豸�������
		//���Ų��������ļ���project->setting->linkingģ���м���winmm.lib
		PlaySound (TEXT ("1.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		GetClientRect(hwnd,&rect);
		DrawText(hdc,TEXT("һЩʾ��"),-1, &rect, DT_CENTER);
		/* TextOut()��һ������ */
		TextOut(hdc,cxChar ,cyChar,TEXT("��һ��ʾ��"),sizeof(TEXT("��һ��ʾ��"))-1);
		/* TextOut()�ڶ������� */
		iLength = wsprintf (szBuffer, TEXT ("�ڶ���ʾ��%d+%d=%d"),1,2, 1+2);
		TextOut(hdc, cxChar, cyChar * 2, szBuffer, iLength);
		/* TextOut()���������� */
		TextOut(hdc, cxChar, cyChar * 3, szBuffer,
			wsprintf (szBuffer, TEXT ("������ʾ��%d+%d=%d"), 2, 4, 2+4));

		EndPaint(hwnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
