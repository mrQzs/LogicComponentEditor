#pragma once

#include "yd_project.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <Windows.h>
#endif
#include "SystemHelper.h"

namespace yd
{
	// 项目管理器访问实现类
	class CProjectAccessorImpl
	{
	public:
		CProjectAccessorImpl() {
			m_strWorkingDirectory = yd::CFileHelper::GetMainWorkingDirectory();
		}
		~CProjectAccessorImpl() {
			this->Uninitialize();
		}

	public:
		// 创建实例
		static std::shared_ptr<CProjectAccessorImpl> CreateInstance() {
			return std::make_shared<CProjectAccessorImpl>();
		}

	public:
		// 是否已经初始化
		bool IsInitialized() const {
			return m_bInitialized;
		}

		// 初始化
		bool Initialize(uint32 uiVersion, const std::string& strProjectName, uint8 ucFormat) {
#ifdef _WIN32
			std::string strFilePath = yd::CStringHelper::Format("%s%s\\libProject.dll", m_strWorkingDirectory.c_str(), DEPENDENCE_PATH_NAME);
#else
			std::string strFilePath = yd::CStringHelper::Format("%s%s/libProject.so", m_strWorkingDirectory.c_str(), DEPENDENCE_PATH_NAME);
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
			yd::funcGetIProjectManager func = (yd::funcGetIProjectManager)::GetProcAddress(m_hLibrary, "GetIProjectManager");
			if (nullptr == func) {
				m_strErrorMsg = yd::CStringHelper::Format("获取接口(GetIProjectManager)地址失败，错误代码：%u", ::GetLastError());
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
				return false;
			}
			m_pProjectManager = func(uiVersion, strProjectName.c_str(), ucFormat);
			if (nullptr == m_pProjectManager) {
				m_strErrorMsg = yd::CStringHelper::Format("执行接口(GetIProjectManager)失败，错误代码：%u", ::GetLastError());
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
			if (nullptr != m_pProjectManager) {
				m_pProjectManager->Release();
				m_pProjectManager = nullptr;
			}
#ifdef _WIN32
			if (nullptr != m_hLibrary) {
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
			}
#endif
			m_bLoaded = false;

			return true;
		}

		// 获取错误信息
		const char* GetErrorMsg() {
			if (!m_strErrorMsg.empty()) {
				return m_strErrorMsg.c_str();
			}
			if (nullptr != m_pProjectManager) {
				return m_pProjectManager->GetErrorMsg();
			}
			else {
				return "";
			}
		}

		// 获取项目管理接口
		bool GetProjectManager(yd::IProjectManager*& pProjectManager) {
			if (nullptr != m_pProjectManager) {
				m_pProjectManager->AddRef();
				pProjectManager = m_pProjectManager;
				return true;
			}
			return false;
		}

	private:
		std::string				m_strWorkingDirectory{ "" };
		std::string				m_strErrorMsg{ "" };
		bool					m_bInitialized{ false };
		bool					m_bLoaded{ false };
#ifdef _WIN32
		HINSTANCE				m_hLibrary{ nullptr };
#endif
		yd::IProjectManager* m_pProjectManager{ nullptr };
	};
	using CProjectAccessorImplPtr = std::shared_ptr<CProjectAccessorImpl>;
}
