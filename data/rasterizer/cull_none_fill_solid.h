#pragma once

// ÉfÅ[É^
#include <data\rasterizer.h>

namespace Rasterizer
{
	class CullNoneFillSolid : public IRasterizer
	{
	public:
		CullNoneFillSolid(void)
		{
			this->Create(D3D11_CULL_NONE, D3D11_FILL_SOLID);
		}
	};
}