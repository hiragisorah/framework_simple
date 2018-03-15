#pragma once

// ÉfÅ[É^
#include <data\vertex.h>

namespace Vertex
{
	class Point : public IVertex
	{
	public:
		Point(void)
		{
			this->topology_ = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
			std::vector<D3DXVECTOR3> vertices;
			vertices.emplace_back(D3DXVECTOR3(0.f, 0.f, 0.f));
			this->CreateBuffer(&vertices);
		}
	};
}