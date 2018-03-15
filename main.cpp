// �t���[�����[�N
#include <framework\game.h>

// �V�X�e��
#include <system\window.h>
#include <system\direct3d11.h>
#include <system\scene_manager.h>
#include <system\camera.h>
#include <system\database.h>

// �f�[�^
#include <data\blend.h>
#include <data\rasterizer.h>
#include <data\sampler.h>
#include <data\shader.h>
#include <data\vertex.h>
#include <data\index.h>

// �V�[��
#include <scene\title.h>

// �W�����C�u����
#include <crtdbg.h>

#ifdef _DEBUG
void main(void)
{
	{// �������[���[�N���o
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int)
{
#endif

	{// �V�X�e���̒ǉ�
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

	{// ���[�h
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

	{// �����ݒ�
		Game::GetSystem<System::SceneManager>()->ChangeScene<Scene::Title>();
	}

	{// �N��
		Game::Run();
	}
}