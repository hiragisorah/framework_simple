#pragma once

#pragma warning(disable: 4455)

#include <string>

std::string operator""hlsl(const char* str, size_t size)
{
	return "resource/shader/" + std::string(str, size) + ".hlsl";
}