// Win32Project4.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32Project4.h"

#define MAX_LOADSTRING 100
#define BUFFER(x, y) *(pBuffer + y * cxBuffer + x)


// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT4));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT4));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT4);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // cxChar �ַ���ƽ�����
    // cyChar �ַ���ƽ���߶�
    // cxClient �ͻ����Ŀ��
    // cyClient �ͻ����ĸ߶�
    // cxBuffer ���ں�����󻺳���
    // cyBuffer ����������󻺳���
    // xCaret ���������ŵĺ�����
    // yCaret ���������ŵ�������
    static int cxChar, cyChar, cxClient, cyClient, cxBuffer, cyBuffer, xCaret, yCaret;
    // pBuffer �洢������Ļ�����ݵĻ�����
    static TCHAR *pBuffer = NULL;
    // �豸����
    HDC hdc;
    // x�Ǻ����������y�������꼼����i����ʱ����
    int x, y, i;
    // �����ͻ������Ƶ���Ϣ
    PAINTSTRUCT ps;
    // ��ǰ�豸�������������Ϣ
    TEXTMETRIC tm;
	HMENU hmenu;

    switch (message)
    {
		case WM_COMMAND:
			switch(LOWORD(wParam))
        {
		    case IDM_EXIT:
			DestroyWindow(hwnd);
			break;

		   default:
           return DefWindowProc(hwnd, message, wParam, lParam);
		   break;
        }
			
	
        break;
    // ���ڴ���ʱ�����������ƽ����Ⱥ͸߶�
    // �õ� cxChar �� cyChar ��ֵ
    case WM_CREATE:
        hdc = GetDC(hwnd);

        SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth;
        cyChar = tm.tmHeight;
        ReleaseDC(hwnd, hdc);

        // �˴�ľ�з��أ�ľ��break

    case WM_SIZE:
        // ��ÿͻ����Ŀ�Ⱥ͸߶�
        // �õ� cxClient �� cyClient ��ֵ
        if (message == WM_SIZE) {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
        }
        // ��ú�����󻺴�����������󻺴�����ֵ
        // �õ� cxBuffer �� cyBuffer
        cxBuffer = max(1, cxClient / cxChar);
        cyBuffer = max(1, cyClient / cyChar);

        // �����㹻�����ͻ�����ʾ���ַ��������Ŀռ�
        if (pBuffer != NULL) {
            free(pBuffer);
        }
        pBuffer = (TCHAR *)malloc(cxBuffer * cyBuffer * sizeof(TCHAR));

        // �������ַ��������Ŀռ���Ϊ���ַ�
        for (y = 0; y < cyBuffer; y++) {
            for (x = 0; x < cxBuffer; x++) {
                BUFFER(x, y) = ' ';
            }
        }

        // ���������ָ�����Ͻ�
        xCaret = 0;
        yCaret = 0;

        // �����ǰ���ڻ�������뽹�㣬���������뽹��
        if (hwnd == GetFocus()) {
            // ���뽹����ָ��λ��
            // λ������Ϊ (xCaret, yCaret)
            SetCaretPos(xCaret * cxChar, yCaret * cyChar);
        }

        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    // �������������������Ų�����ʾ
    case WM_SETFOCUS:
        CreateCaret(hwnd, NULL, cxChar, cyChar);
        SetCaretPos(xCaret * cxChar, yCaret * cyChar);
        ShowCaret(hwnd);
        return 0;

    // ���ز��ݻ�����������
    // ��������ز����Ǳ�Ҫ�ģ�ֻ���� ShowCaret() �� HideCaret()
    // ����һһ��Ӧ��ʱ�����������ŲŻ���ʾ����
    case WM_KILLFOCUS:
        HideCaret(hwnd);
        DestroyCaret();
        return 0;

    // ���������Ϣ
    case WM_KEYDOWN:
        switch (wParam)
        {
        // home��
        case VK_HOME:
            xCaret = 0;
            break;

        // end��
        case VK_END:
            xCaret = cxBuffer - 1;
            break;

        // pg up��
        case VK_PRIOR:
            yCaret = 0;
            break;

        // pg dn��
        case VK_NEXT:
            yCaret = cyBuffer - 1;
            break;

        // <-��
        case VK_LEFT:
            xCaret = max(xCaret - 1, 0);
            break;

        // ->��
        case VK_RIGHT:
            xCaret = min(xCaret + 1, cxBuffer - 1);
            break;

        // �ϼ�
        case VK_UP:
            yCaret = max(yCaret - 1, 0);
            break;

        // �¼�
        case VK_DOWN:
            yCaret = min(yCaret + 1, cyBuffer - 1);
            break;

        // del��
        case VK_DELETE:
            // Ҫɾ��ָ��λ�õ�һ���ַ�����Ҫ�Ѻ�����ַ�
            // һ��һ��Ų��ǰ��һ��λ���ϣ��ٽ����һ��λ��
            // ���ַ���Ϊ��

            for (x = xCaret; x < cxBuffer - 1; x++) {
                BUFFER(x, yCaret) = BUFFER(x + 1, yCaret);

            }
			
            BUFFER(cxBuffer - 1, yCaret) = ' ';
            HideCaret(hwnd);

            hdc = GetDC(hwnd);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
            TextOut(hdc, xCaret * cxChar, yCaret * cyChar, &BUFFER(xCaret, yCaret), cxBuffer - xCaret);
            ReleaseDC(hwnd, hdc);
            ShowCaret(hwnd);
            break;
        }

        SetCaretPos(xCaret * cxChar, yCaret * cyChar);
        return 0;

    // �����ַ���Ϣ
    case WM_CHAR: // lParam ��ʾ�ظ������� wParam ��ʾ�ַ�����
        for (i = 0; i < (int)LOWORD(lParam); i++) {
            switch (wParam)
            {
            // backspace��
            case '\b':
                if (xCaret > 0) {
                    xCaret--;
                    SendMessage(hwnd, WM_KEYDOWN, VK_DELETE, 1);
                }
                break;

            // tab��
            case '\t':
                do {
                    SendMessage(hwnd, WM_CHAR, ' ', 1);
                } while (xCaret % 8 != 0);
                break;

            // enter��
            case '\n':
                if (++yCaret == cyBuffer) {
                    yCaret = 0;
                }
                break;

            // enter��
            case '\r':
                xCaret = 0;
                if (++yCaret == cyBuffer) {
                    yCaret = 0;
                }
                break;

            // esc��
            case '\x1B': // ʮ�����Ƶ�1B����Ӧ��ASCII�ַ���ESC
                for (y = 0; y < cyBuffer; y++) {
                    for (x = 0; x < cxBuffer; x++) {
                        BUFFER(x, y) = ' ';
                    }
                }

                xCaret = 0;
                yCaret = 0;

                InvalidateRect(hwnd, NULL, FALSE);
                break;

            // ����û����µļ�λ
            default:
                BUFFER(xCaret, yCaret) = (TCHAR)wParam;

                HideCaret(hwnd);
                hdc = GetDC(hwnd);
                SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
                TextOut(hdc, xCaret * cxChar, yCaret * cyChar, &BUFFER(xCaret, yCaret), 1);
                ReleaseDC(hwnd, hdc);
                ShowCaret(hwnd);

                // ���������ˣ�����ת��һ�п�ͷ��ʾ
                if (++xCaret == cxBuffer) {
                    xCaret = 0;
                    if (++yCaret == cyBuffer) {
                        yCaret = 0;
                    }
                }
                break;
            }
            SetCaretPos(xCaret * cxChar, yCaret * cyChar);
            return 0;
        }

    // ��ʾ�����е���Ϣ��֮ǰ������ÿ��Ϊ��λ��ʾ��
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
        for (y = 0; y < cyBuffer; y++) {
            TextOut(hdc, 0, y * cyChar, &BUFFER(0, y), cxBuffer);
        }

        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}