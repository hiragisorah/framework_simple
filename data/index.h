#pragma once

// システム
#include <system\direct3d11.h>

// 標準ライブラリ
#include <vector>

// API
#include <D3DX10.h>
#include <D3DX11.h>

struct IIndex
{
	ID3D11Buffer * buffer_;
	unsigned int num_;

	void Renderering(void)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		d3d->context_->IASetIndexBuffer(this->buffer_, DXGI_FORMAT_R32_UINT, 0);
	}

	void CreateBuffer(std::vector<unsigned int> * indices)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		this->num_ = indices->size();

		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * this->num_;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA init_data;
		init_data.pSysMem = indices->data();

		if (FAILED(d3d->device_->CreateBuffer(&bd, &init_data, &this->buffer_)))
		{
			MessageBoxA(0, "インデックスバッファーの生成に失敗しました。", 0, MB_OK);
			PostQuitMessage(0);
		}
	}
};