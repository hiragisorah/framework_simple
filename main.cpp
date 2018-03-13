// フレームワーク
#include <framework\game.h>

// システム
#include <system\window.h>
#include <system\direct3d11.h>

// 標準ライブラリ
#include <crtdbg.h>

#ifdef _DEBUG
void main(void)
{
	{// メモリーリーク検出
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int)
{
#endif

	{// システムの追加
		Game::AddSystem<System::Window>();
		Game::AddSystem<System::Direct3D11>();
	}

	{// ロード

	}

	{// 初期設定

	}

	{// 起動
		Game::Run();
	}
}