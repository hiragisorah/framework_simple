#pragma once

// フレームワーク
#include <framework\component.h>

// API
#include <D3DX10.h>

namespace Component
{
	class Transform : public IComponent
	{
	public:
		Transform(Entity * parent) : IComponent(parent)
		{

		}

	public:
		D3DXVECTOR3 position_ = { 0.f, 0.f, 0.f, };
		D3DXVECTOR3 rotation_ = { 0.f, 0.f, 0.f };
		D3DXVECTOR3 scale_ = { 1.f, 1.f, 1.f };

	public:
		D3DXVECTOR3 center_rotation_ = { 0.f, 0.f, 0.f };
		D3DXVECTOR3 center_scale_ = { 0.f, 0.f, 0.f };

	public:
		D3DXMATRIX Matrix(void)
		{
			D3DXMATRIX ret;
			D3DXQUATERNION rot;
			D3DXQuaternionRotationYawPitchRoll(&rot, this->rotation_.y, this->rotation_.x, this->rotation_.z);
			D3DXMatrixTransformation(&ret, &this->center_scale_, nullptr, &this->scale_, &this->center_rotation_, &rot, &this->position_);
			return ret;
		}
	};
}