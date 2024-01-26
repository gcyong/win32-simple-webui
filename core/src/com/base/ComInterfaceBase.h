#pragma once

#include <new>
#include <type_traits>

#include <Unknwnbase.h>

#include "ComPtr.h"

namespace core::com::base
{
	template <typename T, typename I>
	class ComInterfaceBase : public I
	{
	public:
		explicit ComInterfaceBase() noexcept : mRefCount(1)
		{
		}

		virtual ~ComInterfaceBase() = default;

		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override
		{
			if (riid == __uuidof(IUnknown))
			{
				(*ppvObject) = SafeAcquire(this);
				return S_OK;
			}
			else if (riid == __uuidof(I))
			{
				(*ppvObject) = SafeAcquire(this);
				return S_OK;
			}

			return E_NOINTERFACE;
		}

		virtual ULONG STDMETHODCALLTYPE AddRef() override
		{
			return InterlockedIncrement(&mRefCount);
		}

		virtual ULONG STDMETHODCALLTYPE Release() override
		{
			const ULONG kRefCount = InterlockedDecrement(&mRefCount);
			if (kRefCount == 0)
			{
				delete this;
			}
			return kRefCount;
		}

		template <typename... Args>
		static ComPtr<T> CreateInstance(Args&&... args)
		{
			return new(std::nothrow) T(std::forward<Args>(args)...);
		}

	private:
		volatile ULONG mRefCount;
	};
} // namespace core::com::base