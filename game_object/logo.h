#pragma once

// フレームワーク
#include <framework\entity.h>

// コンポーネント
#include <component\renderer\draw.h>

// システム
#include <system\camera.h>

// データ
#include <data\blend\alpha.h>
#include <data\rasterizer\cull_none_fill_solid.h>
#include <data\vertex\point.h>
#include <data\vertex\line.h>
#include <data\vertex\triangle.h>
#include <data\vertex\quad.h>
#include <data\vertex\quad_normal.h>
#include <data\shader\default2d.h>
#include <data\shader\default3d.h>
#include <data\shader\shadow.h>

namespace GameObject
{
	class Logo : public Entity
	{
	private:
		Component::Renderer::Draw * renderer_ = nullptr;
		Shader::Shadow::CB cb_;

	public:
		Logo(Entity * parent) : Entity(parent)
		{
			{// コンポーネント追加
				this->renderer_ = this->AddComponent<Component::Renderer::Draw>();
			}

			{// コンポーネント設定
				//this->renderer_->SetBlend<Blend::Alpha>();
				this->renderer_->SetRasterizer<Rasterizer::CullNoneFillSolid>();
				this->renderer_->SetShader<Shader::Shadow>();
				this->renderer_->SetVertex<Vertex::QuadNormal>();
				this->renderer_->SetConstantsBuffer(&this->cb_);
			}
		}
		
	private:
		void Update(void) override
		{
			//this->Destroy();
		}
		void Always(void) override
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();
			auto window = Game::GetSystem<System::Window>();
			auto camera = Game::GetSystem<System::Camera>();

			D3DXMATRIX World;

			//ワールドトランスフォーム
			static float x = 0;
			x += 0.01f;
			D3DXMATRIX Tran;
			D3DXMatrixRotationY(&Tran, x);
			World = Tran;
			
			//this->cb_.world_ = World;
			//this->cb_.viewport_ = { window->Width<float>(),  window->Height<float>() };

			this->cb_.w_ = World;
			this->cb_.v_ = camera->GetView();
			this->cb_.p_ = camera->GetProjection();

			this->cb_.lightdir_ = { 1.f, 0.f, 1.f, 0.f };
			this->cb_.diffuse_ = { 1.f, 0.f, 0.f, 1.f };
		}
	};
}