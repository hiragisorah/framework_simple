#pragma once

// ÉfÅ[É^
#include <data\vertex.h>

namespace Vertex
{
	class Triangle : public IVertex
	{
	public:
		Triangle(void)
		{
			this->topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			std::vector<D3DXVECTOR3> vertices;
			vertices.emplace_back(D3DXVECTOR3(0.0f, 0.5f, 0.0f));
			vertices.emplace_back(D3DXVECTOR3(0.5f, -.5f, 0.0f));
			vertices.emplace_back(D3DXVECTOR3(-.5f, -.5f, 0.0f));
			this->CreateBuffer(&vertices);
		}
	};
}