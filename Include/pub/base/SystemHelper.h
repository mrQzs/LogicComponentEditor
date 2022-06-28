#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <chrono>
#include <thread>
#include <platform.h>
#include <direct.h>
#include <sys/stat.h>
#include "StringHelper.h"

namespace yd {
	// 系统协助类
	class CSystemHelper
	{
	public:
		// 当前进程id
		static uint32 CurrentProcessId() {
#ifdef _WIN32
			return static_cast<uint32>(::GetCurrentProcessId());
#else
#endif
		}

		// 当前线程id
		static uint32 CurrentThreadId() {
			return static_cast<uint32>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
		}

		// 模块名称
		static std::string CurrentModuleName() {
			std::string strModuleName = "";
#ifdef _WIN32
			char szModule[256] = { 0x00 };
			::GetModuleFileNameA(NULL, szModule, 256);
			strModuleName = szModule;
			size_t pos = strModuleName.rfind("\\");
			if (std::string::npos != pos) {
				strModuleName = strModuleName.substr(pos + 1, strModuleName.length() - pos - 1);
			}
			pos = strModuleName.rfind(".exe");
			if (std::string::npos != pos) {
				strModuleName = strModuleName.substr(0, pos);
			}
#else
#endif
			return strModuleName;
		}

		// 生成方法实例摘要
		static std::string GenerateMethodDigest(uint32 uiMainId, uint32 uiSubId, const std::string& strMainName, const std::string& strSubName, std::string(*pEncodeFunction)(const std::string&)) {
			std::string strSource = yd::CStringHelper::Format("%s_%s_%u_%u", strMainName.c_str(), strSubName.c_str(), uiMainId, uiSubId);
			if (nullptr != pEncodeFunction) {
				return (*pEncodeFunction)(strSource);
			}
			else {
				return strSource;
			}
		}

		// 生成运动设备方法实例摘要
		static std::string GenerateMotionMethodDigest(uint32 uiDeviceId, uint16 usAxis, const std::string& strMethodName, std::string(*pEncodeFunction)(const std::string&)) {
			return CSystemHelper::GenerateMethodDigest(uiDeviceId, usAxis, strMethodName, "", pEncodeFunction);
		}

		// 生成逻辑流程方法实例摘要
		static std::string GenerateProcessMethodDigest(uint32 uiProcessId, uint32 uiDeviceId, const std::string& strMethodName, std::string(*pEncodeFunction)(const std::string&)) {
			return CSystemHelper::GenerateMethodDigest(uiProcessId, uiDeviceId, strMethodName, "", pEncodeFunction);
		}
	};

	// 时间计时器
	class CDuration
	{
	public:
		CDuration() {
			m_begin = std::chrono::high_resolution_clock::now();
		}

	public:
		// 获取微秒
		int64 GetMicroseconds() {
			std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::microseconds>(end - m_begin).count();
		}

		// 获取毫秒
		int64 GetMilliseconds() {
			return this->GetMicroseconds() / 1000;
		}

		// 获取秒
		int64 GetSeconds() {
			return this->GetMicroseconds() / 1000000;
		}

		// 更新
		void Update() {
			m_begin = std::chrono::high_resolution_clock::now();
		}
	private:
		std::chrono::high_resolution_clock::time_point	m_begin;
	};

	// 时间戳类
	class CTimestamp
	{
	public:
		// 获取当前时间：微秒
		static uint64 GetCurrentMicroseconds() {
			return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		}

		// 获取当前时间：毫秒
		static uint64 GetCurrentMilliseconds() {
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		}

		// 获取当前时间：秒
		static uint64 GetCurrentSeconds() {
			return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		}

		// 获取当前时间：格式化字符串 - YYYY-MM-DD hh:mm:ss
		static std::string GetCurrentFormatTime() {
			std::chrono::system_clock::time_point tm_pt = std::chrono::system_clock::now();
			uint64 ullMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(tm_pt.time_since_epoch()).count();
			time_t cur_time = std::chrono::system_clock::to_time_t(tm_pt);
			char szBuffer[60 + 1] = { 0x00 };
			struct tm cur_tm; localtime_s(&cur_tm, &cur_time);
			std::strftime(szBuffer, sizeof(szBuffer), "%Y-%m-%d %H:%M:%S", &cur_tm);
			std::string strMilliSeconds = CStringHelper::Format("%.06llu", ullMicroseconds % 1000000);

			return std::string(szBuffer) + std::string(".") + strMilliSeconds;
		}

