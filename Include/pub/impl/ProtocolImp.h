#pragma once

#include "yd_protocol.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <Windows.h>
#endif
#include "SystemHelper.h"

namespace yd {
	// 通讯协议实现类
	class CProtocolImpl
	{
	public:
		CProtocolImpl() {
			m_strWorkingDirectory = yd::CFileHelper::GetMainWorkingDirectory();
		}
		~CProtocolImpl() {
			this->Uninitialize();
		}

	public:
		// 创建实例
		static std::shared_ptr<CProtocolImpl> CreateInstance() {
			return std::make_shared<CProtocolImpl>();
		}

	public:
		// 是否已经初始化
		bool IsInitialized() const {
			return m_bInitialized;
		}

		// 初始化
		bool Initialize(uint32 uiVersion, const std::string& strName) {
#ifdef _WIN32
			std::string strFilePath = yd::CStringHelper::Format("%s%s\\libProtocol.dll", m_strWorkingDirectory.c_str(), DEPENDENCE_PATH_NAME);
#else
			std::string strFilePath = yd::CStringHelper::Format("%s%s/libProtocol.so", m_strWorkingDirectory.c_str(), DEPENDENCE_PATH_NAME);
#endif
			if (!yd::CFileHelper::FileExists(strFilePath)) {
				m_strErrorMsg = yd::CStringHelper::Format("动态库(%s)不存在", strFilePath.c_str());
				return false;
			}

#ifdef _WIN32
			m_hLibrary = ::LoadLibraryA(strFilePath.c_str());
			if (nullptr == m_hLibrary) {
				m_strErrorMsg = yd::CStringHelper::Format("加载动态库(%s)失败，错误代码：%u", strFilePath.c_str(), ::GetLastError());
				return false;
			}
			proto::funcGetIProtocol func = (proto::funcGetIProtocol)::GetProcAddress(m_hLibrary, "GetIProtocol");
			if (nullptr == func) {
				m_strErrorMsg = yd::CStringHelper::Format("获取接口(GetIProtocol)地址失败，错误代码：%u", ::GetLastError());
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
				return false;
			}
			m_pProtocol = func(uiVersion, strName.c_str());
			if (nullptr == m_pProtocol) {
				m_strErrorMsg = yd::CStringHelper::Format("执行接口(GetIProtocol)失败，错误代码：%u", ::GetLastError());
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
				return false;
			}
#else
#endif
			return (m_bInitialized = true);
		}

		// 反初始化
		bool Uninitialize() {
			if (!m_bInitialized) {
				return false;
			}
			m_bInitialized = false;
			if (nullptr != m_pProtocol) {
				m_pProtocol->Release();
				m_pProtocol = nullptr;
			}
			if (nullptr != m_hLibrary) {
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
			}

			return true;
		}

		// 获取错误信息
		const char* GetErrorMsg() {
			return m_strErrorMsg.c_str();
		}

		// 获取通讯协议接口
		bool GetIProtocol(proto::IProtocol*& pIProtocol) {
			if (nullptr != m_pProtocol) {
				m_pProtocol->AddRef();
				pIProtocol = m_pProtocol;
				return true;
			}
			return false;
		}

	private:
		std::string				m_strWorkingDirectory{ "" };
		std::string				m_strErrorMsg{ "" };
		bool					m_bInitialized{ false };
#ifdef _WIN32
		HINSTANCE				m_hLibrary{ nullptr };
#endif
		proto::IProtocol* m_pProtocol{ nullptr };
	};
	using CProtocolImplPtr = std::shared_ptr<CProtocolImpl>;
}
