#pragma once

// システム
#include <system\direct3d11.h>

// データ
#include <data\shader.h>

// Utils
#include <utils\user_literal.h>

namespace Shader
{
	class Default2D : public IShader
	{
	public:
		struct CB
		{
			ALIGN16 D3DXMATRIX world_;
			
			ALIGN16 D3DXVECTOR2 viewport_ = { 1280.f, 720.f };

			ALIGN16 D3DXCOLOR color_ = { 1.f, 1.f, 1.f, 1.f };
		};

		CB cb_;

	public:
		Default2D(void)
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			UINT num = sizeof(layout) / sizeof(layout[0]);
			this->MakeShader<CB>("default2d"hlsl, layout, num);
		}
	};
}