#include "WebUI1.h"

#include <format>
#include <string>
#include <memory>
#include <unordered_map>

#include <Windows.h>
#include <exdisp.h>
#include <MsHTML.h>
#include <ExDispid.h>

#include "com/base/ComPtr.h"

#include "com/SimpleStorage.h"
#include "com/SimpleOleClientSite.h"
#include "com/SimpleDWebBrowserEvents2.h"

namespace webui1
{
	struct WebUI1Context
	{
		HWND mParent = NULL;

		core::com::base::ComPtr<IOleObject> mOleObject;
		core::com::base::ComPtr<IWebBrowser2> mWebBrowser;

		core::com::base::ComPtr<core::com::SimpleStorage> mStorage;
		core::com::base::ComPtr<core::com::SimpleOleClientSite> mOleClientSite;
		core::com::base::ComPtr<core::com::SimpleDWebBrowserEvents2> mDWebBrowserEvents;
	};

	std::unordered_map<HWND, std::shared_ptr<WebUI1Context>> context;

	bool IsValidThread(void* parentWindowHandle)
	{
		const HWND kParentWindowHandle = reinterpret_cast<HWND>(parentWindowHandle);

		if (!IsWindow(kParentWindowHandle))
		{
			return false;
		}

		const DWORD kCurrentThreadId = GetCurrentThreadId();
		const DWORD kParentWindowThreadId = GetWindowThreadProcessId(kParentWindowHandle, nullptr);

		return (kCurrentThreadId == kParentWindowThreadId);
	}

