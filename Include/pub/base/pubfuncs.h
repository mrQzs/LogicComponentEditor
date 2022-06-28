#pragma once

#include <stdio.h>
#include <memory.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <cstring>
#include <tchar.h>

#define random(x) (rand()%x)


#define SAFE_ZERO(x) memset(&x,0,sizeof(x));
#define SAFE_ZERO_P(x,len) memset(x,0,len);
#define SAFE_ZERO_A(x) SAFE_ZERO(x,sizeof(x));
#define SAFE_DELETE(x) {if((x) != NULL) {delete (x); (x) = NULL;}}
#define SAFE_DELETE_A(x) {if((x) != NULL) {delete[] (x); (x) = NULL;}}
#define SAFE_RELEASE(p) {if(NULL != (p)) {(p)->Release(); (p) = NULL;} }
#ifdef _WINDOWS
#define SAFE_STRCOPY(dest, src) strncpy_s((dest), (src), sizeof(dest)-1)
#else
#define SAFE_STRCOPY(dest, src) strcpy_s((dest), (src))
#endif // _WIN32

#define AUTOLOCK(mtx) std::lock_guard<std::mutex> lock(mtx);

namespace pub
{


	
	

#ifdef WIN32

	//utf-8转换到GB3212  
	inline char* U2G(const char* utf8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
		len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr) delete[] wstr;
		return str;
	}
	//GB2312到UTF-8的转换  
	inline char* G2U(const char* gb2312)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr) delete[] wstr;
		return str;
	}

	inline std::string DatetimeToString(time_t time)
	{
		tm tm_;
		localtime_s(&tm_,&time);                // 将time_t格式转换为tm结构体
		int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
		year = tm_.tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
		month = tm_.tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
		day = tm_.tm_mday;                        // 临时变量，日。
		hour = tm_.tm_hour;                       // 临时变量，时。
		minute = tm_.tm_min;                      // 临时变量，分。
		second = tm_.tm_sec;                      // 临时变量，秒。
		char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// 定义时间的各个char*变量。
		sprintf_s(yearStr, "%d", year);              // 年。
		sprintf_s(monthStr, "%d", month);            // 月。
		sprintf_s(dayStr, "%d", day);                // 日。
		sprintf_s(hourStr, "%d", hour);              // 时。
		sprintf_s(minuteStr, "%d", minute);          // 分。
		if (minuteStr[1] == '\0')                  // 如果分为一位，如5，则需要转换字符串为两位，如05。
		{
			minuteStr[2] = '\0';
			minuteStr[1] = minuteStr[0];
			minuteStr[0] = '0';
		}
		sprintf_s(secondStr, "%d", second);          // 秒。
		if (secondStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
		{
			secondStr[2] = '\0';
			secondStr[1] = secondStr[0];
			secondStr[0] = '0';
		}
		char s[20];                                // 定义总日期时间char*变量。
		sprintf_s(s, "%s-%s-%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// 将年月日时分秒合并。
		std::string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
		return str;                                // 返回转换日期时间后的string变量。
	}


	// Convert a wide Unicode string to an UTF8 string
	inline std::string utf8_encode(const std::wstring &wstr)
	{
		if (wstr.empty()) return std::string();
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
		return strTo;
	}

	// Convert an UTF8 string to a wide Unicode String
	inline std::wstring utf8_decode(const std::string &str)
	{
		if (str.empty()) return std::wstring();
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}

	inline std::string wstrtostr(const std::wstring &wstr)
	{
		// Convert a Unicode string to an ASCII string
		std::string strTo;
		char *szTo = new char[wstr.length() + 1];
		szTo[wstr.size()] = '\0';
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);
		strTo = szTo;
		delete[] szTo;
		return strTo;
	}

	inline std::wstring strtowstr(const std::string &str)
	{
		// Convert an ASCII string to a Unicode String
		std::wstring wstrTo;
		wchar_t *wszTo = new wchar_t[str.length() + 1];
		wszTo[str.size()] = L'\0';
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wszTo, (int)str.length());
		wstrTo = wszTo;
		delete[] wszTo;
		return wstrTo;
	}

#ifdef _UNICODE
// 	inline std::wstring ReadFileToString(const char* filename)
// 	{
// 		TCHAR path[MAX_PATH] = { 0 };
// 		TCHAR pathfile[MAX_PATH] = { 0 };
// 		::GetCurrentDirectory(MAX_PATH, path);
// 		swprintf_s(pathfile, L"%s\\%s", path, filename);
// 
// 		FILE* pFile = NULL;
// 		_wfopen_s(&pFile, pathfile, L"rb");
// 		char* pBuf;
// 		fseek(pFile, 0, SEEK_END);//移动文件指针到文件末尾
// 		int len = ftell(pFile);//获取当前文件指针在文件中的偏移量，Gets the current position of a file pointer.offset 
// 		pBuf = new char[len + 1];
// 		rewind(pFile);//将指针移动到文件头，Repositions the file pointer to the beginning of a file
// 					  //也可以用fseek(pFile,0,SEEK_SET);
// 		fread(pBuf, 1, len, pFile);
// 		pBuf[len] = 0;
// 		fclose(pFile);
// 
// 		std::wstring retstr = pBuf;
// 		delete[] pBuf;
// 		return retstr;
// 	}
// 
// 	inline std::wstring GetExecDir()
// 	{
// 		TCHAR _szPath[MAX_PATH + 1] = { 0 };
// 		GetModuleFileName(NULL, _szPath, MAX_PATH);
// 		(_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串
// 
// 		return _szPath;
// 	}
#else
	inline std::string ReadFileToString(const char* filename)
	{
		TCHAR path[MAX_PATH] = { 0 };
		TCHAR pathfile[MAX_PATH] = { 0 };
		::GetCurrentDirectory(MAX_PATH, path);
		sprintf_s(pathfile, "%s\\%s", path, filename);

		FILE* pFile = NULL;
		fopen_s(&pFile, pathfile, "rb");
		char* pBuf;
		fseek(pFile, 0, SEEK_END);//移动文件指针到文件末尾
		int len = ftell(pFile);//获取当前文件指针在文件中的偏移量，Gets the current position of a file pointer.offset 
		pBuf = new char[len + 1];
		rewind(pFile);//将指针移动到文件头，Repositions the file pointer to the beginning of a file
					  //也可以用fseek(pFile,0,SEEK_SET);
		fread(pBuf, 1, len, pFile);
		pBuf[len] = 0;
		fclose(pFile);

		std::string retstr = pBuf;
		delete[] pBuf;
		return retstr;
	}

	inline std::string GetExecDir()
	{
		TCHAR _szPath[MAX_PATH + 1] = { 0 };
		GetModuleFileName(NULL, _szPath, MAX_PATH);
		(_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串

		return _szPath;
	}
#endif
	
	


#else

// int _vscprintf(const char * format, va_list pargs) {
// 	int retval;
// 	va_list argcopy;
// 	va_copy(argcopy, pargs);
// 	retval = vsnprintf(NULL, 0, format, argcopy);
// 	va_end(argcopy);
// 	return retval;
// }

#endif // _WIN32

	

}