#pragma once

#include "base/OleInPlaceSiteBase.h"

namespace core::com
{
	class SimpleOleInPlaceSite : public base::OleInPlaceSiteBase<SimpleOleInPlaceSite>
	{
	public:
		explicit SimpleOleInPlaceSite(HWND parentWindow, base::ComPtr<IOleObject> oleObject) noexcept : mParentWindow(parentWindow), mOleObject(oleObject)
		{
		}

		virtual ~SimpleOleInPlaceSite() = default;

		void Resize(LONG width, LONG height)
		{
			if (mOleInPlaceObject)
			{
				const RECT kRect = { 0, 0, width, height };
				mOleInPlaceObject->SetObjectRects(&kRect, &kRect);
			}
		}

		virtual HRESULT STDMETHODCALLTYPE GetWindow(HWND* phwnd) override
		{
			(*phwnd) = mParentWindow;
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate() override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate() override
		{
			if (!mOleObject)
			{
				return E_FAIL;
			}

			if (mOleInPlaceObject)
			{
				mOleInPlaceObject.Reset();
			}

			HRESULT hr = E_FAIL;

			hr = OleLockRunning(mOleObject, TRUE, FALSE);
			if (FAILED(hr))
			{
				return hr;
			}

			hr = mOleObject->QueryInterface(&mOleInPlaceObject);
			if (FAILED(hr))
			{
				return hr;
			}

			HWND windowHandle = NULL;
			hr = mOleInPlaceObject->GetWindow(&windowHandle);
			if (FAILED(hr))
			{
				return hr;
			}
			ShowWindow(windowHandle, SW_SHOW);

			return hr;
		}

		virtual HRESULT STDMETHODCALLTYPE OnUIActivate() override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo) override
		{
			RECT parentRect = { 0 };
			GetClientRect(mParentWindow, &parentRect);

			(*ppDoc) = nullptr;
			(*ppFrame) = nullptr;
			(*lprcPosRect) = parentRect;
			(*lprcClipRect) = parentRect;

			lpFrameInfo->haccel = NULL;
			lpFrameInfo->fMDIApp = false;
			lpFrameInfo->cAccelEntries = 0;
			lpFrameInfo->hwndFrame = mParentWindow;

			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate(BOOL fUndoable) override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate() override
		{
			mOleObject.Reset();
			mOleInPlaceObject.Reset();
			return S_OK;
		}

	private:
		HWND mParentWindow;

		base::ComPtr<IOleObject> mOleObject;
		base::ComPtr<IOleInPlaceObject> mOleInPlaceObject;
	};
} // namespace core::com