#pragma once

// フレームワーク
#include <framework\system.h>

// 標準ライブラリ
#include <unordered_map>
#include <string>

class Game
{
private:
	static std::unordered_map<std::string, FrameWork::System*> systems_;
	static bool pause_;
	static bool running_;

public:
	template<class _System, class ... Args>
	static _System * const AddSystem(Args ... args)
	{
		auto name = typeid(_System).name();
		auto system = new _System(args ...);
		Game::systems_[name] = system;

		return system;
	}

	template<class _System>
	static _System * const GetSystem(void)
	{
		auto name = typeid(_System).name();

		return static_cast<_System*>(Game::systems_[name]);
	}

	template<class _System>
	static void RemoveSystem(void)
	{
		auto name = typeid(_System).name();
		delete Game::systems_[name];
		Game::systems_[name] = nullptr:
	}

private:
	static void Update(void)
	{
		for (auto itr = Game::systems_.begin(); itr != Game::systems_.end();)
		{
			auto system = (*itr).second;
			if (system)
			{
				system->Update();
				++itr;
			}
			else
			{
				itr = Game::systems_.erase(itr);
			}
		}
	}
	static void Pause(void)
	{
		for (auto itr = Game::systems_.begin(); itr != Game::systems_.end();)
		{
			auto system = (*itr).second;
			if (system)
			{
				system->Pause();
				++itr;
			}
			else
			{
				itr = Game::systems_.erase(itr);
			}
		}
	}
	static void Always(void)
	{
		for (auto itr = Game::systems_.begin(); itr != Game::systems_.end();)
		{
			auto system = (*itr).second;
			if (system)
			{
				system->Always();
				++itr;
			}
			else
			{
				itr = Game::systems_.erase(itr);
			}
		}
	}

public:
	static void Run(void)
	{
		while (Game::running_)
		{
			Game::pause_ ? Game::Pause() : Game::Update();
			Game::Always();
		}

		for (auto system : Game::systems_)
			delete system.second;
	}

	static void Shutdown(void)
	{
		Game::running_ = false;
	}

	static void Pause(bool pause)
	{
		Game::pause_ = pause;
	}
};

std::unordered_map<std::string, FrameWork::System*> Game::systems_ = {};
bool Game::pause_ = false;
bool Game::running_ = true;