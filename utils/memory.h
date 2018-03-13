#pragma once

// �t���[�����[�N
#include <framework\game.h>

// �W��
#include <vector>
#include <unordered_map>
#include <string>
#include <typeinfo>

// API
#include <Windows.h>

#define ALIGN16 _declspec(align(16))

namespace Utils
{
	namespace Memory
	{
		template<class _Pointer>
		void SafeRelease(_Pointer & pointer)
		{
			if (pointer != nullptr) pointer->Release();
		}
		template<class _Pointer, class _Type, class ... Args>
		void SafeNew(_Pointer & pointer, Args ... args)
		{
			delete pointer;
			pointer = new _Type(args ...);
		}
	}
}