#pragma once

// フレームワーク
#include <framework\component.h>

namespace Component
{
	class IRenderer : public IComponent
	{
	public:
		IRenderer(Entity * parent) : IComponent(parent)
		{

		}

	public:
		virtual void Rendering(void) = 0;
	};
}