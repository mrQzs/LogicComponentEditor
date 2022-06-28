#pragma once

#include "yd_protocol_client.h"
#include "ProtocolImp.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <Windows.h>
#endif
#include "SystemHelper.h"

namespace yd {
	// 通讯协议客户端实现类
	class CProtocolClientImpl
	{
	public:
		CProtocolClientImpl() {
			m_strWorkingDirectory = yd::CFileHelper::GetMainWorkingDirectory();
		}
		~CProtocolClientImpl() {
			this->Uninitialize();
		}

	public:
		// 创建实例
		static std::shared_ptr<CProtocolClientImpl> CreateInstance() {
			return std::make_shared<CProtocolClientImpl>();
		}

	public:
		// 是否已经初始化
		bool IsInitialized() const {
			return m_bInitialized;
		}

		// 初始化
		bool Initialize(
			uint32 uiVersion,
			const std::string& strProjectName,
			const std::string& strUser,
			const std::string& strPassword,
			const std::string& strServerIp,
			uint16 usServerPort,
			uint32 uiTimeout) {
#ifdef _WIN32
			std::string strFilePath = yd::CStringHelper::Format("%s%s\\libProtocolClient.dll", m_strWorkingDirectory.c_str(), DEPENDENCE_PATH_NAME);
#else
			std::string strFilePath = yd::CStringHelper::Format("%s%s/libProtocolClient.so", m_strWorkingDirectory.c_str(), DEPENDENCE_PATH_NAME);
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
			proto::funcGetIProtocolClient func = (proto::funcGetIProtocolClient)::GetProcAddress(m_hLibrary, "GetIProtocolClient");
			if (nullptr == func) {
				m_strErrorMsg = yd::CStringHelper::Format("获取接口(GetIProtocolClient)地址失败，错误代码：%u", ::GetLastError());
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
				return false;
			}
			m_pIProtocolClient = func(uiVersion, strProjectName.c_str());
			if (nullptr == m_pIProtocolClient) {
				m_strErrorMsg = yd::CStringHelper::Format("执行接口(GetIProtocolClient)失败，错误代码：%u", ::GetLastError());
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
				return false;
			}
#else
#endif
			m_pImplProtocol = CProtocolImpl::CreateInstance();
			if (!m_pImplProtocol->Initialize(uiVersion, strProjectName)) {
				m_pIProtocolClient->Release();
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
				return false;
			}
			if (!m_pImplProtocol->GetIProtocol(m_pIProtocol)) {
				m_pIProtocolClient->Release();
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
				m_pImplProtocol->Uninitialize();
				return false;
			}
			if (!m_pIProtocolClient->Initialize(m_pIProtocol, strUser, strPassword, strServerIp, usServerPort, uiTimeout)) {
				m_pIProtocolClient->Release();
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
				m_pImplProtocol->Uninitialize();
			}
			return (m_bInitialized = true);
		}

		// 反初始化
		bool Uninitialize() {
			if (!m_bInitialized) {
				return false;
			}
			m_bInitialized = false;
			if (nullptr != m_pIProtocolClient) {
				m_pIProtocolClient->Release();
				m_pIProtocolClient = nullptr;
			}
			if (nullptr != m_hLibrary) {
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
			}
			if (nullptr != m_pImplProtocol) {
				m_pImplProtocol->Uninitialize();
				m_pImplProtocol = nullptr;
			}

			return true;
		}

		// 获取错误信息
		const char* GetErrorMsg() {
			return m_strErrorMsg.c_str();
		}

		// 获取通讯协议客户端接口
		bool GetIProtocolClient(proto::IProtocolClient*& pIProtocolClient) {
			if (nullptr != m_pIProtocolClient) {
				m_pIProtocolClient->AddRef();
				pIProtocolClient = m_pIProtocolClient;
				return true;
			}
			return false;
		}
		proto::IProtocolClient* IProtocolClient() {
			return m_pIProtocolClient;
		}

	private:
		std::string				m_strWorkingDirectory{ "" };
		std::string				m_strErrorMsg{ "" };
		bool					m_bInitialized{ false };
#ifdef _WIN32
		HINSTANCE				m_hLibrary{ nullptr };
#endif
		proto::IProtocolClient* m_pIProtocolClient{ nullptr };
		CProtocolImplPtr		m_pImplProtocol{ nullptr };
		proto::IProtocol* m_pIProtocol{ nullptr };
	};
	using CProtocolClientImplPtr = std::shared_ptr<CProtocolClientImpl>;
}
