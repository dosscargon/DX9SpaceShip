#pragma once

#include <windows.h>

class Window {
public:
	//ウィンドウ作成
	static bool CreateGameWindow(const TCHAR* pName, int x, int y, int width, int height);
	//メッセージの更新
	static bool UpdateWindowMessage(void);
	//ウィンドウハンドル
	static HWND GetWindowHandle(void);
	//終了通知が来ているか
	static bool IsQuitMessage(void);

private:
	//ウインドウプロシージャー
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
	//ウィンドウハンドル
	static HWND g_hWnd;
	//終了通知が来ているか
	static bool g_isQuitMessage;
};