	bool HasContext(void* parentWindowHandle)
	{
		const HWND kParentWindowHandle = reinterpret_cast<HWND>(parentWindowHandle);

		if (!IsValidThread(parentWindowHandle))
		{
			return false;
		}

		return webui1::context.contains(kParentWindowHandle);
	}
} // namespace webui1

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
	int WebUI1_Initialize(void* parentWindowHandle)
	{
		const HWND kParentWindowHandle = reinterpret_cast<HWND>(parentWindowHandle);

		if (!webui1::IsValidThread(parentWindowHandle))
		{
			return E_INVALIDARG;
		}

		if (webui1::HasContext(parentWindowHandle))
		{
			return E_INVALIDARG;
		}

		auto newContext = std::make_shared<webui1::WebUI1Context>();
		newContext->mStorage = core::com::SimpleStorage::CreateInstance();

		HRESULT hr = E_FAIL;
		hr = OleCreate(CLSID_WebBrowser, IID_IOleObject, OLERENDER_DRAW, nullptr, nullptr, newContext->mStorage, (void**)&newContext->mOleObject);
		if (FAILED(hr))
		{
			return hr;
		}

		newContext->mOleClientSite = core::com::SimpleOleClientSite::CreateInstance(kParentWindowHandle, newContext->mOleObject);
		hr = newContext->mOleObject->SetClientSite(newContext->mOleClientSite);
		if (FAILED(hr))
		{
			return hr;
		}

		hr = OleSetContainedObject(newContext->mOleObject, TRUE);
		if (FAILED(hr))
		{
			return hr;
		}

		RECT parentRect = { 0 };
		hr = newContext->mOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, nullptr, newContext->mOleClientSite, -1, kParentWindowHandle, &parentRect);
		if (FAILED(hr))
		{
			return hr;
		}

		hr = newContext->mOleObject->QueryInterface(&newContext->mWebBrowser);
		if (FAILED(hr))
		{
			return hr;
		}

		newContext->mDWebBrowserEvents = core::com::SimpleDWebBrowserEvents2::CreateInstance(newContext->mWebBrowser);
		hr = newContext->mDWebBrowserEvents->GetInitResult();
		if (FAILED(hr))
		{
			return hr;
		}

		newContext->mParent = kParentWindowHandle;

		webui1::context[kParentWindowHandle] = newContext;
		return hr;
	}

	int WebUI1_Finalize(void* parentWindowHandle)
	{
		const HWND kParentWindowHandle = reinterpret_cast<HWND>(parentWindowHandle);

		if (!webui1::HasContext(parentWindowHandle))
		{
			return E_INVALIDARG;
		}

		webui1::context.erase(kParentWindowHandle);
		return S_OK;
	}

	int WebUI1_Resize(void* parentWindowHandle, int width, int height)
	{
		const HWND kParentWindowHandle = reinterpret_cast<HWND>(parentWindowHandle);

		if (!webui1::HasContext(parentWindowHandle))
		{
			return E_INVALIDARG;
		}

		webui1::context[kParentWindowHandle]->mOleClientSite->Resize(width, height);
		return S_OK;
	}

	int WebUI1_Navigate(void* parentWindowHandle, const wchar_t* url)
	{
		const HWND kParentWindowHandle = reinterpret_cast<HWND>(parentWindowHandle);

		if (url == nullptr)
		{
			return E_INVALIDARG;
		}

		const core::com::base::ComStr kUrl(url);
		if (kUrl.IsEmpty())
		{
			return E_INVALIDARG;
		}

		if (!webui1::HasContext(parentWindowHandle))
		{
			return E_INVALIDARG;
		}

		auto context = webui1::context[kParentWindowHandle];

		VARIANT vtEmpty;
		vtEmpty.vt = VT_EMPTY;
		return context->mWebBrowser->Navigate(kUrl, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
	}

	int WebUI1_SetInterface(void* parentWindowHandle, const wchar_t* name, WebUIInterfaceFunc callback)
	{
		const HWND kParentWindowHandle = reinterpret_cast<HWND>(parentWindowHandle);

		if (name == nullptr || callback == nullptr)
		{
			return E_INVALIDARG;
		}

		const core::com::base::ComStr kName(name);
		if (kName.IsEmpty())
		{
			return E_INVALIDARG;
		}

		if (!webui1::HasContext(parentWindowHandle))
		{
			return E_INVALIDARG;
		}

		auto context = webui1::context[kParentWindowHandle];

		auto handler = context->mDWebBrowserEvents->GetDocHostUIHandler();
		auto dispatcher = handler->GetDispatcher();

		const bool kAddInvokerResult = dispatcher->AddInvoker(
			kName,
			[callback](const wchar_t* argument, wchar_t* result, int resultLength) -> unsigned int
			{
				if (!argument || !result)
				{
					return E_INVALIDARG;
				}

				return callback(argument, result, resultLength);
			});

		return kAddInvokerResult? S_OK : E_FAIL;
	}

	int WebUI1_SendEvent(void* parentWindowHandle, const wchar_t* name, const wchar_t* content)
	{
		const HWND kParentWindowHandle = reinterpret_cast<HWND>(parentWindowHandle);

		if (name == nullptr || content == nullptr)
		{
			return E_INVALIDARG;
		}

		const std::wstring kName(name);
		if (kName.empty())
		{
			return E_INVALIDARG;
		}

		const std::wstring kContent(content);
		if (kContent.empty())
		{
			return E_INVALIDARG;
		}

		if (!webui1::HasContext(parentWindowHandle))
		{
			return E_INVALIDARG;
		}

		auto context = webui1::context[kParentWindowHandle];

		core::com::base::ComPtr<IDispatch> document;
		HRESULT hr = context->mWebBrowser->get_Document(&document);
		if (FAILED(hr)) {
			return hr;
		}

		core::com::base::ComPtr<IHTMLDocument2> document2;
		hr = document->QueryInterface(&document2);
		if (FAILED(hr))
		{
			return hr;
		}

		core::com::base::ComPtr<IHTMLWindow2> htmlWindow;
		hr = document2->get_parentWindow(&htmlWindow);
		if (FAILED(hr))
		{
			return hr;
		}

		const core::com::base::ComStr kFunctionCall(std::format(L"{}({});", kName, kContent).c_str());
		const core::com::base::ComStr kLanguage(L"JavaScript");

		VARIANT vt;
		hr = htmlWindow->execScript(kFunctionCall, kLanguage, &vt);

		return hr;
	}
#ifdef __cplusplus
}
#endif // __cplusplus