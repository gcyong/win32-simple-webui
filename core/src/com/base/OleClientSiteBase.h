#pragma once

#include <oleidl.h>

#include "ComInterfaceBase.h"

namespace core::com::base
{
	template <typename T>
	class OleClientSiteBase : public ComInterfaceBase<T, IOleClientSite>
	{
	public:
		virtual ~OleClientSiteBase() = default;

		virtual HRESULT STDMETHODCALLTYPE SaveObject() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker** ppmk) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetContainer(IOleContainer** ppContainer) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE ShowObject() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OnShowWindow(BOOL fShow) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout() override
		{
			return E_NOTIMPL;
		}
	};
} // namespace core::com::base