#pragma once

// ÉfÅ[É^
#include <data\vertex.h>

namespace Vertex
{
	class QuadNormal : public IVertex
	{
		struct VERTEX
		{
			VERTEX(D3DXVECTOR3 position, D3DXVECTOR3 normal) : position_(position), normal_(normal) {}

			D3DXVECTOR3 position_;
			D3DXVECTOR3 normal_;
		};

	public:
		QuadNormal(void)
		{
			this->topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			std::vector<VERTEX> vertices;
			vertices.emplace_back(VERTEX(D3DXVECTOR3(-.5f, -.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.f)));
			vertices.emplace_back(VERTEX(D3DXVECTOR3(-.5f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.f)));
			vertices.emplace_back(VERTEX(D3DXVECTOR3(0.5f, -.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.f)));
			vertices.emplace_back(VERTEX(D3DXVECTOR3(0.5f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.f)));
			this->CreateBuffer(&vertices);
		}
	};
}