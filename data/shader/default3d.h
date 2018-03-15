#pragma once

// システム
#include <system\direct3d11.h>

// データ
#include <data\shader.h>

// Utils
#include <utils\user_literal.h>

namespace Shader
{
	class Default3D : public IShader
	{
	public:
		struct CB
		{
			ALIGN16 D3DXMATRIX w_;
			ALIGN16 D3DXMATRIX v_;
			ALIGN16 D3DXMATRIX p_;

			ALIGN16 D3DXCOLOR color_ = { 1.f, 1.f, 1.f, 1.f };
		};

		CB cb_;

	public:
		Default3D(void)
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			UINT num = sizeof(layout) / sizeof(layout[0]);
			this->MakeShader<CB>("default3d"hlsl, layout, num);
		}
	};
}