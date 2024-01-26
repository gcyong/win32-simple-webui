#pragma once

#include <string>

#include <oleauto.h>

namespace core::com::base
{
	class ComStr
	{
	public:
		explicit ComStr() noexcept : mComStr(nullptr)
		{
		}

		explicit ComStr(const std::wstring& str) noexcept : mComStr(SysAllocString(str.c_str()))
		{
		}

		explicit ComStr(const BSTR comStr) noexcept : mComStr(SysAllocStringByteLen(reinterpret_cast<LPCSTR>(comStr), SysStringByteLen(comStr)))
		{
		}

		explicit ComStr(const ComStr& comStr) noexcept : ComStr(comStr.mComStr)
		{
		}

		explicit ComStr(ComStr&& comStr) noexcept : mComStr(comStr.mComStr)
		{
			comStr.mComStr = nullptr;
		}

		~ComStr()
		{
			Reset();
		}

		ComStr& operator=(const ComStr& comStr) noexcept
		{
			Reset();
			mComStr = SysAllocStringByteLen(reinterpret_cast<LPCSTR>(comStr.mComStr), SysStringByteLen(comStr));
			return *this;
		}

		ComStr& operator=(ComStr&& comStr) noexcept
		{
			Reset();
			mComStr = comStr.mComStr;
			comStr.mComStr = nullptr;
			return *this;
		}

		void Reset()
		{
			if (mComStr)
			{
				SysFreeString(mComStr);
			}
			mComStr = nullptr;
		}

		BSTR Release()
		{
			BSTR comStr = mComStr;
			mComStr = nullptr;
			return comStr;
		}

		bool IsEmpty() const noexcept
		{
			if (mComStr)
			{
				return (SysStringByteLen(mComStr) == 0);
			}

			return true;
		}

		operator BSTR() noexcept
		{
			return mComStr;
		}

		operator const BSTR() const noexcept
		{
			return mComStr;
		}

		wchar_t* GetString() noexcept
		{
			return mComStr;
		}

		const wchar_t* GetString() const noexcept
		{
			return mComStr;
		}

		bool operator==(const ComStr& rhs) const noexcept
		{
			if (mComStr == nullptr && rhs.mComStr == nullptr)
			{
				return true;
			}

			if (mComStr == nullptr || rhs.mComStr == nullptr)
			{
				return false;
			}

			return (std::wstring(mComStr).compare(rhs.mComStr) == 0);
		}

		bool operator!=(const ComStr& rhs) const noexcept
		{
			return !(*this == rhs);
		}

	private:
		BSTR mComStr;
	};

	struct ComStrHash
	{
		std::size_t operator()(const ComStr& comStr) const
		{
			return std::hash<std::wstring>{}(comStr.GetString());
		}
	};
} // namespace core::com::base