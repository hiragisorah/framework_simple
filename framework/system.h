#pragma once

class Game;

class ISystem
{
	friend Game;

public:
	ISystem(void) {}
	virtual ~ISystem(void) {}

private:
	// �|�[�Y���Ă��Ȃ���
	virtual void Update(void) {}
	// �|�[�Y��
	virtual void Pause(void) {}
	// �펞
	virtual void Always(void) {}
};