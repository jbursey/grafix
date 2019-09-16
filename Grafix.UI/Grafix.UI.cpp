// Grafix.UI.cpp : Defines the entry point for the application.
//

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

#include "framework.h"
#include "Grafix.UI.h"
#include "D3DRenderer.h"
#include "InputControls.h"
#include "GrafixConstants.h"
#include <GameTimer.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND g_handle;
GameTimer* g_timer = nullptr;
D3DRenderer* g_renderer = nullptr;
InputControls* g_controls = nullptr;
int g_width;
int g_height;

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
	g_timer = new GameTimer();
	g_renderer = new D3DRenderer();
	g_controls = new InputControls();
	g_width = 1000;
	g_height = 800;

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GRAFIXUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAFIXUI));

    MSG msg;

	// Main message loop:
	double fps = 0;
	double totalFrames = 0;
	double totalUpdates = 0;
	double frameDeltaTime = 0;
	double framesThisSecond = 0;
	double updatesThisSecond = 0;
	double dt = 0;
	double updateTime = 0;

	g_renderer->Init(g_handle, g_width, g_height);    
	g_timer->Start();
    while (true)
    {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}

		if (g_controls->IsKeyDown(VK_ESCAPE))
		{
			break;
		}

		/*
		it dt = 1000ms and the updates per second is 10, then we need to update every 100ms so in this case we are 10 updates behind
		*/		
		while (updateTime > GrafixConstants::MillisecondsPerUpdate)
		{
			g_renderer->Update(g_controls);
			updateTime -= GrafixConstants::MillisecondsPerUpdate;
			++totalUpdates;
			++updatesThisSecond;
		}
		g_renderer->Render();

		frameDeltaTime = g_timer->ElapsedTimeMS();		
		dt += frameDeltaTime;
		updateTime += frameDeltaTime;

		//--update metrics
		++framesThisSecond;
		++totalFrames;		
		
		if (dt >= 1000)
		{
			fps = framesThisSecond / (dt / 1000.0);
			updatesThisSecond = updatesThisSecond / (dt / 1000.0);

			dt = 0;
			framesThisSecond = 0;

			//--update window text
			std::wstring metrics = L"";
			metrics += L"DT: " + std::to_wstring(frameDeltaTime);
			metrics += L" FPS: " + std::to_wstring(fps);
			metrics += L" UPS: " + std::to_wstring(updatesThisSecond);
			metrics += L" Total Updates: " + std::to_wstring(totalUpdates);

			updatesThisSecond = 0;
			SetWindowText(g_handle, metrics.c_str());
		}
    }
	g_timer->Stop();
	
	delete g_timer;
	delete g_renderer;

    return (int) msg.wParam;
}



//
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAFIXUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GRAFIXUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   g_handle = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, g_width, g_height, nullptr, nullptr, hInstance, nullptr);

   if (!g_handle)
   {
      return FALSE;
   }

   ShowWindow(g_handle, nCmdShow);
   UpdateWindow(g_handle);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int stop = 0;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
		g_controls->SetKey((char)wParam, true);
		break;
	case WM_KEYUP:
		g_controls->SetKey((char)wParam, false);
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
