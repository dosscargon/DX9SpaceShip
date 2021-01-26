#pragma once

#include <windows.h>

class Window {
public:
	//�E�B���h�E�쐬
	static bool CreateGameWindow(const TCHAR* pName, int x, int y, int width, int height);
	//���b�Z�[�W�̍X�V
	static bool UpdateWindowMessage(void);
	//�E�B���h�E�n���h��
	static HWND GetWindowHandle(void);
	//�I���ʒm�����Ă��邩
	static bool IsQuitMessage(void);

private:
	//�E�C���h�E�v���V�[�W���[
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
	//�E�B���h�E�n���h��
	static HWND g_hWnd;
	//�I���ʒm�����Ă��邩
	static bool g_isQuitMessage;
};