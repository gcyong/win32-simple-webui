#pragma once

#include <type_traits>

#include <Unknwnbase.h>

namespace base::util
{
	template <typename T> requires std::is_base_of_v<IUnknown, T>
	T* SafeAcquire(T* pT) noexcept
	{
		if (pT)
		{
			(pT)->AddRef();
		}
		return pT;
	}

	template <typename T> requires std::is_base_of_v<IUnknown, T>
	void SafeRelease(T** ppT) noexcept
	{
		if (ppT && (*ppT))
		{
			(*ppT)->Release();
			(*ppT) = nullptr;
		}
	}

	template <typename T> requires std::is_base_of_v<IUnknown, T>
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
			SafeRelease(&mPtr);
		}

		ComPtr<T>& operator=(T* ptr) noexcept
		{
			if (mPtr)
			{
				SafeRelease(&mPtr);
			}

			mPtr = SafeAcquire(ptr);
			return *this;
		}

		ComPtr<T>& operator=(const ComPtr<T>& comPtr) noexcept
		{
			if (mPtr)
			{
				SafeRelease(&mPtr);
			}

			mPtr = SafeAcquire<T*>(comPtr);
			return *this;
		}

		ComPtr<T>& operator=(ComPtr<T>&& comPtr) noexcept
		{
			if (mPtr)
			{
				SafeRelease(&mPtr);
			}

			mPtr = comPtr.mPtr;
			comPtr.mPtr = nullptr;
			return *this;
		}

		operator T*() noexcept
		{
			return mPtr;
		}

		operator const T*() const noexcept
		{
			return mPtr;
		}

		operator IUnknown*() noexcept
		{
			return mPtr;
		}

		operator const IUnknown*() const noexcept
		{
			return mPtr;
		}

		T** operator&() noexcept
		{
			return &mPtr;
		}

	private:
		T* mPtr;
	};

	template <>
	class ComPtr<IUnknown>
	{
	public:
		ComPtr() noexcept : mPtr(nullptr)
		{
		}

		ComPtr(IUnknown* ptr) noexcept : mPtr(ptr)
		{
		}

		ComPtr(const ComPtr<IUnknown>& comPtr) noexcept : mPtr(SafeAcquire(comPtr.mPtr))
		{
		}

		ComPtr(ComPtr<IUnknown>&& comPtr) noexcept : mPtr(comPtr.mPtr)
		{
			comPtr.mPtr = nullptr;
		}

		~ComPtr() noexcept
		{
			SafeRelease(&mPtr);
		}

		ComPtr<IUnknown>& operator=(IUnknown* ptr) noexcept
		{
			if (mPtr)
			{
				SafeRelease(&mPtr);
			}

			mPtr = SafeAcquire(ptr);
			return *this;
		}

		ComPtr<IUnknown>& operator=(const ComPtr<IUnknown>& comPtr) noexcept
		{
			if (mPtr)
			{
				SafeRelease(&mPtr);
			}

			mPtr = SafeAcquire(comPtr.mPtr);
			return *this;
		}

		ComPtr<IUnknown>& operator=(ComPtr<IUnknown>&& comPtr) noexcept
		{
			if (mPtr)
			{
				SafeRelease(&mPtr);
			}

			mPtr = comPtr.mPtr;
			comPtr.mPtr = nullptr;
			return *this;
		}

		operator IUnknown*() noexcept
		{
			return mPtr;
		}

		operator const IUnknown*() const noexcept
		{
			return mPtr;
		}

		IUnknown** operator&() noexcept
		{
			return &mPtr;
		}

	private:
		IUnknown* mPtr;
	};
} // namespace base::util