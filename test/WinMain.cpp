#include <Windows.h>

#include "WebUI1.h"

#pragma warning(disable: 4996)

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		if (SUCCEEDED(WebUI1_Initialize(hWnd)))
		{
			WebUI1_SetInterface(hWnd, L"Add",
				[](const wchar_t* arg, wchar_t* result, int length) -> unsigned int {
					if (wcscmp(arg, L"hello") == 0) {
						wcscpy(result, L"world");
					}
					else if (wcscmp(arg, L"world") == 0) {
						wcscpy(result, L"hello");
					}

					return S_OK;
				});
			WebUI1_Navigate(hWnd, L"res://test.exe/#23/#101");
		}
		SetTimer(hWnd, 1, 3000, nullptr);
		return 0;
	case WM_TIMER:
		KillTimer(hWnd, 1);
		WebUI1_SendEvent(hWnd, L"event1", L"\"event1 triggered!\"");
		return 0;
	case WM_SIZE:
		WebUI1_Resize(hWnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_DESTROY:
		WebUI1_Finalize(hWnd);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pszCmdLine, _In_ int nCmdShow)
{
	HRESULT hr = OleInitialize(nullptr);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"OleInitialize Failed", L"Error", MB_OK);
		return 0;
	}

	WNDCLASS wc = { 0 };
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = &WndProc;
	wc.lpszClassName = L"win32-simple-webui_test";
	wc.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&wc);

	HWND hWnd = CreateWindow(
		L"win32-simple-webui_test",
		L"win32-simple-webui_test",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		nullptr);

	ShowWindow(hWnd, nCmdShow);

	MSG msg = { 0 };
	while (static_cast<int>(GetMessage(&msg, NULL, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	OleUninitialize();
	return static_cast<int>(msg.wParam);
}