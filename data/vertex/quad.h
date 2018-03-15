#pragma once

// ÉfÅ[É^
#include <data\vertex.h>

namespace Vertex
{
	class Quad : public IVertex
	{
	public:
		Quad(void)
		{
			this->topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			std::vector<D3DXVECTOR3> vertices;
			vertices.emplace_back(D3DXVECTOR3(-.5f, -.5f, 0.0f));
			vertices.emplace_back(D3DXVECTOR3(-.5f, 0.5f, 0.0f));
			vertices.emplace_back(D3DXVECTOR3(0.5f, -.5f, 0.0f));
			vertices.emplace_back(D3DXVECTOR3(0.5f, 0.5f, 0.0f));
			this->CreateBuffer(&vertices);
		}
	};
}