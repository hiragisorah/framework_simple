#pragma once

// システム
#include <system\direct3d11.h>

// 標準ライブラリ
#include <vector>

// API
#include <D3DX10.h>
#include <D3DX11.h>

struct IRasterizer
{
	ID3D11RasterizerState * state_;

	void Create(D3D11_CULL_MODE cull, D3D11_FILL_MODE fill)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		D3D11_RASTERIZER_DESC rdc;
		memset(&rdc, 0, sizeof(rdc));

		rdc.CullMode = cull;
		rdc.FillMode = fill;

		d3d->device_->CreateRasterizerState(&rdc, &this->state_);
	}

	void Rendering(void)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		d3d->context_->RSSetState(this->state_);
	}
};