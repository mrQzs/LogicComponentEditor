#pragma once

#include "yd_project.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <Windows.h>
#endif
#include "SystemHelper.h"
#include "RapidJsonHelper.h"

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

// 变量数值封装类
class CVRValue
{
public:
	CVRValue() {
		ucType = 0;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
	}
	CVRValue(const CVRValue& other) {
		ucType = other.ucType;
		memcpy(&vrValue, &other.vrValue, sizeof(yd::VRVALUE));
	}
	CVRValue& operator=(const CVRValue& other) {
		if (this == &other) {
			return *this;
		}
		ucType = other.ucType;
		memcpy(&vrValue, &other.vrValue, sizeof(yd::VRVALUE));
		return *this;
	}

	// 带参数构造函数
	CVRValue(const bool& bValue) {
		ucType = DATA_TYPE_BOOL;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.bValue = bValue;
	}
	CVRValue(const int8& cValue) {
		ucType = DATA_TYPE_INT8;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.cValue = cValue;
	}
	CVRValue(const uint8& ucValue) {
		ucType = DATA_TYPE_UINT8;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.ucValue = ucValue;
	}
	CVRValue(const int16& sValue) {
		ucType = DATA_TYPE_INT16;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.sValue = sValue;
	}
	CVRValue(const uint16& usValue) {
		ucType = DATA_TYPE_UINT16;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.usValue = usValue;
	}
	CVRValue(const int32& iValue) {
		ucType = DATA_TYPE_INT32;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.iValue = iValue;
	}
	CVRValue(const uint32& uiValue) {
		ucType = DATA_TYPE_UINT32;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.uiValue = uiValue;
	}
	CVRValue(const int64& llValue) {
		ucType = DATA_TYPE_INT64;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.llValue = llValue;
	}
	CVRValue(const uint64& ullValue) {
		ucType = DATA_TYPE_UINT64;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.ullValue = ullValue;
	}
	CVRValue(const float& fValue) {
		ucType = DATA_TYPE_FLOAT;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.fValue = fValue;
	}
	CVRValue(const double& dblValue) {
		ucType = DATA_TYPE_DOUBLE;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		vrValue.unValue.dblValue = dblValue;
	}
	CVRValue(const std::string& strValue) {
		ucType = DATA_TYPE_STRING;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		yd::CStringHelper::SafeCopy(vrValue.unValue.szValue, sizeof(vrValue.unValue.szValue), strValue.c_str());
	}
	CVRValue(const yd::COORDS* pCoords) {
		ucType = DATA_TYPE_AXIS_COORD;
		memset(&vrValue, 0x00, sizeof(yd::VRVALUE));
		memcpy(&vrValue.unValue.coords, pCoords, sizeof(yd::COORDS));
	}
	CVRValue(const uint8& ucRelType, const yd::VRVALUE* pValue) {
		ucType = ucRelType;
		memcpy(&vrValue, pValue, sizeof(yd::VRVALUE));
	}

public:
	static std::shared_ptr<CVRValue> CreateInstance() {
		return std::make_shared<CVRValue>();
	}

public:
	// 更新值
	bool SetValue(const std::string& strValue) {
		ucType = DATA_TYPE_STRING;
		yd::CStringHelper::SafeCopy(vrValue.unValue.szValue, sizeof(vrValue.unValue.szValue), strValue.c_str());
		return true;
	}
	bool SetValue(const bool& bValue) {
		ucType = DATA_TYPE_BOOL;
		vrValue.unValue.bValue = bValue;
		return true;
	}
	bool SetValue(const int8& cValue) {
		ucType = DATA_TYPE_INT8;
		vrValue.unValue.cValue = cValue;
		return true;
	}
	bool SetValue(const uint8& ucValue) {
		ucType = DATA_TYPE_UINT8;
		vrValue.unValue.ucValue = ucValue;
		return true;
	}
	bool SetValue(const int16& sValue) {
		ucType = DATA_TYPE_INT16;
		vrValue.unValue.sValue = sValue;
		return true;
	}
	bool SetValue(const uint16& usValue) {
		ucType = DATA_TYPE_UINT16;
		vrValue.unValue.usValue = usValue;
		return true;
	}
	bool SetValue(const int32& iValue) {
		ucType = DATA_TYPE_INT32;
		vrValue.unValue.iValue = iValue;
		return true;
	}
	bool SetValue(const uint32& uiValue) {
		ucType = DATA_TYPE_UINT32;
		vrValue.unValue.uiValue = uiValue;
		return true;
	}
	bool SetValue(const int64& llValue) {
		ucType = DATA_TYPE_INT64;
		vrValue.unValue.llValue = llValue;
		return true;
	}
	bool SetValue(const uint64& ullValue) {
		ucType = DATA_TYPE_UINT64;
		vrValue.unValue.ullValue = ullValue;
		return true;
	}
	bool SetValue(const float& fValue) {
		ucType = DATA_TYPE_FLOAT;
		vrValue.unValue.fValue = fValue;
		return true;
	}
	bool SetValue(const double& dblValue) {
		ucType = DATA_TYPE_DOUBLE;
		vrValue.unValue.dblValue = dblValue;
		return true;
	}
	bool SetValue(uint8 ucRelType, const yd::VRVALUE* pValue) {
		if (nullptr == pValue) {
			return false;
		}
		ucType = ucRelType;
		memcpy(&vrValue, pValue, sizeof(yd::VRVALUE));
		return true;
	}
	bool SetValue(const yd::COORDS* pCoords) {
		if (nullptr == pCoords) {
			return false;
		}
		ucType = DATA_TYPE_AXIS_COORD;
		memcpy(&vrValue.unValue.coords, pCoords, sizeof(yd::COORDS));
		return true;
	}

