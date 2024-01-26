#pragma once

#include <functional>
#include <unordered_map>

#include "base/ComStr.h"
#include "base/DispatchBase.h"

namespace core::com
{
	class SimpleDispatch : public base::DispatchBase<SimpleDispatch>
	{
	private:
		struct Invoker
		{
			DISPID id;
			base::ComStr name;
			std::function<unsigned int(const wchar_t*, wchar_t*, int)> invoker;
		};

	public:
		explicit SimpleDispatch() noexcept : mNewDispId(0)
		{
		}

		virtual ~SimpleDispatch() = default;

		bool AddInvoker(const base::ComStr& name, std::function<unsigned int(const wchar_t*, wchar_t*, int)> invoker)
		{
			if (!invoker)
			{
				return false;
			}

			if (name.IsEmpty())
			{
				return false;
			}

			const DISPID kNewDispId = ++mNewDispId;

			Invoker newInvoker;
			newInvoker.id = kNewDispId;
			newInvoker.name = name;
			newInvoker.invoker = invoker;

			mInvokerList[kNewDispId] = std::move(newInvoker);
			mDispatchIndexerByName[name] = kNewDispId;
			return true;
		}

		virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) override
		{
			for (unsigned int i = 0; i < cNames; ++i)
			{
				const base::ComStr kName(rgszNames[i]);
				if (mDispatchIndexerByName.contains(kName))
				{
					rgDispId[i] = mDispatchIndexerByName[kName];
					return S_OK;
				}
			}

			return S_FALSE;
		}

		virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr) override
		{
			if (!mInvokerList.contains(dispIdMember))
			{
				return S_FALSE;
			}

			if (wFlags & DISPATCH_PROPERTYGET)
			{
				if (pVarResult != NULL)
				{
					VariantInit(pVarResult);
					V_VT(pVarResult) = VT_BOOL;
					V_BOOL(pVarResult) = true;
				}
			}

			if (wFlags & DISPATCH_METHOD)
			{
				// SimpleDispatch allows only one parameter as string type.
				if (pDispParams->cArgs != 1 || (pDispParams->rgvarg[0].vt != VT_BSTR))
				{
					return S_FALSE;
				}

				Invoker& invoker = mInvokerList[dispIdMember];

				constexpr unsigned int kResultMaxLength = 1024;
				wchar_t result[kResultMaxLength] = { 0 };
				if (!SUCCEEDED(invoker.invoker(base::ComStr(pDispParams->rgvarg[0].bstrVal).GetString(), result, kResultMaxLength)))
				{
					return S_FALSE;
				}

				VariantInit(pVarResult);
				V_VT(pVarResult) = VT_BSTR;
				pVarResult->bstrVal = base::ComStr(std::wstring(result)).Release();

				return S_OK;
			}

			return S_FALSE;
		}

	private:
		DISPID mNewDispId;

		std::unordered_map<base::ComStr, DISPID, base::ComStrHash> mDispatchIndexerByName;
		std::unordered_map<DISPID, Invoker> mInvokerList;
	};
} // namespace core::com