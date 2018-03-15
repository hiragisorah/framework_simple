#pragma once

// ƒf[ƒ^
#include <data\blend.h>

namespace Blend
{
	class Alpha : public IBlend
	{
	public:
		Alpha(void)
		{
			D3D11_BLEND_DESC bd;
			memset(&bd, 0, sizeof(D3D11_BLEND_DESC));
			bd.AlphaToCoverageEnable = false;
			bd.IndependentBlendEnable = true;
			bd.RenderTarget[0].BlendEnable = true;
			bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			this->Create(&bd);
		}
	};
}