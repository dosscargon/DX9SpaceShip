#include "Window.h"

//�E�B���h�E�n���h��
HWND Window::g_hWnd = NULL;
//�I���ʒm�����Ă��邩
bool Window::g_isQuitMessage = false;

//�E�C���h�E�v���V�[�W���[
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
	switch (uiMsg) {
	//����ۂ�Window��j��
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	//�v���O�����̏I����ʒm
	case WM_DESTROY:	
		PostQuitMessage(0);
		return 0L;
	}
	//�f�t�H���g�̃v���V�[�W���Ăяo��
	return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

//�E�B���h�E�쐬
bool Window::CreateGameWindow(const TCHAR* pName, int x, int y, int width, int height) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = pName;
	wcex.hIcon = LoadIcon(NULL, IDC_ARROW);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassExW(&wcex);

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	RECT Rect;
	Rect.left = 0;
	Rect.top = 0;
	Rect.right = width;
	Rect.bottom = height;

	AdjustWindowRect(&Rect, dwStyle, false);

	width = Rect.right - Rect.left;
	height = Rect.bottom - Rect.top;

	//�E�C���h�E�쐬
	g_hWnd = CreateWindow(wcex.lpszClassName,
		pName,
		dwStyle,
		x,
		y,
		width,
		height,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);
	if (g_hWnd == NULL) {
		return false;
	}

	ShowWindow(g_hWnd, SW_SHOW);
	UpdateWindow(g_hWnd);

	return true;
}

//���b�Z�[�W�̍X�V
bool Window::UpdateWindowMessage(void) {
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			g_isQuitMessage = true;
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return true;
	}
	return false;
}

//�E�B���h�E�n���h��
bool Window::IsQuitMessage(void) { return g_isQuitMessage; }
//�I���ʒm�����Ă��邩
HWND Window::GetWindowHandle(void) { return g_hWnd; }