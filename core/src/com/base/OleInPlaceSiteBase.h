#pragma once

#include <oleidl.h>

#include "ComInterfaceBase.h"

namespace core::com::base
{
	template <typename T>
	class OleInPlaceSiteBase : public ComInterfaceBase<T, IOleInPlaceSite>
	{
	public:
		virtual ~OleInPlaceSiteBase() = default;

		/*
			IOleWindow
		*/

		virtual HRESULT STDMETHODCALLTYPE GetWindow(HWND* phwnd) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode) override
		{
			return E_NOTIMPL;
		}

		/*
			IOleInPlaceSite
		*/

		virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OnUIActivate() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE Scroll(SIZE scrollExtant) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate(BOOL fUndoable) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE DiscardUndoState() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OnPosRectChange(LPCRECT lprcPosRect) override
		{
			return E_NOTIMPL;
		}
	};
} // namespace core::com::base