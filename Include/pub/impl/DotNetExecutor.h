#pragma once

#include "yddef.h"
#include "StringHelper.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>

// Mono 应用域管理器
class CMonoDomainMgr
{
public:
	// 唯一实例
	static CMonoDomainMgr* Instance() {
		static CMonoDomainMgr mgr;
		return &mgr;
	}

public:
	// 初始化：程序启动时调用一次
	bool Initialize(const std::string& strDomain) {
		if (nullptr != m_pMonoDomain) {
			return true;
		}
#ifdef _WIN32
		mono_set_dirs("C:\\Program Files\\Mono\\lib", "C:\\Program Files\\Mono\\etc");
#else
#endif
		m_pMonoDomain = mono_jit_init(strDomain.c_str());
		return (nullptr != m_pMonoDomain);
	}

	// 反初始化：程序退出前调用一次
	bool Uninitialize() {
		if (nullptr == m_pMonoDomain) {
			return false;
		}
		// 释放应用域
		mono_jit_cleanup(m_pMonoDomain);
		m_pMonoDomain = nullptr;
		return true;
	}

	// 是否初始化
	bool IsInitialized() const {
		return (nullptr != m_pMonoDomain);
	}

	// 获取应用域
	MonoDomain* GetDomain() {
		return m_pMonoDomain;
	}

private:
	MonoDomain* m_pMonoDomain{ nullptr };
};

// .Net 方法执行器
class CDotNetFunction
{
public:
	// 构造/析构函数
	CDotNetFunction(MonoDomain* pMonoDomain, const std::string& strModule, const std::string& strNamespace, const std::string& strClass, const std::string& strFunction) :
		m_pMonoDomain(pMonoDomain), m_strModule(strModule), m_strNamespace(strNamespace), m_strClass(strClass), m_strFunction(strFunction) {
	}
	~CDotNetFunction() {}

public:
	// 创建实例
	static std::shared_ptr<CDotNetFunction> CreateInstance(MonoDomain* pMonoDomain, const std::string& strModule, const std::string& strNamespace, const std::string& strClass, const std::string& strFunction) {
		return std::make_shared<CDotNetFunction>(pMonoDomain, strModule, strNamespace, strClass, strFunction);
	}

public:
	// 初始化
	bool Initialize() {
		if (m_bInitialized) {
			return true;
		}
		if (nullptr == m_pMonoDomain) {
			m_strLastError = "未初始化MonoDomain";
			return false;
		}
		// 加载程序集
		m_pMonoAssembly = mono_domain_assembly_open(m_pMonoDomain, m_strModule.c_str());
		if (nullptr == m_pMonoAssembly) {
			m_strLastError = yd::CStringHelper::Format("调用mono_domain_assembly_open(%s)失败", m_strModule.c_str());
			return false;
		}
		m_pMonoImage = mono_assembly_get_image(m_pMonoAssembly);
		if (nullptr == m_pMonoImage) {
			m_strLastError = "调用mono_assembly_get_image失败";
			return false;
		}
		// 获取MonoClass，类似于反射
		m_pMonoClass = mono_class_from_name(m_pMonoImage, m_strNamespace.c_str(), m_strClass.c_str());
		if (nullptr == m_pMonoClass) {
			m_strLastError = yd::CStringHelper::Format("调用mono_class_from_name(%s,%s)失败", m_strNamespace.c_str(), m_strClass.c_str());
			return false;
		}
		// 创建类对象
		m_pMonoObject = mono_object_new(m_pMonoDomain, m_pMonoClass);
		if (nullptr == m_pMonoObject) {
			m_strLastError = "调用mono_object_new失败";
			return false;
		}
		// 获取类方法
		m_pMonoMethod = mono_class_get_method_from_name(m_pMonoClass, m_strFunction.c_str(), 1);
		if (nullptr == m_pMonoMethod) {
			m_strLastError = yd::CStringHelper::Format("调用mono_class_get_method_from_name(%s)失败", m_strFunction.c_str());
			return false;
		}
		m_bInitialized = true;
		return true;
	}

	// 执行方法
	int32 Execute() {
		// 初始化
		if (!m_bInitialized) {
			return CROSS_INTERFACE_RESULT_FAILED;
		}
		int32 iResult = 0;
		void* parrParameters[1] = { &iResult };
		mono_runtime_invoke(m_pMonoMethod, m_pMonoObject, parrParameters, nullptr);
		return iResult;
	}

	// 获取错误
	const char* GetLastError() {
		return m_strLastError.c_str();
	}

private:
	std::string m_strLastError{ "" };
	std::string	m_strModule{ "" };
	std::string	m_strNamespace{ "" };
	std::string	m_strClass{ "" };
	std::string m_strFunction{ "" };
	bool		m_bInitialized{ false };
	MonoDomain* m_pMonoDomain{ nullptr };
	MonoAssembly* m_pMonoAssembly{ nullptr };
	MonoImage* m_pMonoImage{ nullptr };
	MonoClass* m_pMonoClass{ nullptr };
	MonoObject* m_pMonoObject{ nullptr };
	MonoMethod* m_pMonoMethod{ nullptr };
};
using CDotNetFunctionPtr = std::shared_ptr<CDotNetFunction>;

