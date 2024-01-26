#pragma once

#include <type_traits>

#include <Unknwnbase.h>

namespace core::com::base
{
	template <typename T>
	T* SafeAcquire(T* pT) noexcept
	{
		if (pT)
		{
			(pT)->AddRef();
		}
		return pT;
	}

	template <typename T>
	void SafeRelease(T** ppT) noexcept
	{
		if (ppT && (*ppT))
		{
			(*ppT)->Release();
			(*ppT) = nullptr;
		}
	}

	template <typename T>
	class ComPtr
	{
	public:
		ComPtr() noexcept : mPtr(nullptr)
		{
		}

		ComPtr(T* ptr) noexcept : mPtr(ptr)
		{
		}

		ComPtr(const ComPtr<T>& comPtr) noexcept : mPtr(SafeAcquire(comPtr.mPtr))
		{
		}

		ComPtr(ComPtr<T>&& comPtr) noexcept : mPtr(comPtr.mPtr)
		{
			comPtr.mPtr = nullptr;
		}

		~ComPtr() noexcept
		{
			Reset();
		}

		ComPtr<T>& operator=(T* ptr) noexcept
		{
			Reset();

			mPtr = SafeAcquire(ptr);
			return *this;
		}

		ComPtr<T>& operator=(const ComPtr<T>& comPtr) noexcept
		{
			Reset();

			mPtr = SafeAcquire(comPtr.mPtr);
			return *this;
		}

		ComPtr<T>& operator=(ComPtr<T>&& comPtr) noexcept
		{
			Reset();

			mPtr = comPtr.mPtr;
			comPtr.mPtr = nullptr;
			return *this;
		}

		T* Clone() noexcept
		{
			return SafeAcquire(mPtr);
		}

		T* Release() noexcept
		{
			T* const kPtr = mPtr;
			mPtr = nullptr;
			return kPtr;
		}

		void Reset() noexcept
		{
			SafeRelease(&mPtr);
		}

		template <typename I>
		operator I*() noexcept
		{
			return mPtr;
		}

		template <typename I>
		operator const I*() const noexcept
		{
			return mPtr;
		}

		T** operator&() noexcept
		{
			return &mPtr;
		}

		explicit operator bool() const noexcept
		{
			return (mPtr != nullptr);
		}

		T* operator->() noexcept
		{
			return mPtr;
		}

		const T* operator->() const noexcept
		{
			return mPtr;
		}

		T& operator*() noexcept
		{
			return *mPtr;
		}

		const T& operator*() const noexcept
		{
			return *mPtr;
		}

	private:
		T* mPtr;
	};
} // namespace core::com::base