#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �Q�[���I�u�W�F�N�g
#include <game_object\logo.h>

namespace Scene
{
	class Title : public Entity
	{
	public:
		Title(Entity * parent) : Entity(parent)
		{
			this->AddChild<GameObject::Logo>();
		}
	};
}