#include "Window.h"
#include "DirectX.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Input.h"
#include "Sound.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int width = 640;
	int height = 480;
	if (!Window::CreateGameWindow(TEXT("DirectX9"), 0, 0, width, height)) {
		return false;
	}

	//èâä˙âª
	DirectX::Initialize(Window::GetWindowHandle(), width, height, false);
	Sound::Initialize(Window::GetWindowHandle());
	Input::Initialize(hInstance, Window::GetWindowHandle());
	GameObject::Initialize();
	SceneManager::ChangeScene(new GameScene());

	//ÉãÅ[Év
	while (!Window::IsQuitMessage()) {
		if (!Window::UpdateWindowMessage()) {
			Input::Update();
			SceneManager::GetScene().Update();

			DirectX::GetDirect3DDevice().BeginScene();
			{
				DirectX::GetDirect3DDevice().Clear(0, NULL, 
					D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);

				SceneManager::GetScene().Render();
			}
			DirectX::GetDirect3DDevice().EndScene();
			DirectX::GetDirect3DDevice().Present(NULL, NULL, NULL, NULL);
		}
	}
	//èIóπèàóù
	GameObject::Finalize();
	Input::Finalize();
	Sound::Finalize();
	DirectX::Finalize();

	return 0;
}