		// 格式化时间 - YYYY-MM-DD hh:mm:ss
		static std::string FormatTimeFromMicroseconds(uint64 ullMicroseconds) {
			time_t cur_time = (time_t)(ullMicroseconds / 1000000);
			char szBuffer[40 + 1] = { 0x00 };
			struct tm cur_tm; localtime_s(&cur_tm, &cur_time);
			std::strftime(szBuffer, sizeof(szBuffer), "%Y-%m-%d %H:%M:%S", &cur_tm);
			std::string strMilliSeconds = CStringHelper::Format("%.06llu", ullMicroseconds % 1000000);

			return std::string(szBuffer) + std::string(".") + strMilliSeconds;
		}

		// 日期时间转微秒
		static uint64 DateTime2UnixMicroseconds(const std::string& strDateTime) {
			return 0;
		}

		// 获取当前日期：格式化字符串 - YYYY-MM-DD
		static std::string GetCurrentFormatDate() {
			return CTimestamp::GetCurrentFormatTime().substr(0, 10);
		}

		// 获取指定天数之前的日期：格式化字符串 - YYYY-MM-DD
		static std::string GetFormateDateDaysBefore(uint16 usDays) {
			time_t cur_time = (time_t)(time(nullptr) - (time_t)usDays * 24 * 3600);
			char szBuffer[60 + 1] = { 0x00 };
			struct tm cur_tm; localtime_s(&cur_tm, &cur_time);
			std::strftime(szBuffer, sizeof(szBuffer), "%Y-%m-%d", &cur_tm);
			return szBuffer;
		}
	};

	// 日期时间类
	class CDateTime
	{
	public:
		// 静态方法
		static CDateTime GetCurrentDateTime() {
			return CDateTime();
		}
		static CDateTime GetDateTimeDiff(int iDays) {
			return CDateTime(time(nullptr) + (time_t)iDays * 24 * 3600);
		}
		static int GetMonthDays(int iYear, int iMonth) {
			switch (iMonth) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				return 31;
			case 2:
				return CDateTime::IsLeapYear(iYear) ? 29 : 28;
			default:
				return 30;
			}
		}
		static int GetYearDays(int iYear) {
			return (CDateTime::IsLeapYear(iYear) ? 366 : 365);
		}
		static bool IsLeapYear(int iYear) {
			if (0 == (iYear % 400)) {
				return true;
			}
			else {
				if (0 == (iYear % 4) && 0 != (iYear % 100)) {
					return true;
				}
				else {
					return false;
				}
			}
		}

	public:
		// 构造函数
		CDateTime() {
			m_timestamp = time(nullptr);
			this->ToLocalTime();
		}
		CDateTime(const CDateTime& ref) {
			this->m_timestamp = ref.m_timestamp;
			this->ToLocalTime();
		}
		CDateTime(const time_t ref) {
			m_timestamp = ref;
			this->ToLocalTime();
		}
		CDateTime(const struct tm* ref) {
			m_timestamp = mktime((struct tm*)ref);
			this->ToLocalTime();
		}

	public:
		// 赋值运算符
		CDateTime& operator=(const CDateTime& ref) {
			if (this == &ref) {
				return *this;
			}
			this->m_timestamp = ref.m_timestamp;
			this->ToLocalTime();
			return *this;
		}
		CDateTime& operator=(const time_t ref) {
			m_timestamp = ref;
			this->ToLocalTime();
			return *this;
		}
		CDateTime& operator=(const struct tm* ref) {
			m_timestamp = mktime((struct tm*)ref);
			this->ToLocalTime();
			return *this;
		}

	public:
		// 比较运算
		bool operator==(const CDateTime& ref) {
			return (this->m_timestamp == ref.m_timestamp);
		}
		bool operator!=(const CDateTime& ref) {
			return (this->m_timestamp != ref.m_timestamp);
		}
		bool operator>(const CDateTime& ref) {
			return (this->m_timestamp > ref.m_timestamp);
		}
		bool operator<(const CDateTime& ref) {
			return (this->m_timestamp < ref.m_timestamp);
		}
		bool operator>=(const CDateTime& ref) {
			return (this->m_timestamp >= ref.m_timestamp);
		}
		bool operator<=(const CDateTime& ref) {
			return (this->m_timestamp <= ref.m_timestamp);
		}

