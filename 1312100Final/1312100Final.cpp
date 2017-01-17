//1312100Final.cpp : Defines the entry point for the application.
#include "stdafx.h"
#include "1312100Final.h"
#include <shellapi.h>
#define MAX_LOADSTRING 100
#define	WM_USER_SHELLICON WM_USER + 1
// Global Variables:
HMENU hPopMenu;
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
BOOL bDisable = FALSE;
PTSTR pszCurDir;

INT_PTR CALLBACK Dialog1_WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
NOTIFYICONDATA nidApp = {
};
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1312100FINAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1312100FINAL));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1312100FINAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1312100FINAL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HICON hMainIcon;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   hMainIcon = LoadIcon(hInstance, (LPCTSTR)MAKEINTRESOURCE(IDI_ICON1));
   nidApp.uVersion = NOTIFYICON_VERSION_4;
   nidApp.cbSize = sizeof(NOTIFYICONDATA);
   nidApp.hWnd = (HWND)hWnd;
   nidApp.uID = IDI_ICON1;
   nidApp.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
   nidApp.hIcon = hMainIcon;
   nidApp.uCallbackMessage = WM_USER_SHELLICON;
   LoadString(hInstance, NULL, nidApp.szTip, MAX_LOADSTRING);
   Shell_NotifyIcon(NIM_ADD, &nidApp);

   //ShowWindow(hWnd, nCmdShow);
  // UpdateWindow(hWnd);

   return TRUE;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmEvent;
	POINT lpClickPoint;
    switch (message)
    {
	case WM_USER_SHELLICON:
		//systray msg callback
		switch (LOWORD(lParam))
		{
		case WM_RBUTTONDOWN:
			UINT uFlag = MF_BYPOSITION | MF_STRING;
			GetCursorPos(&lpClickPoint);
			hPopMenu = CreatePopupMenu();
			if (bDisable == TRUE)
			{
				uFlag |= MF_GRAYED;
			}
			InsertMenu(hPopMenu, 0xFFFFFFFF, uFlag, ID_MENU_VIEWNOTE, _T("Test 2")); // Test 2
			InsertMenu(hPopMenu, 0xFFFFFFFF, uFlag, ID_MENU_VIEWSTATISTICS, _T("Test 1")); // Test 1				
			InsertMenu(hPopMenu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, IDM_EXIT, _T("Exit"));

			SetForegroundWindow(hWnd);
			TrackPopupMenu(hPopMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, lpClickPoint.x, lpClickPoint.y, 0, hWnd, NULL);
			return TRUE;

		}
		break;
    case WM_COMMAND:
        {
		wmEvent = HIWORD(wParam);
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_MENU_VIEWNOTE:
			//MessageBox(NULL, _T("This is a test for menu view note"), _T("Test 1"), MB_OK);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, Dialog1_WndProc);
			break;
		case ID_MENU_VIEWSTATISTICS:
			MessageBox(NULL, _T("This is a test for menu statistics"), _T("Test 2"), MB_OK);
			break;
		case IDM_EXIT:
			Shell_NotifyIcon(NIM_DELETE, &nidApp);
            DestroyWindow(hWnd);
			break;}
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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

//code xu ly hop thoai xuat hien khi nhap chon menu test 2.
//hien thi cac file trong thu muc notestored
//su dung kien thuc listview
INT_PTR CALLBACK Dialog1_WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	TCHAR achBuffer[MAX_PATH];
	switch (message)
	{
	case WM_INITDIALOG:
		pszCurDir = achBuffer;
		GetCurrentDirectory(MAX_PATH, pszCurDir);
		wcscat(pszCurDir, L"NoteStored");
		CreateDirectory(pszCurDir, 0);
		wcscat(pszCurDir, L"\\");
		//DlgDirList(hDlg, achBuffer, IDC_LIST1, 0, DDL_ARCHIVE | DDL_DIRECTORY);
		return FALSE;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDOK: {
			EndDialog(hDlg, TRUE);
		}
						  break;
		}
	}
					 break;
	case WM_DESTROY: {
		EndDialog(hDlg, TRUE);
		return TRUE;
	}
					 break;
	}
	return FALSE;
}