	// 获取值
	bool GetValue(std::string& strValue) {
		switch (ucType) {
		case DATA_TYPE_BOOL:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			strValue = yd::CStringHelper::Format("%u", vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			strValue = yd::CStringHelper::Format("%lld", vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			strValue = yd::CStringHelper::Format("%llu", vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			strValue = yd::CStringHelper::Format("%f", vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			strValue = yd::CStringHelper::Format("%lf", vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			strValue = vrValue.unValue.szValue;
			break;
		case DATA_TYPE_AXIS_COORD:
			yd::CRapidJsonHelper::AxisCoords2Json(&vrValue.unValue.coords, strValue);
			break;
		default:
			break;
		}
		return true;
	}
	bool GetValue(bool& bValue) {
		bValue = false;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			bValue = vrValue.unValue.bValue;
			break;
		case DATA_TYPE_INT8:
			bValue = (0 != vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			bValue = (0 != vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			bValue = (0 != vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			bValue = (0 != vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			bValue = (0 != vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			bValue = (0 != vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			bValue = (0 != vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			bValue = (0 != vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			bValue = (0 != vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			bValue = (0 != vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			if (strlen(vrValue.unValue.szValue) > 0) {
				if (0 == strcmp(vrValue.unValue.szValue, "yes") ||
					0 == strcmp(vrValue.unValue.szValue, "YES") ||
					0 == strcmp(vrValue.unValue.szValue, "true") ||
					0 == strcmp(vrValue.unValue.szValue, "True") ||
					0 == strcmp(vrValue.unValue.szValue, "ON") ||
					0 == strcmp(vrValue.unValue.szValue, "on") ||
					0 != atoi(vrValue.unValue.szValue)) {
					bValue = true;
				}
			}
			break;
		}
		return true;
	}
	bool GetValue(int8& cValue) {
		cValue = 0;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			cValue = static_cast<int8>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			cValue = static_cast<int8>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			cValue = static_cast<int8>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			cValue = static_cast<int8>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			cValue = static_cast<int8>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			cValue = static_cast<int8>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			cValue = static_cast<int8>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			cValue = static_cast<int8>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			cValue = static_cast<int8>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			cValue = static_cast<int8>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			cValue = static_cast<int8>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			cValue = static_cast<int8>(atoi(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(uint8& ucValue) {
		ucValue = 0;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			ucValue = static_cast<uint8>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			ucValue = static_cast<uint8>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			ucValue = static_cast<uint8>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			ucValue = static_cast<uint8>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			ucValue = static_cast<uint8>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			ucValue = static_cast<uint8>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			ucValue = static_cast<uint8>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			ucValue = static_cast<uint8>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			ucValue = static_cast<uint8>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			ucValue = static_cast<uint8>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			ucValue = static_cast<uint8>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			ucValue = static_cast<uint8>(atoi(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(int16& sValue) {
		sValue = 0;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			sValue = static_cast<int16>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			sValue = static_cast<int16>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			sValue = static_cast<int16>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			sValue = static_cast<int16>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			sValue = static_cast<int16>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			sValue = static_cast<int16>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			sValue = static_cast<int16>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			sValue = static_cast<int16>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			sValue = static_cast<int16>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			sValue = static_cast<int16>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			sValue = static_cast<int16>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			sValue = static_cast<int16>(atoi(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(uint16& usValue) {
		usValue = 0;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			usValue = static_cast<uint16>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			usValue = static_cast<uint16>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			usValue = static_cast<uint16>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			usValue = static_cast<uint16>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			usValue = static_cast<uint16>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			usValue = static_cast<uint16>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			usValue = static_cast<uint16>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			usValue = static_cast<uint16>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			usValue = static_cast<uint16>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			usValue = static_cast<uint16>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			usValue = static_cast<uint16>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			usValue = static_cast<uint16>(atoi(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(int32& iValue) {
		iValue = 0;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			iValue = static_cast<int32>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			iValue = static_cast<int32>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			iValue = static_cast<int32>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			iValue = static_cast<int32>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			iValue = static_cast<int32>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			iValue = static_cast<int32>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			iValue = static_cast<int32>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			iValue = static_cast<int32>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			iValue = static_cast<int32>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			iValue = static_cast<int32>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			iValue = static_cast<int32>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			iValue = static_cast<int32>(atol(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(uint32& uiValue) {
		uiValue = 0;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			uiValue = static_cast<uint32>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			uiValue = static_cast<uint32>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			uiValue = static_cast<uint32>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			uiValue = static_cast<uint32>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			uiValue = static_cast<uint32>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			uiValue = static_cast<uint32>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			uiValue = static_cast<uint32>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			uiValue = static_cast<uint32>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			uiValue = static_cast<uint32>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			uiValue = static_cast<uint32>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			uiValue = static_cast<uint32>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			uiValue = static_cast<uint32>(atol(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(int64& llValue) {
		llValue = 0;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			llValue = static_cast<int64>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			llValue = static_cast<int64>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			llValue = static_cast<int64>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			llValue = static_cast<int64>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			llValue = static_cast<int64>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			llValue = static_cast<int64>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			llValue = static_cast<int64>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			llValue = static_cast<int64>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			llValue = static_cast<int64>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			llValue = static_cast<int64>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			llValue = static_cast<int64>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			llValue = static_cast<int64>(atoll(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(uint64& ullValue) {
		ullValue = 0;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			ullValue = static_cast<uint64>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			ullValue = static_cast<uint64>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			ullValue = static_cast<uint64>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			ullValue = static_cast<uint64>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			ullValue = static_cast<uint64>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			ullValue = static_cast<uint64>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			ullValue = static_cast<uint64>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			ullValue = static_cast<uint64>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			ullValue = static_cast<uint64>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			ullValue = static_cast<uint64>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			ullValue = static_cast<uint64>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			ullValue = static_cast<uint64>(atoll(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(float& fValue) {
		fValue = 0.0f;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			fValue = static_cast<float>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			fValue = static_cast<float>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			fValue = static_cast<float>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			fValue = static_cast<float>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			fValue = static_cast<float>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			fValue = static_cast<float>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			fValue = static_cast<float>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			fValue = static_cast<float>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			fValue = static_cast<float>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			fValue = static_cast<float>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			fValue = static_cast<float>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			fValue = static_cast<float>(atof(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(double& dblValue) {
		dblValue = 0.0f;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			dblValue = static_cast<double>(vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			dblValue = static_cast<double>(vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			dblValue = static_cast<double>(vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			dblValue = static_cast<double>(vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			dblValue = static_cast<double>(vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			dblValue = static_cast<double>(vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			dblValue = static_cast<double>(vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			dblValue = static_cast<double>(vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			dblValue = static_cast<double>(vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			dblValue = static_cast<double>(vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			dblValue = static_cast<double>(vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			dblValue = static_cast<double>(atof(vrValue.unValue.szValue));
			break;
		}
		return true;
	}
	bool GetValue(uint8& ucRelType, yd::VRVALUE* pValue) {
		if (nullptr == pValue) {
			return false;
		}
		ucRelType = ucType;
		memcpy(pValue, &vrValue, sizeof(yd::VRVALUE));
		return true;
	}
	bool GetValue(yd::COORDS* pCoords) {
		if (DATA_TYPE_AXIS_COORD != ucType || nullptr == pCoords) {
			return false;
		}
		memcpy(pCoords, &vrValue.unValue.coords, sizeof(yd::COORDS));
		return true;
	}

	// 获取字符串数值
	bool GetStringValue(std::string& strValue) {
		bool bResult = true;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.bValue ? 1 : 0);
			break;
		case DATA_TYPE_INT8:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			strValue = yd::CStringHelper::Format("%d", vrValue.unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			strValue = yd::CStringHelper::Format("%u", vrValue.unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			strValue = yd::CStringHelper::Format("%lld", vrValue.unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			strValue = yd::CStringHelper::Format("%llu", vrValue.unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			strValue = yd::CStringHelper::Format("%f", vrValue.unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			strValue = yd::CStringHelper::Format("%lf", vrValue.unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			strValue = vrValue.unValue.szValue;
			break;
		case DATA_TYPE_AXIS_COORD:
			yd::CRapidJsonHelper::AxisCoords2Json(&vrValue.unValue.coords, strValue);
			break;
		default:
			break;
		}
		return bResult;
	}

	// 是否相同
	bool IsSame(CVRValue* pValue) {
		if (this->GetType() != pValue->GetType()) {
			return false;
		}
		bool bResult = false;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			bResult = this->IsSame(pValue->Value()->unValue.bValue);
			break;
		case DATA_TYPE_INT8:
			bResult = this->IsSame(pValue->Value()->unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			bResult = this->IsSame(pValue->Value()->unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			bResult = this->IsSame(pValue->Value()->unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			bResult = this->IsSame(pValue->Value()->unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			bResult = this->IsSame(pValue->Value()->unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			bResult = this->IsSame(pValue->Value()->unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			bResult = this->IsSame(pValue->Value()->unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			bResult = this->IsSame(pValue->Value()->unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			bResult = this->IsSame(pValue->Value()->unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			bResult = this->IsSame(pValue->Value()->unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			bResult = this->IsSame(pValue->Value()->unValue.szValue);
			break;
		case DATA_TYPE_AXIS_COORD:
			bResult = this->IsSame(&pValue->Value()->unValue.coords);
			break;
		default:
			break;
		}
		return bResult;
	}
	bool IsSame(const std::string& strValue) {
		if (DATA_TYPE_STRING != ucType) {
			return false;
		}
		return (0 == strValue.compare(vrValue.unValue.szValue));
	}
	bool IsSame(const bool& bValue) {
		if (DATA_TYPE_BOOL != ucType) {
			return false;
		}
		return (bValue == vrValue.unValue.bValue);
	}
	bool IsSame(const int8& cValue) {
		if (DATA_TYPE_INT8 != ucType) {
			return false;
		}
		return (cValue == vrValue.unValue.cValue);
	}
	bool IsSame(const uint8& ucValue) {
		if (DATA_TYPE_UINT8 != ucType) {
			return false;
		}
		return (ucValue == vrValue.unValue.ucValue);
	}
	bool IsSame(const int16& sValue) {
		if (DATA_TYPE_INT16 != ucType) {
			return false;
		}
		return (sValue == vrValue.unValue.sValue);
	}
	bool IsSame(const uint16& usValue) {
		if (DATA_TYPE_UINT16 != ucType) {
			return false;
		}
		return (usValue == vrValue.unValue.usValue);
	}
	bool IsSame(const int32& iValue) {
		if (DATA_TYPE_INT32 != ucType) {
			return false;
		}
		return (iValue == vrValue.unValue.iValue);
	}
	bool IsSame(const uint32& uiValue) {
		if (DATA_TYPE_UINT32 != ucType) {
			return false;
		}
		return (uiValue == vrValue.unValue.uiValue);
	}
	bool IsSame(const int64& llValue) {
		if (DATA_TYPE_INT64 != ucType) {
			return false;
		}
		return (llValue == vrValue.unValue.llValue);
	}
	bool IsSame(const uint64& ullValue) {
		if (DATA_TYPE_UINT64 != ucType) {
			return false;
		}
		return (ullValue == vrValue.unValue.ullValue);
	}
	bool IsSame(const float& fValue) {
		if (DATA_TYPE_FLOAT != ucType) {
			return false;
		}
		return (fValue == vrValue.unValue.fValue);
	}
	bool IsSame(const double& dblValue) {
		if (DATA_TYPE_DOUBLE != ucType) {
			return false;
		}
		return (dblValue == vrValue.unValue.dblValue);
	}
	bool IsSame(const uint8& ucRelType, const yd::VRVALUE* pValue) {
		if (ucRelType != ucType || nullptr == pValue) {
			return false;
		}
		bool bResult = false;
		switch (ucType) {
		case DATA_TYPE_BOOL:
			bResult = this->IsSame(pValue->unValue.bValue);
			break;
		case DATA_TYPE_INT8:
			bResult = this->IsSame(pValue->unValue.cValue);
			break;
		case DATA_TYPE_UINT8:
			bResult = this->IsSame(pValue->unValue.ucValue);
			break;
		case DATA_TYPE_INT16:
			bResult = this->IsSame(pValue->unValue.sValue);
			break;
		case DATA_TYPE_UINT16:
			bResult = this->IsSame(pValue->unValue.usValue);
			break;
		case DATA_TYPE_INT32:
			bResult = this->IsSame(pValue->unValue.iValue);
			break;
		case DATA_TYPE_UINT32:
			bResult = this->IsSame(pValue->unValue.uiValue);
			break;
		case DATA_TYPE_INT64:
		case DATA_TYPE_MEMORY_ADDR:
			bResult = this->IsSame(pValue->unValue.llValue);
			break;
		case DATA_TYPE_UINT64:
			bResult = this->IsSame(pValue->unValue.ullValue);
			break;
		case DATA_TYPE_FLOAT:
			bResult = this->IsSame(pValue->unValue.fValue);
			break;
		case DATA_TYPE_DOUBLE:
			bResult = this->IsSame(pValue->unValue.dblValue);
			break;
		case DATA_TYPE_STRING:
			bResult = this->IsSame(std::string(pValue->unValue.szValue));
			break;
		case DATA_TYPE_AXIS_COORD:
			bResult = this->IsSame(&pValue->unValue.coords);
			break;
		}
		return bResult;
	}
	bool IsSame(const yd::COORDS* pCoords) {
		if (DATA_TYPE_AXIS_COORD != ucType || nullptr == pCoords) {
			return false;
		}
		if (vrValue.unValue.coords.ucNumber != pCoords->ucNumber ||
			vrValue.unValue.coords.ucCtrlType != pCoords->ucCtrlType) {
			return false;
		}
		for (uint8 i = 0; i < vrValue.unValue.coords.ucNumber; i++) {
			if (vrValue.unValue.coords.arrCoords[i].usCard != pCoords->arrCoords[i].usCard ||
				vrValue.unValue.coords.arrCoords[i].usAxis != pCoords->arrCoords[i].usAxis ||
				vrValue.unValue.coords.arrCoords[i].ucType != pCoords->arrCoords[i].ucType ||
				vrValue.unValue.coords.arrCoords[i].refTarget.dblValue != pCoords->arrCoords[i].refTarget.dblValue ||
				vrValue.unValue.coords.arrCoords[i].refVelocity.dblValue != pCoords->arrCoords[i].refVelocity.dblValue) {
				return false;
			}
		}
		return true;
	}

	// 设置/获取类型
	void SetType(uint8 ucRelType) {
		ucType = ucRelType;
	}
	uint8 GetType() const {
		return ucType;
	}

	// 设置/获取时间戳
	void SetTimestamp(uint64 ullRelTimestamp) {
		vrValue.ullTimestamp = ullRelTimestamp;
	}
	uint64 GetTimestamp() const {
		return vrValue.ullTimestamp;
	}

	// 数值地址
	yd::VRVALUE* Value() {
		return &vrValue;
	}

private:
	yd::VRVALUE		vrValue;
	uint8			ucType;
};
using CVRValuePtr = std::shared_ptr<CVRValue>;
using MapUint2CVRValuePtr = std::map<uint32, CVRValuePtr>;
using MapBigUint2CVRValuePtr = std::map<uint64, CVRValuePtr>;
using MapString2CVRValuePtr = std::map<std::string, CVRValuePtr>;
using MapString2CVRValue = std::map<std::string, CVRValue>;
