// フレームワーク
#include <framework\game.h>

// システム
#include <system\window.h>
#include <system\direct3d11.h>
#include <system\scene_manager.h>
#include <system\camera.h>
#include <system\database.h>

// データ
#include <data\blend.h>
#include <data\rasterizer.h>
#include <data\sampler.h>
#include <data\shader.h>
#include <data\vertex.h>
#include <data\index.h>

// シーン
#include <scene\title.h>

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
		Game::AddSystem<System::SceneManager>();
		Game::AddSystem<System::Camera>();
		Game::AddSystem<System::Database<IBlend>>();
		Game::AddSystem<System::Database<IRasterizer>>();
		Game::AddSystem<System::Database<ISampler>>();
		Game::AddSystem<System::Database<IShader>>();
		Game::AddSystem<System::Database<IVertex>>();
		Game::AddSystem<System::Database<IIndex>>();
	}

	{// ロード
		Game::GetSystem<System::Database<IBlend>>()->Load<Blend::Alpha>();
		Game::GetSystem<System::Database<IRasterizer>>()->Load<Rasterizer::CullNoneFillSolid>();
		Game::GetSystem<System::Database<IShader>>()->Load<Shader::Default2D>();
		Game::GetSystem<System::Database<IShader>>()->Load<Shader::Default3D>();
		Game::GetSystem<System::Database<IShader>>()->Load<Shader::Shadow>();
		Game::GetSystem<System::Database<IVertex>>()->Load<Vertex::Point>();
		Game::GetSystem<System::Database<IVertex>>()->Load<Vertex::Line>();
		Game::GetSystem<System::Database<IVertex>>()->Load<Vertex::Triangle>();
		Game::GetSystem<System::Database<IVertex>>()->Load<Vertex::Quad>();
		Game::GetSystem<System::Database<IVertex>>()->Load<Vertex::QuadNormal>();
	}

	{// 初期設定
		Game::GetSystem<System::SceneManager>()->ChangeScene<Scene::Title>();
	}

	{// 起動
		Game::Run();
	}
}