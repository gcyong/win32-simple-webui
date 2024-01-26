#pragma once

#include <MsHtmHst.h>

#include "ComInterfaceBase.h"

namespace core::com::base
{
	template <typename T>
	class DocHostUIHandlerBase : public ComInterfaceBase<T, IDocHostUIHandler>
	{
	public:
		virtual ~DocHostUIHandlerBase() = default;

		virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(DWORD dwID, POINT* ppt, IUnknown* pcmdtReserved, IDispatch* pdispReserved) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetHostInfo(DOCHOSTUIINFO* pInfo) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE ShowUI(DWORD dwID, IOleInPlaceActiveObject* pActiveObject, IOleCommandTarget* pCommandTarget, IOleInPlaceFrame* pFrame, IOleInPlaceUIWindow* pDoc) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE HideUI() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE UpdateUI() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE EnableModeless(BOOL fEnable) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate(BOOL fActivate) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(BOOL fActivate) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE ResizeBorder(LPCRECT prcBorder, IOleInPlaceUIWindow* pUIWindow, BOOL fRameWindow) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG lpMsg, const GUID* pguidCmdGroup, DWORD nCmdID) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath(LPOLESTR* pchKey, DWORD dw) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetDropTarget(IDropTarget* pDropTarget, IDropTarget** ppDropTarget) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE GetExternal(IDispatch** ppDispatch) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE TranslateUrl(DWORD dwTranslate, LPWSTR pchURLIn, LPWSTR* ppchURLOut) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE FilterDataObject(IDataObject* pDO, IDataObject** ppDORet) override
		{
			return E_NOTIMPL;
		}
	};
} // namespace core::com::base