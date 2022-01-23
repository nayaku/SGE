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
	// ���ÿ���̨��������ʾ
	setlocale(LC_ALL, "chs");

	int width = 1024;
	int height = 720;
	HINSTANCE hInstance;
	hInstance = GetModuleHandle(NULL);
	WNDCLASS wndClass{};
	// ����Ӧ��ͼ��
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.lpfnWndProc = WindowProc;
	// ����������
	wndClass.lpszClassName = L"SGE";
	wndClass.hInstance = hInstance;
	// ָ��Ψһһ��style
	wndClass.style = CS_OWNDC;

	// ע��
	RegisterClass(&wndClass);

	HWND hwnd = CreateWindow(
		L"SGE",							// ����
		L"The Seed Game Engine",		// ������
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
		std::wcout << L"�������ڳ���" << std::endl;
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