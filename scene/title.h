#pragma once

// フレームワーク
#include <framework\entity.h>

// ゲームオブジェクト
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