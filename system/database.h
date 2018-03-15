#pragma once

// フレームワーク
#include <framework\system.h>

// 標準ライブラリ
#include <unordered_map>
#include <typeinfo>

namespace System
{
	template<class _Type>
	class Database : public ISystem
	{
	private:
		std::unordered_map<std::string, _Type*> data_;

	public:
		~Database(void)
		{
			for (auto data : this->data_)
				delete data.second;
		}

	public:
		template<class _Data>
		_Type * const GetData(void)
		{
			return this->data_[typeid(_Data).name()];
		}
		template<class _Data, class ... Args>
		void Load(Args ... args)
		{
			delete this->data_[typeid(_Data).name()];
			this->data_[typeid(_Data).name()] = new _Data(args ...);
		}
		template<class _Data>
		void Unload(void)
		{
			delete this->data_[typeid(_Data).name()];
			this->data_[typeid(_Data).name()] = nullptr;
		}
	};
}