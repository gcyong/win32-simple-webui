#pragma once

#include <oaidl.h>

#include "ComInterfaceBase.h"

namespace core::com::base
{
	template <typename T>
	class DispatchBase : public ComInterfaceBase<T, IDispatch>
	{
	public:
		virtual ~DispatchBase() = default;

		virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT* pctinfo) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr) override
		{
			return E_NOTIMPL;
		}
	};
} // namespace core::com::base