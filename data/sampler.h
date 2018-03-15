#pragma once

// システム
#include <system\direct3d11.h>

// 標準ライブラリ
#include <vector>

// API
#include <D3DX10.h>
#include <D3DX11.h>

struct ISampler
{
	ID3D11SamplerState * state_;

	void Create(D3D11_SAMPLER_DESC * sd)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		d3d->device_->CreateSamplerState(sd, &this->state_);
	}

	void Rendering(void)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		d3d->context_->PSSetSamplers(0, 1, &this->state_);
	}
};