#pragma once
#pragma warning(disable: 4996)

// フレームワーク
#include <framework\game.h>
#include <framework\system.h>
#include <framework\entity.h>

// 標準ライブラリ
#include <stdio.h>

namespace System
{
	class SceneManager : public ISystem
	{
	public:
		SceneManager(void) {}
		~SceneManager(void)
		{
			delete this->current_scene_;
			delete this->next_scene_;
		}

	private:
		Entity * current_scene_ = nullptr;
		Entity * next_scene_ = nullptr;

	private:
		void Update(void) override
		{
			if (this->current_scene_)
				this->current_scene_->_Update();
		}
		void Pause(void) override
		{
			if(this->current_scene_)
				this->current_scene_->_Pause();
		}
		void Always(void) override
		{
			if (this->current_scene_)
				this->current_scene_->_Always();

			if (this->next_scene_)
			{
				delete this->current_scene_;
				this->current_scene_ = this->next_scene_;
				this->next_scene_ = nullptr;
			}
		}
	public:
		template<class _Scene, class ... Args>
		void ChangeScene(Args ... args)
		{
			this->next_scene_ = new _Scene(nullptr, args ...);
		}
	};
}