#pragma once

class Game;

namespace FrameWork
{
	class System
	{
		friend Game;

	public:
		System(void) {}
		virtual ~System(void) {}

	private:
		// ポーズしていない時
		virtual void Update(void) {}
		// ポーズ時
		virtual void Pause(void) {}
		// 常時
		virtual void Always(void) {}
	};
}