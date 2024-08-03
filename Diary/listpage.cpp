#include <format>
#include "framework.h"
#include "listpage.h"
#include "dialog.h"
#include "displayutils.h"
#include "utils.h"
#include "StringConvert.h"

#include "KLog.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    using namespace fkkt::listpage;

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, listTitleString, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DIARY, listWindowClass, MAX_LOADSTRING);
    RegisterClass(hInstance);

    if (!InitWindow(hInstance, nCmdShow))
    {
        return false;
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

namespace fkkt
{
    namespace listpage
    {
        ATOM RegisterClass(HINSTANCE hInstance)
        {
            WNDCLASSEXW wcex;

            wcex.cbSize = sizeof(WNDCLASSEX);

            wcex.style         = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc   = ListWndProc;
            wcex.cbClsExtra    = 0;
            wcex.cbWndExtra    = 0;
            wcex.hInstance     = hInstance;
            wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIARY));
            wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
            wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszMenuName  = MAKEINTRESOURCEW(IDM_LIST_MENU);
            wcex.lpszClassName = listWindowClass;
            wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

            return RegisterClassExW(&wcex);
        }

        BOOL InitWindow(HINSTANCE hInstance, int nCmdShow)
        {
            listPageInstance = hInstance; // 将实例句柄存储在全局变量中

            Window window =
                CreateWindowW(listWindowClass, listTitleString, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
            if (!window)
            {
                listDialog->showMsg("Failed to create window!", "Error");
                return false;
            }

            ShowWindow(window, nCmdShow);
            UpdateWindow(window);

            return true;
        }

        LRESULT CALLBACK ListWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
            case WM_CREATE:
            {
                auto      screenWidth  = GetSystemMetrics(SM_CXSCREEN);
                auto      screenHeight = GetSystemMetrics(SM_CYSCREEN);
                HINSTANCE hInstance    = GetModuleHandle(NULL);
                // 创建列表视图控件
                listView = CreateWindowEx(
                    WS_EX_CLIENTEDGE,
                    TEXT("SysListView32"),
                    nullptr,
                    WS_VISIBLE | WS_CHILD | LVS_REPORT,
                    0,
                    0,
                    screenWidth,
                    screenHeight,
                    hWnd,
                    HMENU(IDM_LIST_MENU),
                    hInstance,
                    0);

                // 添加列头
                RECT rect;
                GetClientRect(listView, &rect);

                LVCOLUMN lvColumn = { 0 };
                lvColumn.mask     = LVCF_TEXT | LVCF_WIDTH;
                lvColumn.pszText  = StringW("日期");
                lvColumn.cx       = 157;
                SendMessage(listView, LVM_INSERTCOLUMN, 0, (LPARAM)&lvColumn);

                lvColumn         = { 1 };
                lvColumn.mask    = LVCF_TEXT | LVCF_WIDTH;
                lvColumn.pszText = StringW("简介");
                lvColumn.cx      = 157;
                SendMessage(listView, LVM_INSERTCOLUMN, 0, (LPARAM)&lvColumn);

                // 添加列表项
                for (int i = 31; i > 1; i--)
                {
                    LVITEM lvItem  = { 0 };
                    lvItem.mask    = LVIF_TEXT;
                    lvItem.pszText = StringW(std::format("2023年3月{}日", i).c_str());
                    SendMessage(listView, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
                    KLog::out("123");
                }

                ListView_SetExtendedListViewStyle(listView, LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);

                break;
            }
            case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);
                switch (wmId)
                {
                case IDM_NEW: break;
                case IDM_SAVE: listDialog->showMsg("已保存"); break;
                case IDM_ABOUT: DialogBox(listPageInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, ShowListAbout); break;
                case IDM_EXIT: DestroyWindow(hWnd); break;
                default: return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
            break;
            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC         hdc = BeginPaint(hWnd, &ps);
                // TODO: 在此处添加使用 hdc 的任何绘图代码...
                fkkt::DisplayUtils::updateWidgetSize(listView);
                EndPaint(hWnd, &ps);
            }
            break;
            case WM_NOTIFY: onListItemClicked(hWnd, lParam); break;
            case WM_DESTROY: PostQuitMessage(0); break;
            default: return DefWindowProc(hWnd, message, wParam, lParam);
            }
            return 0;
        }

        void InitListAboutDialog(Window &window)
        {
            // sqlite3pp::database db("test.db");
            // db.execute("INSERT INTO contacts (name, phone) VALUES ('Mike', '555-1234')");
            const char *buildDateTime  = __DATE__ " " __TIME__;
            const char *sqlite3Version = g_DBManager.getSqlite3Version();
            // const int   tableSize      = g_DBManager.getRecordSize();
            String msg("");
            msg.append("软件版本:1.0.1");
            msg.append("\n");
            msg.append("数据库版本:");
            msg.append(sqlite3Version);
            msg.append("\n");
            msg.append("编译时间:");
            msg.append(buildDateTime);
            msg.append("\n");
            msg.append("数据库记录:");
            // msg.append(std::to_string(tableSize));
            msg.append("\n");
            msg.append("版权所有 Coder-CC");
            Widget aboutTextView = GetDlgItem(window, IDD_ABOUT_TEXT);
            SetWindowText(aboutTextView, StringW(msg));
        }

        INT_PTR CALLBACK ShowListAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
        {
            UNREFERENCED_PARAMETER(lParam);
            switch (message)
            {
            case WM_INITDIALOG: InitListAboutDialog(hDlg); return (INT_PTR) true;

            case WM_COMMAND:
                if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
                {
                    EndDialog(hDlg, LOWORD(wParam));
                    return (INT_PTR) true;
                }
                break;
            }
            return (INT_PTR) false;
        }

        void onListItemClicked(const HWND &hWnd, const LPARAM &lParam)
        {
            NMHDR *pNMHDR = (NMHDR *)lParam;
            if (pNMHDR->code == NM_CLICK)
            {
                // 列表视图被点击
                NMITEMACTIVATE *pItemClick = (NMITEMACTIVATE *)lParam;
                int             itemIndex  = pItemClick->iItem;
                // MessageBox(hWnd,
                //	StringW(std::format("list {} was clicked", itemIndex).c_str()),
                //	L"Click Event",
                //	MB_OK
                //);
            }
        }
    } // namespace listpage
} // namespace fkkt