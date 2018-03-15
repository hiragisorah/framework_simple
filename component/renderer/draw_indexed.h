#pragma once

// コンポーネント
#include <component\renderer.h>

// データ
#include <data\shader.h>
#include <data\rasterizer.h>
#include <data\blend.h>
#include <data\sampler.h>
#include <data\vertex.h>
#include <data\index.h>

// システム
#include <system\database.h>

namespace Component
{
	namespace Renderer
	{
		class DrawIndexed : public Component::IRenderer
		{
		private:
			IShader * shader_ = nullptr;
			IRasterizer * rasterizer_ = nullptr;
			IBlend * blend_ = nullptr;
			ISampler * sampler_ = nullptr;
			IVertex * vertex_ = nullptr;
			IIndex * index_ = nullptr;
			void * cb_ = nullptr;
			unsigned int cb_size_ = 0;

		public:
			template<class _Shader>
			void SetShader(void)
			{
				this->shader_ = Game::GetSystem<System::Database<IShader>>()->GetData<_Shader>();
			}
			template<class _Rasterizer>
			void SetRasterizer(void)
			{
				this->rasterizer_ = Game::GetSystem<System::Database<IRasterizer>>()->GetData<_Rasterizer>();
			}
			template<class _Blend>
			void SetBlend(void)
			{
				this->blend_ = Game::GetSystem<System::Database<IBlend>>()->GetData<_Blend>();
			}
			template<class _Sampler>
			void SetSampler(void)
			{
				this->sampler_ = Game::GetSystem<System::Database<ISampler>>()->GetData<_Sampler>();
			}
			template<class _Vertex>
			void SetVertex(void)
			{
				this->vertex_ = Game::GetSystem<System::Database<IVertex>>()->GetData<_Vertex>();
			}
			template<class _Index>
			void SetIndex(void)
			{
				this->index_ = Game::GetSystem<System::Database<IIndex>>()->GetData<_Index>();
			}
			template<class _CBUFFER>
			void SetConstantsBuffer(_CBUFFER * cb)
			{
				this->cb_ = cb;
				this->cb_size_ = sizeof(_CBUFFER);
			}

		private:
			void Rendering(void) override
			{
				auto d3d = Game::GetSystem<System::Direct3D11>();

				this->UpdateConstantBuffer();

				this->shader_->Rendering();

				if(this->rasterizer_)
					this->rasterizer_->Rendering();

				if(this->rasterizer_)
					this->blend_->Rendering();

				if(this->sampler_)
					this->sampler_->Rendering();

				this->vertex_->Rendering();
				this->index_->Renderering();

				d3d->context_->DrawIndexed(this->index_->num_, 0, 0);
			}

		private:
			void UpdateConstantBuffer(void)
			{
				this->shader_->cb_ = this->cb_;
				this->shader_->cb_size = this->cb_size_;
			}

		private:
			void Always(void) override
			{
				Game::GetSystem<System::Direct3D11>()->draw_list_.emplace_back(this);
			}
		};
	}
}