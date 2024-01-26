#pragma once

#include <exdisp.h>

#include "base/DWebBrowserEvents2Base.h"

#include "SimpleDocHostUIHandler.h"

namespace core::com
{
	class SimpleDWebBrowserEvents2 : public base::DWebBrowserEvents2Base<SimpleDWebBrowserEvents2>
	{
	public:
		explicit SimpleDWebBrowserEvents2(base::ComPtr<IWebBrowser2> webBrowser) noexcept : mInitResult(S_OK), mWebBrowser(webBrowser), mDocHostUIHandler(SimpleDocHostUIHandler::CreateInstance()), mConnectionPointCookie(0)
		{
			base::ComPtr<IConnectionPointContainer> connectionPointContainer;
			mInitResult = webBrowser->QueryInterface(&connectionPointContainer);
			if (FAILED(mInitResult))
			{
				return;
			}

			mInitResult = connectionPointContainer->FindConnectionPoint(DIID_DWebBrowserEvents2, &mConnectionPoint);
			if (FAILED(mInitResult))
			{
				return;
			}

			mInitResult = mConnectionPoint->Advise(this, &mConnectionPointCookie);
		}

		virtual ~SimpleDWebBrowserEvents2()
		{
			if (SUCCEEDED(mInitResult))
			{
				mConnectionPoint->Unadvise(mConnectionPointCookie);
			}
		}

		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override
		{
			if (riid == __uuidof(IDispatch))
			{
				(*ppvObject) = SafeAcquire(this);
				return S_OK;
			}

			return base::DWebBrowserEvents2Base<SimpleDWebBrowserEvents2>::QueryInterface(riid, ppvObject);
		}

		virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr) override
		{
			if (dispIdMember == DISPID_NAVIGATECOMPLETE2)
			{
				HRESULT hr = S_OK;

				base::ComPtr<IDispatch> pDoc;
				hr = mWebBrowser->get_Document(&pDoc);
				if (FAILED(hr))
				{
					return hr;
				}

				base::ComPtr<ICustomDoc> pCustomDoc;
				hr = pDoc->QueryInterface(&pCustomDoc);
				if (FAILED(hr))
				{
					return hr;
				}

				pCustomDoc->SetUIHandler(mDocHostUIHandler);
			}

			return S_OK;
		}

		HRESULT GetInitResult() const noexcept
		{
			return mInitResult;
		}

		base::ComPtr<SimpleDocHostUIHandler> GetDocHostUIHandler() const noexcept
		{
			return mDocHostUIHandler;
		}

	private:
		HRESULT mInitResult;

		base::ComPtr<IWebBrowser2> mWebBrowser;
		base::ComPtr<SimpleDocHostUIHandler> mDocHostUIHandler;

		DWORD mConnectionPointCookie;
		base::ComPtr<IConnectionPoint> mConnectionPoint;
	};
} // namespace core::com