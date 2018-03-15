#pragma once

// フレームワーク
#include <framework\system.h>

// コンポーネント
#include <component\collider.h>

// 標準ライブラリ
#include <vector>
#include <unordered_map>

namespace System
{
	class CollisionManager : public ISystem
	{
	private:
		std::vector<Component::ICollider*> list_;

	public:
		void Add(Component::ICollider * collider)
		{
			this->list_.emplace_back(collider);
		}

	public:
		void Update(void) override
		{

		}
	};
}