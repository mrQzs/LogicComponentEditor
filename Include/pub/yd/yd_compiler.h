#pragma once

#include <string>
#include <vector>
#include <map>
#include "yddef.h"
#include "mod.h"
#include "mod_macro.h"

namespace yd {
	// 编译器接口
	interface ICompiler : public ICountor
	{
		// 枚举框架
		virtual bool EnumFrameworks(
			uint8 ucTargetCPU,
			std::vector<std::string>& listFrameworks) = 0;

		// 获取可编程控件源文件路径
		virtual std::string GetProgrammableProcessCodeFilePath(
			const std::string& strProcessName,
			uint8 ucCompilerType) = 0;

		// 获取扩展脚本源文件路径
		virtual std::string GetExtendableScriptCodeFilePath(
			const std::string& strScriptName,
			uint8 ucCompilerType) = 0;

		// 获取可编程控件模块名称
		virtual std::string GetProgrammableProcessModuleName(
			const std::string& strProcessName) = 0;

		// 获取扩展脚本模块名称
		virtual std::string GetExtendableScriptModuleName(
			const std::string& strScriptName) = 0;

		// 编译可编程逻辑控件
		virtual bool CompileProgrammableProcess(
			const std::string& strProcessName,
			uint8 ucCompilerType,
			const std::string& strTargetFramework,
			uint8 ucTargetCPU,
			std::string& strCompileInformation) = 0;

		// 编译扩展脚本
		virtual bool CompileExtendableScript(
			const std::string& strScriptName,
			uint8 ucCompilerType,
			const std::string& strTargetFramework,
			uint8 ucTargetCPU,
			std::string& strCompileInformation) = 0;
	};
	typedef ICompiler* (*funcGetICompiler)(uint32, const char*);
}
