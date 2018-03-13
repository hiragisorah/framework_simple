#pragma once

// フレームワーク
#include <framework\system.h>
#include <Windows.h>

namespace System
{
	// 空クラス
	class Window;

	namespace Input
	{
		const int KEY_MAX = 256;

		class WM : public FrameWork::System
		{
			friend Window;

		private:
			bool Enable = false;
			bool IsKeys[KEY_MAX] = {};
			bool IsLClick = false;
			bool IsRClick = false;
			bool IsOldKeys[KEY_MAX] = {};
			bool IsOldLClick = false;
			bool IsOldRClick = false;
			unsigned int Keys[KEY_MAX] = {};
			unsigned int LClick = 0;
			unsigned int RClick = 0;
			unsigned int MousePosX = 0;
			unsigned int MousePosY = 0;
			POINT CursorPos;
		private:
			void Update(void) override
			{
				for (int n = 0; n < KEY_MAX; n++)
					this->IsKeys[n] ? ++this->Keys[n] : this->Keys[n] = 0;

				this->IsLClick ? ++this->LClick : this->LClick = 0;
				this->IsRClick ? ++this->RClick : this->RClick = 0;
			}

		public:
			bool KeyPressed(unsigned char key)
			{
				return this->IsKeys[key];
			}
			bool LeftClickPressed(void)
			{
				return this->IsLClick;
			}
			bool RightClickPressed(void)
			{
				return this->IsRClick;
			}
			bool KeyTriggered(unsigned char key)
			{
				return this->Keys[key] == 1;
			}
			bool LeftClickTriggered(void)
			{
				return this->LClick == 1;
			}
			bool RightClickTriggered(void)
			{
				return this->RClick == 1;
			}
			bool KeyReleased(unsigned char key)
			{
				return this->IsOldKeys[key] && !this->IsKeys[key];
			}
			bool LeftClickReleased(void)
			{
				return this->IsOldLClick && !this->IsLClick;
			}
			bool RightClickReleased(void)
			{
				return this->IsOldRClick && !this->IsRClick;
			}
			int GetMousePosX(void)
			{
				printf("%d, %d\n", this->CursorPos.x, this->CursorPos.y);
				return this->CursorPos.x - 640;
			}
			int GetMousePosY(void)
			{
				return this->CursorPos.y - 353;
			}
		};
	}
}