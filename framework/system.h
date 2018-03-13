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
		// �|�[�Y���Ă��Ȃ���
		virtual void Update(void) {}
		// �|�[�Y��
		virtual void Pause(void) {}
		// �펞
		virtual void Always(void) {}
	};
}