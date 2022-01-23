#include <windows.h>
#include <iostream>

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
int wmain(int argc, wchar_t* argv[])
{
	// 设置控制台的中文显示
	setlocale(LC_ALL, "chs");

	int width = 1024;
	int height = 720;
	HINSTANCE hInstance;
	hInstance = GetModuleHandle(NULL);
	WNDCLASS wndClass{};
	// 设置应用图标
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.lpfnWndProc = WindowProc;
	// 设置类名字
	wndClass.lpszClassName = L"SGE";
	wndClass.hInstance = hInstance;
	// 指定唯一一个style
	wndClass.style = CS_OWNDC;

	// 注册
	RegisterClass(&wndClass);

	HWND hwnd = CreateWindow(
		L"SGE",							// 类名
		L"The Seed Game Engine",		// 窗口名
		WS_OVERLAPPED  | WS_SYSMENU  | WS_MINIMIZEBOX  | WS_VISIBLE,
		38,
		20,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (FAILED(hwnd))
	{
		std::wcout << L"创建窗口出错！" << std::endl;
		throw;
		return  0;
	}

	MSG msg;
	while (true)
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return 0;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(300);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}