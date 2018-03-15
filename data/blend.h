#pragma once

// システム
#include <system\direct3d11.h>

// 標準ライブラリ
#include <vector>

// API
#include <D3DX10.h>
#include <D3DX11.h>

struct IBlend
{
	ID3D11BlendState * state_;

	void Create(D3D11_BLEND_DESC * bd)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		d3d->device_->CreateBlendState(bd, &this->state_);
	}

	void Rendering(void)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		d3d->context_->OMSetBlendState(this->state_, nullptr, 0xffffff);
	}
};