	public:
		// 条件判定
		bool IsSameYear(const CDateTime& dtToCompare) const {
			return (this->GetYear() == dtToCompare.GetYear());
		}
		bool IsNextYear(const CDateTime& dtToCompare) const {
			return (this->GetYear() > dtToCompare.GetYear());
		}
		bool IsPreviousYear(const CDateTime& dtToCompare) const {
			return (!this->IsSameYear(dtToCompare) && !this->IsNextYear(dtToCompare));
		}
		bool IsSameMonth(const CDateTime& dtToCompare) const {
			return (this->IsSameYear(dtToCompare) && this->GetMonth() == dtToCompare.GetMonth());
		}
		bool IsNextMonth(const CDateTime& dtToCompare) const {
			if (this->IsSameYear(dtToCompare)) {
				return (this->GetMonth() > dtToCompare.GetMonth());
			}
			else {
				return this->IsNextYear(dtToCompare);
			}
		}
		bool IsPreviousMonth(const CDateTime& dtToCompare) const {
			return (!this->IsSameMonth(dtToCompare) && !this->IsNextMonth(dtToCompare));
		}
		bool IsSameDay(const CDateTime& dtToCompare) const {
			return (this->IsSameMonth(dtToCompare) && this->GetDay() == dtToCompare.GetDay());
		}
		bool IsNextDay(const CDateTime& dtToCompare) const {
			if (this->IsSameMonth(dtToCompare)) {
				return (this->GetDay() > dtToCompare.GetDay());
			}
			else {
				return (this->IsNextYear(dtToCompare) || this->IsNextMonth(dtToCompare));
			}
		}
		bool IsPreviousDay(const CDateTime& dtToCompare) const {
			return (!this->IsSameDay(dtToCompare) && !this->IsNextDay(dtToCompare));
		}

	public:
		// 属性
		time_t GetTimestamp() const {
			return m_timestamp;
		}
		int GetYear() const {
			return m_localtime.tm_year + 1900;
		}
		int GetMonth() const {
			return m_localtime.tm_mon + 1;
		}
		int GetDay() const {
			return m_localtime.tm_mday;
		}
		int GetHour() const {
			return m_localtime.tm_hour;
		}
		int GetMinute() const {
			return m_localtime.tm_min;
		}
		int GetSecond() const {
			return m_localtime.tm_sec;
		}
		int GetDayOfYear() const {
			return m_localtime.tm_yday + 1;
		}
		int GetDayOfWeek() const {
			return m_localtime.tm_wday + 1;
		}

	private:
		// 解析时间
		void ToLocalTime() {
			localtime_s(&m_localtime, &m_timestamp);
		}

