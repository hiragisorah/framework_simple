#pragma once

class IComponent
{
	friend class Entity;

private:
	Entity * parent_;

public:
	IComponent(Entity * parent) : parent_(parent) {}
	virtual ~IComponent(void) {}

public:
	Entity * const GetParent(void)
	{
		return this->parent_;
	}

private:
	// �|�[�Y���Ă��Ȃ���
	virtual void Update(void) {}
	// �|�[�Y��
	virtual void Pause(void) {}
	// �펞
	virtual void Always(void) {}
};