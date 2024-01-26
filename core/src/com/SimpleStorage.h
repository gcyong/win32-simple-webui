#pragma once

#include "base/StorageBase.h"

namespace core::com
{
	class SimpleStorage : public base::StorageBase<SimpleStorage>
	{
	public:
		virtual ~SimpleStorage() = default;

		virtual HRESULT STDMETHODCALLTYPE SetClass(REFCLSID clsid) override
		{
			return S_OK;
		}
	};
} // namespace core::com