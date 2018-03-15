#pragma once

// システム
#include <system\direct3d11.h>

// 標準ライブラリ
#include <vector>

// API
#include <D3DX10.h>
#include <D3DX11.h>

struct IVertex
{
	D3D11_PRIMITIVE_TOPOLOGY topology_ = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	ID3D11Buffer * buffer_ = nullptr;
	unsigned int stride_ = 0;
	unsigned int offset_ = 0;
	unsigned int num_ = 0;

	void Rendering(void)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		d3d->context_->IASetPrimitiveTopology(this->topology_);
		d3d->context_->IASetVertexBuffers(0, 1, &this->buffer_, &this->stride_, &this->offset_);
	}

	template<class _Type>
	void CreateBuffer(std::vector<_Type> * vertices)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		this->num_ = vertices->size();
		this->stride_ = sizeof(_Type);
		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = this->stride_ * this->num_;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA init_data;
		init_data.pSysMem = vertices->data();

		if (FAILED(d3d->device_->CreateBuffer(&bd, &init_data, &this->buffer_)))
		{
			MessageBoxA(0, "頂点バッファーの生成に失敗しました。", 0, MB_OK);
			PostQuitMessage(0);
		}
	}
};