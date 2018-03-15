#pragma once

// ÉfÅ[É^
#include <data\rasterizer.h>

namespace Rasterizer
{
	class CullFrontFillSolid : public IRasterizer
	{
	public:
		CullFrontFillSolid(void)
		{
			this->Create(D3D11_CULL_FRONT, D3D11_FILL_SOLID);
		}
	};
}