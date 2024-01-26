#pragma once

#include "base/OleClientSiteBase.h"

#include "SimpleOleInPlaceSite.h"

namespace core::com
{
	class SimpleOleClientSite : public base::OleClientSiteBase<SimpleOleClientSite>
	{
	public:
		explicit SimpleOleClientSite(HWND parentWindow, base::ComPtr<IOleObject> oleObject) noexcept : mOleInPlaceSite(SimpleOleInPlaceSite::CreateInstance(parentWindow, oleObject))
		{
		}

		virtual ~SimpleOleClientSite() = default;

		void Resize(LONG width, LONG height)
		{
			if (mOleInPlaceSite)
			{
				mOleInPlaceSite->Resize(width, height);
			}
		}

		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override
		{
			if (riid == __uuidof(IOleInPlaceSite))
			{
				if (mOleInPlaceSite)
				{
					(*ppvObject) = mOleInPlaceSite.Clone();
					return S_OK;
				}
			}

			return base::OleClientSiteBase<SimpleOleClientSite>::QueryInterface(riid, ppvObject);
		}

		virtual HRESULT STDMETHODCALLTYPE GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker** ppmk) override
		{
			if ((dwAssign == OLEGETMONIKER_ONLYIFTHERE) && (dwWhichMoniker == OLEWHICHMK_CONTAINER))
			{
				return E_FAIL;
			}
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetContainer(IOleContainer** ppContainer) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE ShowObject() override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE OnShowWindow(BOOL fShow) override
		{
			return S_OK;
		}

	private:
		base::ComPtr<SimpleOleInPlaceSite> mOleInPlaceSite;
	};
} // namespace core::com