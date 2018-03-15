#pragma once

// フレームワーク
#include <framework\component.h>

namespace Component
{
	class ICollider
	{
		virtual void OnCollisionEnter(ICollider * target)
		{

		}
		virtual void OnCollisionStay(ICollider * target)
		{

		}
		virtual void OnCollisionExit(ICollider * target)
		{

		}
	};
}