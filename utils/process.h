#pragma once

// �t���[�����[�N
#include <framework\game.h>

// �W�����C�u����
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