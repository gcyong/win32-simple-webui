#pragma once

#include "base/DocHostUIHandlerBase.h"

#include "SimpleDispatch.h"

namespace core::com
{
	class SimpleDocHostUIHandler : public base::DocHostUIHandlerBase<SimpleDocHostUIHandler>
	{
	public:
		explicit SimpleDocHostUIHandler() noexcept : mDispatcher(SimpleDispatch::CreateInstance())
		{
		}

		virtual ~SimpleDocHostUIHandler() = default;

		virtual HRESULT STDMETHODCALLTYPE GetExternal(IDispatch** ppDispatch) override
		{
			(*ppDispatch) = mDispatcher.Clone();
			return S_OK;
		}

		base::ComPtr<SimpleDispatch> GetDispatcher() const noexcept
		{
			return mDispatcher;
		}

	private:
		base::ComPtr<SimpleDispatch> mDispatcher;
	};
} // namespace core::com