// .Net 类执行器
class CDotNetClass
{
public:
	// 构造/析构函数
	CDotNetClass(MonoDomain* pMonoDomain, const std::string& strModule, const std::string& strNamespace, const std::string& strClass) :
		m_pMonoDomain(pMonoDomain), m_strModule(strModule), m_strNamespace(strNamespace), m_strClass(strClass) {
	}
	~CDotNetClass() {}

public:
	// 创建实例
	static std::shared_ptr<CDotNetClass> CreateInstance(MonoDomain* pMonoDomain, const std::string& strModule, const std::string& strNamespace, const std::string& strClass) {
		return std::make_shared<CDotNetClass>(pMonoDomain, strModule, strNamespace, strClass);
	}

public:
	// 初始化
	bool Initialize() {
		if (m_bInitialized) {
			return true;
		}
		if (nullptr == m_pMonoDomain) {
			return false;
		}
		// 加载程序集
		m_pMonoAssembly = mono_domain_assembly_open(m_pMonoDomain, m_strModule.c_str());
		if (nullptr == m_pMonoAssembly) {
			return false;
		}
		m_pMonoImage = mono_assembly_get_image(m_pMonoAssembly);
		if (nullptr == m_pMonoImage) {
			return false;
		}
		// 获取MonoClass，类似于反射
		m_pMonoClass = mono_class_from_name(m_pMonoImage, m_strNamespace.c_str(), m_strClass.c_str());
		if (nullptr == m_pMonoClass) {
			return false;
		}
		// 创建类对象
		m_pMonoObject = mono_object_new(m_pMonoDomain, m_pMonoClass);
		if (nullptr == m_pMonoObject) {
			return false;
		}
		m_bInitialized = true;
		return true;
	}

	// 执行方法
	int32 Execute(const std::string& strFunction) {
		// 初始化
		if (!m_bInitialized) {
			return CROSS_INTERFACE_RESULT_FAILED;
		}
		// 获取类方法
		MonoMethod* pMonoMethod = mono_class_get_method_from_name(m_pMonoClass, strFunction.c_str(), 1);
		if (nullptr == pMonoMethod) {
			return CROSS_INTERFACE_RESULT_FAILED;
		}
		int32 iResult = 0;
		void* parrParameters[1] = { &iResult };
		mono_runtime_invoke(pMonoMethod, m_pMonoObject, parrParameters, nullptr);
		return iResult;
	}

private:
	std::string	m_strModule{ "" };
	std::string	m_strNamespace{ "" };
	std::string	m_strClass{ "" };
	bool		m_bInitialized{ false };
	MonoDomain* m_pMonoDomain{ nullptr };
	MonoAssembly* m_pMonoAssembly{ nullptr };
	MonoImage* m_pMonoImage{ nullptr };
	MonoClass* m_pMonoClass{ nullptr };
	MonoObject* m_pMonoObject{ nullptr };
};
using CDotNetClassPtr = std::shared_ptr<CDotNetClass>;

// .Net 类库执行器
class CDotNetLibrary
{
public:
	// 构造/析构函数
	CDotNetLibrary(MonoDomain* pMonoDomain, const std::string& strModule) :
		m_pMonoDomain(pMonoDomain), m_strModule(strModule) {
	}
	~CDotNetLibrary() {}

public:
	// 创建实例
	static std::shared_ptr<CDotNetLibrary> CreateInstance(MonoDomain* pMonoDomain, const std::string& strModule) {
		return std::make_shared<CDotNetLibrary>(pMonoDomain, strModule);
	}

public:
	// 初始化
	bool Initialize() {
		if (m_bInitialized) {
			return true;
		}
		if (nullptr == m_pMonoDomain) {
			return false;
		}
		// 加载程序集
		m_pMonoAssembly = mono_domain_assembly_open(m_pMonoDomain, m_strModule.c_str());
		if (nullptr == m_pMonoAssembly) {
			return false;
		}
		m_pMonoImage = mono_assembly_get_image(m_pMonoAssembly);
		if (nullptr == m_pMonoImage) {
			return false;
		}
		m_bInitialized = true;
		return true;
	}

	// 执行方法
	int32 Execute(
		const std::string& strNamespace,
		const std::string& strClass,
		const std::string& strFunction) {
		// 初始化
		if (!m_bInitialized) {
			return CROSS_INTERFACE_RESULT_FAILED;
		}
		// 获取MonoClass，类似于反射
		MonoClass* pMonoClass = mono_class_from_name(m_pMonoImage, strNamespace.c_str(), strClass.c_str());
		if (nullptr == pMonoClass) {
			return CROSS_INTERFACE_RESULT_FAILED;
		}
		// 创建类对象
		MonoObject* pMonoObject = mono_object_new(m_pMonoDomain, pMonoClass);
		if (nullptr == pMonoObject) {
			return CROSS_INTERFACE_RESULT_FAILED;
		}
		// 获取类方法
		MonoMethod* pMonoMethod = mono_class_get_method_from_name(pMonoClass, strFunction.c_str(), 1);
		if (nullptr == pMonoMethod) {
			return CROSS_INTERFACE_RESULT_FAILED;
		}
		int32 iResult = 0;
		void* parrParameters[1] = { &iResult };
		mono_runtime_invoke(pMonoMethod, pMonoObject, parrParameters, nullptr);
		return iResult;
	}

private:
	std::string	m_strModule{ "" };
	bool		m_bInitialized{ false };
	MonoDomain* m_pMonoDomain{ nullptr };
	MonoAssembly* m_pMonoAssembly{ nullptr };
	MonoImage* m_pMonoImage{ nullptr };
};
using CDotNetLibraryPtr = std::shared_ptr<CDotNetLibrary>;
