#pragma once

// フレームワーク
#include <framework\system.h>

// API
#include <D3DX10.h>

namespace System
{
	class Camera : public ISystem
	{
	public:
		D3DXVECTOR3 eye_ = { 0.f, 1.f, -2.f };
		D3DXVECTOR3 at_ = { 0.f, 0.f, 0.f };
		D3DXVECTOR3 up_ = { 0.f, 1.f, 0.f };

	public:
		float fov_ = 3.141592f / 4;
		float aspect_ = 16.f / 9.f;
		float near_ = 0.1f;
		float far_ = 100.f;

	public:
		D3DXMATRIX GetView(void)
		{
			D3DXMATRIX ret;
			D3DXMatrixLookAtLH(&ret, &this->eye_, &this->at_, &this->up_);
			return ret;
		}

		D3DXMATRIX GetProjection(void)
		{
			D3DXMATRIX ret;
			D3DXMatrixPerspectiveFovLH(&ret, this->fov_, this->aspect_, this->near_, this->far_);
			return ret;
		}
	};
}