	private:
		time_t		m_timestamp;
		struct tm	m_localtime;
	};

	// 文件协助类
	class CFileHelper
	{
	public:
		// 文件（夹）信息
		typedef struct _FileInfo {
		public:
			std::string		strFileName;
			std::string		strLastModified;
		}FILEINFO;
		typedef std::vector<FILEINFO>	VEC_FILEINFOS;

	public:
		// 归一化目录
		static std::string NormalizeDirectory(const std::string& strDirectory) {
			if (std::string::npos != strDirectory.find("\\")) {
				if ('\\' != strDirectory[strDirectory.length() - 1]) {
					return strDirectory + "\\";
				}
				else {
					return strDirectory;
				}
			}
			else {
				if ('/' != strDirectory[strDirectory.length() - 1]) {
					return strDirectory + "/";
				}
				else {
					return strDirectory;
				}
			}
		}

		// 获取主程序目录
		static std::string GetMainWorkingDirectory(const std::string& strCurrentPath) {
			bool bWinStyle = (std::string::npos != strCurrentPath.find("\\"));
			std::string strPathToCheck = "";
			if (bWinStyle) {
				if (std::string::npos == strCurrentPath.find("\\")) {
					return CFileHelper::NormalizeDirectory(strCurrentPath);
				}
				if ('\\' != strCurrentPath[strCurrentPath.length() - 1]) {
					strPathToCheck = strCurrentPath + std::string("\\") + std::string(DEPENDENCE_PATH_NAME);
				}
				else {
					strPathToCheck = strCurrentPath + std::string(DEPENDENCE_PATH_NAME);
				}
			}
			else {
				if (std::string::npos == strCurrentPath.find("/")) {
					return CFileHelper::NormalizeDirectory(strCurrentPath);
				}
				if ('/' != strCurrentPath[strCurrentPath.length() - 1]) {
					strPathToCheck = strCurrentPath + std::string("/") + std::string(DEPENDENCE_PATH_NAME);
				}
				else {
					strPathToCheck = strCurrentPath + std::string(DEPENDENCE_PATH_NAME);
				}
			}
			if (CFileHelper::FileExists(strPathToCheck)) {
				return CFileHelper::NormalizeDirectory(strCurrentPath);
			}
			else {
				if (bWinStyle) {
					strPathToCheck = strCurrentPath.substr(0, strCurrentPath.rfind("\\"));
				}
				else {
					strPathToCheck = strCurrentPath.substr(0, strCurrentPath.rfind("/"));
				}
				return CFileHelper::GetMainWorkingDirectory(strPathToCheck);
			}
		}
		static std::string GetMainWorkingDirectory() {
			return CFileHelper::GetMainWorkingDirectory(std::filesystem::current_path().string());
		}

		// 判断文件是否存在
		static bool FileExists(const std::string& strFilePath) {
			return std::filesystem::exists(std::filesystem::path(strFilePath));
		}

		// 删除文件
		static bool DeleteFile(const std::string& strFilePath) {
			std::filesystem::path ptFile(strFilePath);
			if (std::filesystem::exists(ptFile)) {
				return std::filesystem::remove(ptFile);
			}
			return true;
		}

		// 获取文件大小
		static uint64 FileSize(const std::string& strFilePath) {
			std::filesystem::path ptFile(strFilePath);
			if (!std::filesystem::exists(ptFile)) {
				return 0;
			}
			return static_cast<uint64>(std::filesystem::file_size(ptFile));
		}

		// 读取文件
		static uint64 GetFile(const std::string& strFilePath, char* lpszBuffer, uint64 ullBufferSize) {
			if (!CFileHelper::FileExists(strFilePath)) {
				return 0;
			}
			uint64 ullReadSize = CFileHelper::FileSize(strFilePath);
			if (ullReadSize > ullBufferSize) {
				ullReadSize = ullBufferSize;
			}
			std::ifstream ifs(strFilePath.c_str(), std::ios::binary);
			if (!ifs.is_open()) {
				return 0;
			}
			ifs.read(lpszBuffer, ullReadSize);
			ifs.close();
			ullReadSize = strlen(lpszBuffer);
			lpszBuffer[ullReadSize] = '\0';
			return ullReadSize;
		}

		// 写入文件
		static uint64 SetFile(const std::string& strFilePath, const char* lpszBuffer, uint64 ullLength, bool bOverwrite = true) {
			if (bOverwrite) {
				if (CFileHelper::FileExists(strFilePath)) {
					CFileHelper::DeleteFile(strFilePath);
				}
			}
			std::ofstream ofs(strFilePath.c_str(), std::ios::binary | std::ios::app);
			if (!ofs.is_open()) {
				return 0;
			}
			ofs.write(nullptr != lpszBuffer ? lpszBuffer : "", ullLength);
			ofs.close();
			return CFileHelper::FileSize(strFilePath);
		}

		// 拷贝文件
		static bool CopyFile(const std::string& strSourceFile, const std::string& strDestFile) {
			std::filesystem::path ptSource(strSourceFile), ptDest(strDestFile);
			std::filesystem::copy_file(ptSource, ptDest, std::filesystem::copy_options::overwrite_existing);
			return std::filesystem::exists(ptDest);
		}

		// 拷贝文件夹
		static bool CopyDirectory(const std::string& strSourceDirectory, const std::string& strDestDirectory) {
			std::filesystem::path ptSource(strSourceDirectory), ptDest(strDestDirectory);
			std::filesystem::copy(ptSource, ptDest, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
			return std::filesystem::exists(ptDest);
		}

		// 创建文件夹
		static bool CreateDirectory(const std::string& strDirectory) {
			std::filesystem::path ptDir(strDirectory);
			if (std::filesystem::exists(ptDir)) {
				return true;
			}
			return std::filesystem::create_directory(ptDir);
		}
		static bool CreateDirectories(const std::string& strDirectories) {
			std::filesystem::path ptDirs(strDirectories);
			return std::filesystem::create_directories(ptDirs);
		}

		// 删除文件夹
		static bool DeleteDirectory(const std::string& strDirectory) {
			std::filesystem::path ptDir(strDirectory);
			if (!std::filesystem::exists(ptDir)) {
				return false;
			}
			return std::filesystem::remove_all(ptDir) > 0;
		}

		// 重命名文件夹
		static bool RenameDirectory(const std::string& strOldDirectoryName, const std::string& strNewDirectoryName) {
			std::filesystem::path ptOld(strOldDirectoryName), ptNew(strNewDirectoryName);
			if (!std::filesystem::exists(ptOld)) {
				return false;
			}
			std::filesystem::rename(ptOld, ptNew);
			return std::filesystem::exists(ptNew);
		}

		// 获取指定目录下所有子文件夹
		static bool GetSubDirectories(const std::string& strDirectory, std::vector<std::string>& listSubDirectories) {
			listSubDirectories.clear();
			std::filesystem::path ptDirectory(strDirectory);
			if (std::filesystem::exists(ptDirectory)) {
				for (const auto& entry : std::filesystem::directory_iterator(ptDirectory)) {
					if (entry.is_directory()) {
						listSubDirectories.push_back(entry.path().filename().string());
					}
				}
			}
			return !listSubDirectories.empty();
		}

		// 获取指定文件（夹）最后修改时间
		static std::string GetFileLastModifiedTime(const std::string& strPath) {
			std::filesystem::path pt(strPath);
			auto lastModified = std::filesystem::last_write_time(pt).time_since_epoch().count();
			lastModified -= 116444736000000000;
			lastModified /= 10000000;
			char szBuffer[40 + 1] = { 0x00 };
#ifdef _WIN32
			struct tm cur_tm; _localtime64_s(&cur_tm, &lastModified);
#else
#endif
			std::strftime(szBuffer, sizeof(szBuffer), "%Y-%m-%d %H:%M:%S", &cur_tm);
			return std::string(szBuffer);
		}

		// 获取指定文件夹下匹配前缀的文件
		static bool GetDirectoryFilesWithPrefixMatched(const std::string& strDirectory, const std::string& strPrefix, VEC_FILEINFOS& listFiles) {
			listFiles.clear();
			std::filesystem::path pt(strDirectory);
			if (std::filesystem::exists(pt)) {
				for (const auto& entry : std::filesystem::directory_iterator(pt)) {
					FILEINFO fileInfo;
					fileInfo.strFileName = entry.path().filename().string();
					fileInfo.strLastModified = CFileHelper::GetFileLastModifiedTime(strDirectory + std::string("/") + fileInfo.strFileName);
					if (!strPrefix.empty()) {
						if (std::string::npos != fileInfo.strFileName.find(strPrefix, 0)) {
							listFiles.push_back(fileInfo);
						}
					}
					else {
						listFiles.push_back(fileInfo);
					}
				}
			}

			return !listFiles.empty();
		}

		// 获取指定目录下设备组件库
		static bool GetDeviceComponentFiles(const std::string& strDirectory, VEC_FILEINFOS& listComponentFiles) {
			listComponentFiles.clear();
			std::filesystem::path pt(strDirectory);
			if (std::filesystem::exists(pt)) {
				for (const auto& entry : std::filesystem::directory_iterator(pt)) {
					FILEINFO fileInfo;
					fileInfo.strFileName = entry.path().filename().string();
					fileInfo.strLastModified = CFileHelper::GetFileLastModifiedTime(strDirectory + std::string("/") + fileInfo.strFileName);
					if (std::string::npos != fileInfo.strFileName.find("modDev_", 0) &&
						std::string::npos != fileInfo.strFileName.rfind(".dll")) {
						listComponentFiles.push_back(fileInfo);
					}
				}
			}
			return !listComponentFiles.empty();
		}
	};

	// 项目协助类
	class CProjectHelper
	{
	public:
		// 项目数据
		typedef struct _ProjectData {
			std::string							strProjectName;
			std::string							strProjectContent;
			std::map<std::string, std::string>	mapRecipeName2Content;
		}ProjectData;

	public:
		// 项目是否存在
		static bool IsProjectExisting(const std::string& strRootDirectory, const std::string& strProjectName) {
			return CFileHelper::FileExists(CProjectHelper::GenerateProjectDirectory(strRootDirectory, strProjectName));
		}

		// 配方是否存在
		static bool IsProjectRecipeExisting(const std::string& strRootDirectory, const std::string& strProjectName, const std::string& strRecipeName) {
			return CFileHelper::FileExists(CProjectHelper::GenerateProjectRecipeDirectory(strRootDirectory, strProjectName, strRecipeName));
		}

		// 更新项目名称
		static bool UpdateProjectName(const std::string& strRootDirectory, const std::string& strOldProjectName, const std::string& strNewProjectName) {
			std::string strOldDirectory = CProjectHelper::GenerateProjectDirectory(strRootDirectory, strOldProjectName);
			if (!CFileHelper::FileExists(strOldDirectory)) {
				return false;
			}
			std::string strNewDirectory = CProjectHelper::GenerateProjectDirectory(strRootDirectory, strNewProjectName);
			return CFileHelper::RenameDirectory(strOldDirectory, strNewDirectory);
		}

		// 更新配方名称
		static bool UpdateProjectRecipeName(const std::string& strRootDirectory, const std::string& strProjectName, const std::string& strOldRecipeName, const std::string& strNewRecipeName) {
			std::string strOldDirectory = CProjectHelper::GenerateProjectRecipeDirectory(strRootDirectory, strProjectName, strOldRecipeName);
			if (!CFileHelper::FileExists(strOldDirectory)) {
				return false;
			}
			std::string strNewDirectory = CProjectHelper::GenerateProjectRecipeDirectory(strRootDirectory, strProjectName, strNewRecipeName);
			return CFileHelper::RenameDirectory(strOldDirectory, strNewDirectory);
		}

		// 枚举所有项目名称
		static bool EnumerateProjectNames(const std::string& strRootDirectory, std::vector<std::string>& listProjectNames) {
			return CFileHelper::GetSubDirectories(strRootDirectory, listProjectNames);
		}

		// 枚举指定项目所有配方名称
		static bool EnumerateProjectRecipeNames(const std::string& strRootDirectory, const std::string& strProjectName, std::vector<std::string>& listRecipeNames) {
			return CFileHelper::GetSubDirectories(CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName, listRecipeNames);
		}

		// 创建项目文件夹
		static bool CreateProjectDirectory(const std::string& strRootDirectory, const std::string& strProjectName) {
			return CFileHelper::CreateDirectory(CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName);
		}

		// 创建指定项目配方文件夹
		static bool CreateProjectRecipeDirectory(const std::string& strRootDirectory, const std::string& strProjectName, const std::string& strRecipeName) {
			if (!CProjectHelper::CreateProjectDirectory(strRootDirectory, strProjectName)) {
				return false;
			}
			std::string strDirectory = CFileHelper::NormalizeDirectory(strRootDirectory);
			if (std::string::npos != strDirectory.find("\\")) {
				strDirectory += strProjectName + std::string("\\") + strRecipeName;
			}
			else {
				strDirectory += strProjectName + std::string("/") + strRecipeName;
			}
			return CFileHelper::CreateDirectory(strDirectory);
		}

		// 删除项目文件夹
		static bool DeleteProjectDirectory(const std::string& strRootDirectory, const std::string& strProjectName) {
			std::string strDirectory = CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName;
			return CFileHelper::DeleteDirectory(strDirectory);
		}

		// 删除配方文件夹
		static bool DeleteProjectRecipeDirectory(
			const std::string& strRootDirectory,
			const std::string& strProjectName,
			const std::string& strRecipeName) {
			std::string strDirectory = CFileHelper::NormalizeDirectory(strRootDirectory);
			if (std::string::npos != strRootDirectory.find("\\")) {
				strDirectory += strProjectName + std::string("\\") + strRecipeName;
			}
			else {
				strDirectory += strProjectName + std::string("/") + strRecipeName;
			}
			return CFileHelper::DeleteDirectory(strDirectory);
		}

		// 生成项目文件夹
		static std::string GenerateProjectDirectory(
			const std::string& strRootDirectory,
			const std::string& strProjectName) {
			return CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName;
		}

		// 生成配方文件夹
		static std::string GenerateProjectRecipeDirectory(
			const std::string& strRootDirectory,
			const std::string& strProjectName,
			const std::string& strRecipeName) {
			if (std::string::npos != strRootDirectory.find("\\")) {
				return CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName + std::string("\\") + strRecipeName;
			}
			else {
				return CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName + std::string("/") + strRecipeName;
			}
		}

		// 生成项目配置文件路径
		static std::string GenerateProjectCfgFilePath(
			const std::string& strRootDirectory,
			const std::string& strProjectName) {
			if (std::string::npos != strRootDirectory.find("\\")) {
				return CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName + std::string("\\") + std::string(PROJECT_CFG_NAME);
			}
			else {
				return CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName + std::string("/") + std::string(PROJECT_CFG_NAME);
			}
		}

		// 生成配方配置文件路径
		static std::string GenerateProjectRecipeCfgFilePath(
			const std::string& strRootDirectory,
			const std::string& strProjectName,
			const std::string& strRecipeName) {
			if (std::string::npos != strRootDirectory.find("\\")) {
				return CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName + std::string("\\") + strRecipeName + std::string("\\") + std::string(RECIPE_CFG_NAME);
			}
			else {
				return CFileHelper::NormalizeDirectory(strRootDirectory) + strProjectName + std::string("/") + strRecipeName + std::string("/") + std::string(RECIPE_CFG_NAME);
			}
		}

		// 读取项目文件
		static uint64 ReadProjectCfgFile(
			const std::string& strRootDirectory,
			const std::string& strProjectName,
			char* lpszBuffer,
			uint64 ullBufferSize) {
			std::string strFilePath = CProjectHelper::GenerateProjectCfgFilePath(
				strRootDirectory,
				strProjectName);
			return CFileHelper::GetFile(strFilePath, lpszBuffer, ullBufferSize);
		}

		// 写入项目文件
		static uint64 WriteProjectCfgFile(
			const std::string& strRootDirectory,
			const std::string& strProjectName,
			const char* lpszBuffer,
			uint64 ullLength) {
			std::string strFilePath = CProjectHelper::GenerateProjectCfgFilePath(
				strRootDirectory,
				strProjectName);
			return CFileHelper::SetFile(strFilePath, lpszBuffer, ullLength);
		}

		// 读取配方文件
		static uint64 ReadProjectRecipeCfgFile(
			const std::string& strRootDirectory,
			const std::string& strProjectName,
			const std::string& strRecipeName,
			char* lpszBuffer,
			uint64 ullBufferSize) {
			std::string strFilePath = CProjectHelper::GenerateProjectRecipeCfgFilePath(
				strRootDirectory,
				strProjectName,
				strRecipeName);
			return CFileHelper::GetFile(strFilePath, lpszBuffer, ullBufferSize);
		}

		// 写入配方文件
		static uint64 WriteProjectRecipeCfgFile(
			const std::string& strRootDirectory,
			const std::string& strProjectName,
			const std::string& strRecipeName,
			const char* lpszBuffer,
			uint64 ullLength) {
			std::string strFilePath = CProjectHelper::GenerateProjectRecipeCfgFilePath(
				strRootDirectory,
				strProjectName,
				strRecipeName);
			return CFileHelper::SetFile(strFilePath, lpszBuffer, ullLength);
		}

		// 读取项目
		static bool ReadConfig(
			const std::string& strRootDirectory,
			ProjectData* pProjectData,
			char* lpszBuffer,
			uint64 ullBufferSize) {
			// 读取项目参数
			memset(lpszBuffer, 0x00, ullBufferSize);
			uint64 ullFileSize = CProjectHelper::ReadProjectCfgFile(
				strRootDirectory,
				pProjectData->strProjectName,
				lpszBuffer,
				ullBufferSize);
			if (0 == ullFileSize) {
				return false;
			}
			pProjectData->strProjectContent = lpszBuffer;
			// 读取所有配方参数
			std::vector<std::string> listRecipeNames;
			if (!CProjectHelper::EnumerateProjectRecipeNames(
				strRootDirectory,
				pProjectData->strProjectName,
				listRecipeNames)) {
				return false;
			}
			for (auto& strRecipeName : listRecipeNames) {
				memset(lpszBuffer, 0x00, ullBufferSize);
				ullFileSize = CProjectHelper::ReadProjectRecipeCfgFile(
					strRootDirectory,
					pProjectData->strProjectName,
					strRecipeName,
					lpszBuffer,
					ullBufferSize);
				if (0 == ullFileSize) {
					return false;
				}
				pProjectData->mapRecipeName2Content[strRecipeName] = lpszBuffer;
			}
			return (!pProjectData->strProjectName.empty() && !pProjectData->strProjectContent.empty());
		}

		// 保存项目
		static bool WriteConfig(
			const std::string& strRootDirectory,
			const ProjectData* pProjectData) {
			// 创建项目文件夹
			if (!CProjectHelper::CreateProjectDirectory(strRootDirectory, pProjectData->strProjectName)) {
				return false;
			}
			// 保存项目参数
			uint64 ullFileSize = yd::CProjectHelper::WriteProjectCfgFile(
				strRootDirectory,
				pProjectData->strProjectName,
				pProjectData->strProjectContent.c_str(),
				pProjectData->strProjectContent.length());
			if (ullFileSize != pProjectData->strProjectContent.length()) {
				return false;
			}
			// 保存所有配方参数
			for (auto iter = pProjectData->mapRecipeName2Content.begin();
				iter != pProjectData->mapRecipeName2Content.end();
				++iter) {
				if (!CProjectHelper::CreateProjectRecipeDirectory(
					strRootDirectory,
					pProjectData->strProjectName,
					iter->first)) {
					return false;
				}
				ullFileSize = yd::CProjectHelper::WriteProjectRecipeCfgFile(
					strRootDirectory,
					pProjectData->strProjectName,
					iter->first,
					iter->second.c_str(),
					iter->second.length());
				if (ullFileSize != iter->second.length()) {
					return false;
				}
			}
			return true;
		}

		// 获取配置文件夹
		static std::string GetConfigDirectory() {
			return CFileHelper::NormalizeDirectory(CFileHelper::GetMainWorkingDirectory() + std::string(CONFIG_PATH_NAME));
		}

		// 获取下载文件夹
		static std::string GetDownloadDirectory() {
			return CFileHelper::NormalizeDirectory(CFileHelper::GetMainWorkingDirectory() + std::string(DOWNLOAD_PATH_NAME));
		}

		// 获取上传文件夹
		static std::string GetUploadDirectory() {
			return CFileHelper::NormalizeDirectory(CFileHelper::GetMainWorkingDirectory() + std::string(UPLOAD_PATH_NAME));
		}

		// 获取组件文件夹
		static std::string GetComponentDirectory() {
			return CFileHelper::NormalizeDirectory(CFileHelper::GetMainWorkingDirectory() + std::string(COMPONENT_PATH_NAME));
		}

		// 获取依赖库文件夹
		static std::string GetDependenceDirectory() {
			return CFileHelper::NormalizeDirectory(CFileHelper::GetMainWorkingDirectory() + std::string(DEPENDENCE_PATH_NAME));
		}

		// 获取日志文件夹
		static std::string GetLogDirectory() {
			return CFileHelper::NormalizeDirectory(CFileHelper::GetMainWorkingDirectory() + std::string(LOG_PATH_NAME));
		}

		// 获取插件文件夹
		static std::string GetPluginDirectory() {
			return CFileHelper::NormalizeDirectory(CFileHelper::GetMainWorkingDirectory() + std::string(PLUGIN_PATH_NAME));
		}

		// 获取脚本文件夹
		static std::string GetScriptDirectory() {
			return CFileHelper::NormalizeDirectory(CFileHelper::GetMainWorkingDirectory() + std::string(SCRIPT_PATH_NAME));
		}

		// 获取临时文件夹
		static std::string GetTempDirectory() {
			return CFileHelper::NormalizeDirectory(CFileHelper::GetMainWorkingDirectory() + std::string(TEMP_PATH_NAME));
		}
	};
}
