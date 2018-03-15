#pragma once

// �t���[�����[�N
#include <framework\system.h>

// �R���|�[�l���g
#include <component\collider.h>

// �W�����C�u����
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