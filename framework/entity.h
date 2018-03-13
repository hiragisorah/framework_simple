#pragma once

#pragma warning(disable: 4316)

// フレームワーク
#include <framework\component.h>

// 標準ライブラリ
#include <unordered_map>
#include <vector>
#include <string>
#include <typeinfo>

namespace FrameWork
{
	class Entity
	{
	private:
		Entity * parent_;
		std::unordered_map<std::string, Component*> components_;
		std::vector<Entity*> children_;
		bool destroy_ = false;

	public:
		Entity(Entity * parent) : parent_(parent) {}
		virtual ~Entity(void)
		{
			for (auto component : this->components_)
				delete component.second;

			for (auto child : this->children_)
				delete child;
		}

	public:
		template<class _Component, class ... Args>
		_Component * const AddComponent(Args ... args)
		{
			auto name = typeid(_Component).name();
			auto component = new _Component(this, args ...);
			this->components_[name] = component;

			return component;
		}

		template<class _Component>
		_Component * const GetComponent(void)
		{
			auto name = typeid(_Component).name();

			return static_cast<_Component*>(this->components_[name]);
		}

		template<class _Component>
		void RemoveComponent(void)
		{
			auto name = typeid(_Component).name();
			delete this->components_[name];
			this->components_[name] = nullptr;
		}

	public:
		template<class _Child, class ... Args>
		_Child * const AddChild(Args ... args)
		{
			auto child = new _Child(this, args ...);
			this->children_.emplace_back(child);

			return child;
		}

	public:
		void Destroy(void)
		{
			this->destroy_ = true;
		}

	public:
		void _Update(void)
		{
			this->Update();
			for (auto itr = this->components_.begin(); itr != this->components_.end();)
			{
				auto component = (*itr).second;
				if (component)
				{
					component->Update();
					++itr;
				}
				else
				{
					itr = this->components_.erase(itr);
				}
			}

			for (size_t n = 0; n < this->children_.size();)
			{
				auto child = this->children_[n];

				if (child->destroy_)
				{
					this->children_.erase(this->children_.begin() + n);
				}
				else
				{
					child->_Update();
					++n;
				}
			}
		}
		void _Pause(void)
		{
			this->Pause();
			for (auto itr = this->components_.begin(); itr != this->components_.end();)
			{
				auto component = (*itr).second;
				if (component)
				{
					component->Pause();
					++itr;
				}
				else
				{
					itr = this->components_.erase(itr);
				}
			}

			for (size_t n = 0; n < this->children_.size();)
			{
				auto child = this->children_[n];

				if (child->destroy_)
				{
					this->children_.erase(this->children_.begin() + n);
				}
				else
				{
					child->_Pause();
					++n;
				}
			}
		}
		void _Always(void)
		{
			this->Always();
			for (auto itr = this->components_.begin(); itr != this->components_.end();)
			{
				auto component = (*itr).second;
				if (component)
				{
					component->Always();
					++itr;
				}
				else
				{
					itr = this->components_.erase(itr);
				}
			}

			for (size_t n = 0; n < this->children_.size();)
			{
				auto child = this->children_[n];

				if (child->destroy_)
				{
					this->children_.erase(this->children_.begin() + n);
				}
				else
				{
					child->_Always();
					++n;
				}
			}
		}

	private:
		virtual void Update(void) {}
		virtual void Pause(void) {}
		virtual void Always(void) {}
	};
}