#pragma once

// フレームワーク
#include <framework\game.h>

// 標準ライブラリ
#include <string>

// API
#include <Windows.h>

namespace Utils
{
	void EndMsg(std::string msg)
	{
		MessageBoxA(0, msg.c_str(), 0, MB_OK);
		PostQuitMessage(0);
	}
}