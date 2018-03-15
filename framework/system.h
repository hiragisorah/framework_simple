#pragma once

class Game;

class ISystem
{
	friend Game;

public:
	ISystem(void) {}
	virtual ~ISystem(void) {}

private:
	// ポーズしていない時
	virtual void Update(void) {}
	// ポーズ時
	virtual void Pause(void) {}
	// 常時
	virtual void Always(void) {}
};