#pragma once

#include "yddef.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <memory>

namespace yd {
	// �����ܵ��ͻ���
	class CNamedPipeClient
	{
	public:
		CNamedPipeClient(const std::string& strPipeName, uint32 uiTimeout) : m_hClientPipe(nullptr), m_strPipeName(strPipeName), m_uiTimeOut(uiTimeout), m_iErrorCode(0) {
		}
		~CNamedPipeClient() {
			if (nullptr != m_hClientPipe && INVALID_HANDLE_VALUE != m_hClientPipe) {
				::CloseHandle(m_hClientPipe);
				m_hClientPipe = nullptr;
			}
		}

	public:
		// ����ʵ��
		static std::shared_ptr<CNamedPipeClient> CreateInstance(const std::string& strPipeName, uint32 uiTimeout) {
			return std::make_shared<CNamedPipeClient>(strPipeName, uiTimeout);
		}

	public:
		// �Ƿ��
		bool IsOpened() const {
			return (nullptr != m_hClientPipe && INVALID_HANDLE_VALUE != m_hClientPipe);
		}

		// �򿪹ܵ�
		bool Open() {
			m_iErrorCode = 0;
			if (this->IsOpened()) {
				return true;
			}
			if (!::WaitNamedPipe(m_strPipeName.c_str(), m_uiTimeOut)) {
				m_iErrorCode = (int32)::GetLastError();
				this->Close();
				return false;
			}
			m_hClientPipe = ::CreateFile(
				m_strPipeName.c_str(),
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);
			if (nullptr == m_hClientPipe || INVALID_HANDLE_VALUE == m_hClientPipe) {
				m_iErrorCode = (int32)::GetLastError();
				this->Close();
				return false;
			}
			return true;
		}

		// �رչܵ�
		bool Close() {
			if (nullptr != m_hClientPipe && INVALID_HANDLE_VALUE != m_hClientPipe) {
				::CloseHandle(m_hClientPipe);
				m_hClientPipe = nullptr;
				return true;
			}
			return false;
		}

		// ��������
		uint32 Send(const byte* lpszBuffer, uint32 uiLength) {
			m_iErrorCode = 0;
			if (!this->Open()) {
				return 0;
			}
			DWORD dwBytesWrite = 0;
			if (!::WriteFile(m_hClientPipe, lpszBuffer, uiLength, &dwBytesWrite, NULL) || 0 == dwBytesWrite) {
				m_iErrorCode = (int32)::GetLastError();
				this->Close();
				return 0;
			}
			return (uint32)dwBytesWrite;
		}

		// ��������
		uint32 Receive(byte* lpszBuffer, uint32 uiMaxSize) {
			m_iErrorCode = 0;
			if (!this->Open()) {
				return 0;
			}
			DWORD dwBytesRead = 0;
			if (!::ReadFile(m_hClientPipe, lpszBuffer, uiMaxSize, &dwBytesRead, NULL) || 0 == dwBytesRead) {
				m_iErrorCode = (int32)::GetLastError();
				this->Close();
				return 0;
			}
			return (uint32)dwBytesRead;
		}

		// ��ȡ�������
		int32 GetErrorCode() const {
			return m_iErrorCode;
		}

	private:
		HANDLE		m_hClientPipe;
		std::string	m_strPipeName;
		uint32		m_uiTimeOut;
		int32		m_iErrorCode;
	};
}