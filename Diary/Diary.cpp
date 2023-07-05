#include "framework.h"
#include "Diary.h"
#include "dialog.h"
#include "displayutils.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, appTitleString, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DIARY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIARY));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM InitMyClass(HINSTANCE hInstance) {

	return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIARY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DIARY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	handleInstance = hInstance; // 将实例句柄存储在全局变量中

	Window window = CreateWindowW(szWindowClass, appTitleString, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!window)
	{
		dialog->showMsg(L"Failed to create window!", L"Error");
		return false;
	}

	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
		auto screenHeight = GetSystemMetrics(SM_CYSCREEN);
		HINSTANCE hInstance = GetModuleHandle(NULL);
		editBox = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
			WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL,
			0, 0,
			screenWidth, /* Width */
			screenHeight, /* Height */
			hWnd, /* Parent Window */
			(HMENU)ID_MAIN_EDIT_BOX, hInstance, nullptr);
		if (!editBox)
		{
			dialog->showMsg(L"Failed to create edit control!", L"Error");
			return false;
		}
		SetFont(editBox, 20, 0, L"Microsoft Yahei");
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_NEW:
			SendMessage(editBox, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(L""));
			break;
		case IDM_SAVE:
			dialog->showMsg(L"已保存");
			break;
		case IDM_ABOUT:
			DialogBox(handleInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_MAIN_EDIT_BOX:
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				SendMessage((HWND)lParam, EM_SETSEL, 0, -1);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		fkkt::DisplayUtils::setWidgetSize(editBox);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT SetFont(const Widget& cWidget, const int cHeight, const int cWidth, const LPCWSTR fontName, const int cEscapement, const int cOrientation, const int cWeight, const DWORD bItalic, const DWORD bUnderline, const DWORD bStrikeOut)
{
	HFONT font = CreateFont(
		cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		fontName);
	if (!font)
	{
		dialog->showMsg(L"Can't create font,use default fonts!", L"Warning");
		return 1;
	}
	SendMessage(cWidget, WM_SETFONT, reinterpret_cast<WPARAM>(font), true);
	return 0;
}
