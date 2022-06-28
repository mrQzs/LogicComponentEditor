#pragma once

#include "StringHelper.h"
#include "SystemHelper.h"
#include "TinyxmlHelper.h"
#include "yddef.h"

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
			std::vector<std::string> listProjectNames;
			if (!yd::CProjectHelper::EnumerateProjectNames(CONFIG_PATH_NAME, listProjectNames)) {
				strErrorMsg = "没有一个有效的项目";
				return false;
			}
			m_strProjectName = listProjectNames[0];
			m_strProjectFilePath = yd::CProjectHelper::GenerateProjectCfgFilePath(m_strWorkingDirectory + std::string(CONFIG_PATH_NAME), m_strProjectName);

			return true;
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
