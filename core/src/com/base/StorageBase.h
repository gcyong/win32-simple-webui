#pragma once

#include <oleidl.h>

#include "ComInterfaceBase.h"

namespace core::com::base
{
	template <typename T>
	class StorageBase : public ComInterfaceBase<T, IStorage>
	{
	public:
		virtual ~StorageBase() = default;

		virtual HRESULT STDMETHODCALLTYPE CreateStream(const OLECHAR* pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream** ppstm) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OpenStream(const OLECHAR* pwcsName, void* reserved1, DWORD grfMode, DWORD reserved2, IStream** ppstm) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE CreateStorage(const OLECHAR* pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage** ppstg) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE OpenStorage(const OLECHAR* pwcsName, IStorage* pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage** ppstg) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE CopyTo(DWORD ciidExclude, const IID* rgiidExclude, SNB snbExclude, IStorage* pstgDest) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE MoveElementTo(const OLECHAR* pwcsName, IStorage* pstgDest, const OLECHAR* pwcsNewName, DWORD grfFlags) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE Commit(DWORD grfCommitFlags) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE Revert() override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE EnumElements(DWORD reserved1, void* reserved2, DWORD reserved3, IEnumSTATSTG** ppenum) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE DestroyElement(const OLECHAR* pwcsName) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE RenameElement(const OLECHAR* pwcsOldName, const OLECHAR* pwcsNewName) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE SetElementTimes(const OLECHAR* pwcsName, const FILETIME* pctime, const FILETIME* patime, const FILETIME* pmtime) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE SetClass(REFCLSID clsid) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE SetStateBits(DWORD grfStateBits, DWORD grfMask) override
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE Stat(STATSTG* pstatstg, DWORD grfStatFlag) override
		{
			return E_NOTIMPL;
		}
	};
} // namespace core::com::base