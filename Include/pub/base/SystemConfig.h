#pragma once

#include "StringHelper.h"
#include "SystemHelper.h"
#include "TinyxmlHelper.h"
#include "yddef.h"
#include <algorithm>

// 系统配置类
namespace yd
{
	class CSystemConfig
	{
	private:
		std::string				m_strWorkingDirectory{ "" };
		uint32					m_uiVersion{ CURRENT_VERSION };
		uint8					m_ucFormat{ CURRENT_CONFIG_FORMAT };
		std::string				m_strProjectName{ "" };
		std::string				m_strProjectFilePath{ "" };
		std::string				m_strRecipeName{ "" };
		std::string				m_strRecipeFilePath{ "" };
		bool					m_bChanged{ false };

	public:
		CSystemConfig() {
			m_strWorkingDirectory = yd::CFileHelper::GetMainWorkingDirectory();
		}

	public:
		// 唯一实例
		static CSystemConfig* Instance() {
			static CSystemConfig cfg;
			return &cfg;
		}

	public:
		// 加载配置
		bool Load(std::string& strErrorMsg) {
			// 工作配置文件
			std::string strFilePath = "";
			if (std::string::npos != m_strWorkingDirectory.find("\\")) {
				strFilePath = CFileHelper::NormalizeDirectory(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME)) + std::string("\\") + std::string("System.xml");
			}
			else {
				strFilePath = CFileHelper::NormalizeDirectory(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME)) + std::string("/") + std::string("System.xml");
			}
			// 文件不存在
			if (!yd::CFileHelper::FileExists(strFilePath)) {
				strErrorMsg = "配置文件不存在";
				return false;
			}
			tinyxml2::XMLDocument xmlDoc;
			int32 xmlError = xmlDoc.LoadFile(strFilePath.c_str());
			if (tinyxml2::XML_SUCCESS != xmlError) {
				strErrorMsg = xmlDoc.ErrorStr();
				xmlDoc.Clear();
				return false;
			}
			tinyxml2::XMLElement* pXmlSystem = xmlDoc.RootElement();
			if (nullptr == pXmlSystem) {
				strErrorMsg = "配置文件格式错误：<system></system>不存在";
				xmlDoc.Clear();
				return false;
			}
			tinyxml2::XMLElement* pXmlProject = pXmlSystem->FirstChildElement("project");
			if (nullptr == pXmlProject) {
				strErrorMsg = "配置文件格式错误：<project></project>不存在";
				xmlDoc.Clear();
				return false;
			}
			// 项目配置信息
			m_strProjectName = yd::CStringHelper::UTF8ToGB2312(yd::CTinyxmlHelper::GetAttributeValue(pXmlProject, "name", nullptr));
			m_strRecipeName = yd::CStringHelper::UTF8ToGB2312(yd::CTinyxmlHelper::GetAttributeValue(pXmlProject, "recipe", nullptr));
			m_uiVersion = yd::CTinyxmlHelper::GetAttributeValue(pXmlProject, "version", (uint32)0);
			std::string strFormat = yd::CStringHelper::UTF8ToGB2312(yd::CTinyxmlHelper::GetAttributeValue(pXmlProject, "format", nullptr));
			xmlDoc.Clear();
			if (!yd::CProjectHelper::IsProjectExisting(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME), m_strProjectName)) {
				strErrorMsg = yd::CStringHelper::Format("项目(%s)不存在", m_strProjectName.c_str());
				return false;
			}
			if (!yd::CProjectHelper::IsProjectRecipeExisting(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME), m_strProjectName, m_strRecipeName)) {
				strErrorMsg = yd::CStringHelper::Format("项目(%s)配方(%s)不存在", m_strProjectName.c_str(), m_strRecipeName.c_str());
				return false;
			}
			m_strProjectFilePath = yd::CProjectHelper::GenerateProjectCfgFilePath(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME), m_strProjectName);
			m_strRecipeFilePath = yd::CProjectHelper::GenerateProjectRecipeCfgFilePath(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME), m_strProjectName, m_strRecipeName);
			std::transform(strFormat.begin(), strFormat.end(), strFormat.begin(), ::tolower);
			if (0 == strFormat.compare("xml")) {
				m_ucFormat = CONFIG_FORMA_XML;
			}
			else if (0 == strFormat.compare("sqlite")) {
				m_ucFormat = CONFIG_FORMA_SQLITE;
			}
			else if (0 == strFormat.compare("mysql")) {
				m_ucFormat = CONFIG_FORMA_MYSQL;
			}
			if (m_ucFormat < CONFIG_FORMA_XML || m_ucFormat > CONFIG_FORMA_MYSQL) {
				strErrorMsg = yd::CStringHelper::Format("配置格式(%d)不支持", m_ucFormat);
				return false;
			}
			return true;
		}

		// 保存配置
		bool Save() {
			if (!m_bChanged) {
				return true;
			}
			// 工作配置文件
			std::string strFilePath = "";
			if (std::string::npos != m_strWorkingDirectory.find("\\")) {
				strFilePath = CFileHelper::NormalizeDirectory(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME)) + std::string("\\") + std::string("System.xml");
			}
			else {
				strFilePath = CFileHelper::NormalizeDirectory(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME)) + std::string("/") + std::string("System.xml");
			}
			// 序列化
			tinyxml2::XMLDocument xmlDoc;
			xmlDoc.Parse("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
			tinyxml2::XMLElement* pXmlSystem = xmlDoc.NewElement("system");
			if (nullptr == pXmlSystem) {
				return false;
			}
			xmlDoc.InsertEndChild(pXmlSystem);
			tinyxml2::XMLElement* pXmlProject = xmlDoc.NewElement("project");
			if (nullptr == pXmlProject) {
				return false;
			}
			pXmlSystem->InsertEndChild(pXmlProject);
			pXmlProject->SetAttribute("version", (int64_t)m_uiVersion);
			std::string strFormat = "";
			switch (m_ucFormat) {
			case CONFIG_FORMA_XML:
				strFormat = "xml";
				break;
			case CONFIG_FORMA_SQLITE:
				strFormat = "sqlite";
				break;
			case CONFIG_FORMA_MYSQL:
				strFormat = "mysql";
				break;
			}
			pXmlProject->SetAttribute("format", yd::CStringHelper::GB2312ToUTF8(strFormat).c_str());
			pXmlProject->SetAttribute("name", yd::CStringHelper::GB2312ToUTF8(m_strProjectName).c_str());
			pXmlProject->SetAttribute("recipe", yd::CStringHelper::GB2312ToUTF8(m_strRecipeName).c_str());
			// 写入文件
			int32 xmlError = xmlDoc.SaveFile(strFilePath.c_str());
			xmlDoc.Clear();
			if (tinyxml2::XML_SUCCESS == xmlError) {
				m_bChanged = false;
			}
			return (tinyxml2::XML_SUCCESS == xmlError);
		}

		// 获取版本号
		uint32 GetVersion() const {
			return m_uiVersion;
		}

		// 获取配置格式
		uint8 GetFormat() const {
			return m_ucFormat;
		}

		// 获取项目名称
		const char* GetProjectName() const {
			return m_strProjectName.c_str();
		}

		// 更新项目名称
		bool SetProjectName(const std::string& strProjectName) {
			if (0 != m_strProjectName.compare(strProjectName)) {
				m_bChanged = true;
			}
			m_strProjectName = strProjectName;
			if (!m_strProjectName.empty()) {
				m_strProjectFilePath = yd::CProjectHelper::GenerateProjectCfgFilePath(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME), m_strProjectName);
			}
			return !m_strProjectName.empty();
		}

		// 获取项目参数路径
		const char* GetProjectFilePath() const {
			return m_strProjectFilePath.c_str();
		}

		// 获取配方名称
		const char* GetRecipeName() const {
			return m_strRecipeName.c_str();
		}

		// 更新配方名称
		bool SetRecipeName(const std::string& strRecipeName) {
			if (0 != m_strRecipeName.compare(strRecipeName)) {
				m_bChanged = true;
			}
			m_strRecipeName = strRecipeName;
			if (!m_strRecipeName.empty()) {
				m_strRecipeFilePath = yd::CProjectHelper::GenerateProjectRecipeCfgFilePath(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME), m_strProjectName, m_strRecipeName);
			}
			return !m_strRecipeName.empty();
		}

		// 获取配方参数路径
		const char* GetRecipeFilePath() const {
			return m_strRecipeFilePath.c_str();
		}
	};
}
