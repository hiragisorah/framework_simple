#pragma once

namespace FrameWork
{
	class Component
	{
		friend class Entity;

	private:
		Entity * parent_;

	public:
		Component(Entity * parent) : parent_(parent) {}
		virtual ~Component(void) {}

	public:
		Entity * const GetParent(void)
		{
			return this->parent_;
		}

	private:
		// ポーズしていない時
		virtual void Update(void) {}
		// ポーズ時
		virtual void Pause(void) {}
		// 常時
		virtual void Always(void) {}
	};
}