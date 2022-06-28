#pragma once

#include "yd_compiler.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <Windows.h>
#endif
#include "SystemHelper.h"

// 编译器实现类
namespace yd {
	class CCompilerImpl
	{
	public:
		CCompilerImpl() {
			m_strWorkingDirectory = yd::CFileHelper::GetMainWorkingDirectory();
		}
		~CCompilerImpl() {
			this->Uninitialize();
		}

	public:
		// 创建实例
		static std::shared_ptr<CCompilerImpl> CreateInstance() {
			return std::make_shared<CCompilerImpl>();
		}

	public:
		// 是否已经初始化
		bool IsInitialized() const {
			return m_bInitialized;
		}

		// 初始化
		bool Initialize(uint32 uiVersion, const std::string& strName) {
#ifdef _WIN32
			std::string strFilePath = yd::CStringHelper::Format("%s%s\\libCompiler.dll", m_strWorkingDirectory.c_str(), DEPENDENCE_PATH_NAME);
#else
			std::string strFilePath = yd::CStringHelper::Format("%s%s/libCompiler.so", m_strWorkingDirectory.c_str(), DEPENDENCE_PATH_NAME);
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
			yd::funcGetICompiler func = (yd::funcGetICompiler)::GetProcAddress(m_hLibrary, "GetICompiler");
			if (nullptr == func) {
				m_strErrorMsg = yd::CStringHelper::Format("获取接口(GetICompiler)地址失败，错误代码：%u", ::GetLastError());
				::FreeLibrary(m_hLibrary);
				m_hLibrary = nullptr;
				return false;
			}
			m_pCompiler = func(uiVersion, strName.c_str());
			if (nullptr == m_pCompiler) {
				m_strErrorMsg = yd::CStringHelper::Format("执行接口(GetICompiler)失败，错误代码：%u", ::GetLastError());
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
			if (nullptr != m_pCompiler) {
				m_pCompiler->Release();
				m_pCompiler = nullptr;
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

		// 获取编译器接口
		bool GetCompiler(yd::ICompiler*& pCompiler) {
			if (nullptr != m_pCompiler) {
				m_pCompiler->AddRef();
				pCompiler = m_pCompiler;
				return true;
			}
			return false;
		}

	private:
		std::string		m_strWorkingDirectory{ "" };
		std::string		m_strErrorMsg{ "" };
		bool			m_bInitialized{ false };
#ifdef _WIN32
		HINSTANCE		m_hLibrary{ nullptr };
#endif
		yd::ICompiler* m_pCompiler{ nullptr };
	};
	using CCompilerImplPtr = std::shared_ptr<CCompilerImpl>;
}
