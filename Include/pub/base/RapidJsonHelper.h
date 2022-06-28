#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <platform.h>
#include "pubfuncs.h"
#include "StringHelper.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"

// RapidJson协助类
namespace yd {
	class CRapidJsonHelper
	{
	public:
		// 获取成员值：字符串
		static void GetMemberValue(rapidjson::Value& jValue, std::string& strValue) {
			strValue.clear();
			if (jValue.IsString()) {
				strValue = jValue.GetString();
			}
			else if (jValue.IsBool()) {
				strValue = yd::CStringHelper::Format("%d", jValue.GetBool() ? "1" : "0");
			}
			else if (jValue.IsInt()) {
				strValue = yd::CStringHelper::Format("%d", jValue.GetInt());
			}
			else if (jValue.IsUint()) {
				strValue = yd::CStringHelper::Format("%u", jValue.GetUint());
			}
			else if (jValue.IsInt64()) {
				strValue = yd::CStringHelper::Format("%lld", jValue.GetInt64());
			}
			else if (jValue.IsUint64()) {
				strValue = yd::CStringHelper::Format("%llu", jValue.GetUint64());
			}
			else if (jValue.IsFloat()) {
				strValue = yd::CStringHelper::Format("%f", jValue.GetFloat());
			}
			else if (jValue.IsDouble()) {
				strValue = yd::CStringHelper::Format("%lf", jValue.GetDouble());
			}
		}

		// 获取成员值：布尔型
		static void GetMemberValue(rapidjson::Value& jValue, bool& bValue) {
			bValue = false;
			if (jValue.IsBool()) {
				bValue = jValue.GetBool();
			}
			else {
				std::string strValue = "";
				CRapidJsonHelper::GetMemberValue(jValue, strValue);
				bValue = (
					0 == strValue.compare("true") ||
					0 == strValue.compare("True") ||
					0 == strValue.compare("TRUE") ||
					0 == strValue.compare("T") ||
					yd::CStringHelper::String2Numeric(strValue.c_str(), (uint64)0) > 0
					);
			}
		}

		// 获取成员值：8位无符号整型
		static void GetMemberValue(rapidjson::Value& jValue, uint8& ucValue) {
			uint32 uiValue = 0;
			CRapidJsonHelper::GetMemberValue(jValue, uiValue);
			ucValue = LOBYTE(LOWORD(uiValue));
		}

		// 获取成员值：8位有符号整型
		static void GetMemberValue(rapidjson::Value& jValue, int8& cValue) {
			uint32 uiValue = 0;
			CRapidJsonHelper::GetMemberValue(jValue, uiValue);
			cValue = static_cast<int8>(LOBYTE(LOWORD(uiValue)));
		}

		// 获取成员值：16位无符号整型
		static void GetMemberValue(rapidjson::Value& jValue, uint16& usValue) {
			uint32 uiValue = 0;
			CRapidJsonHelper::GetMemberValue(jValue, uiValue);
			usValue = LOWORD(uiValue);
		}

		// 获取成员值：16位有符号整型
		static void GetMemberValue(rapidjson::Value& jValue, int16& sValue) {
			uint32 uiValue = 0;
			CRapidJsonHelper::GetMemberValue(jValue, uiValue);
			sValue = static_cast<int16>(LOWORD(uiValue));
		}

		// 获取成员值：32位无符号整型
		static void GetMemberValue(rapidjson::Value& jValue, uint32& uiValue) {
			uiValue = 0;
			if (jValue.IsInt()) {
				uiValue = static_cast<uint32>(jValue.GetInt());
			}
			else if (jValue.IsUint()) {
				uiValue = jValue.GetUint();
			}
			else if (jValue.IsInt64()) {
				uiValue = static_cast<uint32>(jValue.GetInt64());
			}
			else if (jValue.IsUint64()) {
				uiValue = static_cast<uint32>(jValue.GetUint64());
			}
			else if (jValue.IsFloat()) {
				uiValue = static_cast<uint32>(jValue.GetFloat());
			}
			else if (jValue.IsDouble()) {
				uiValue = static_cast<uint32>(jValue.GetDouble());
			}
			else {
				std::string strValue = "";
				CRapidJsonHelper::GetMemberValue(jValue, strValue);
				uiValue = yd::CStringHelper::String2Numeric(strValue.c_str(), (uint32)0);
			}
		}

		// 获取成员值：32位有符号整型
		static void GetMemberValue(rapidjson::Value& jValue, int32& iValue) {
			iValue = 0;
			if (jValue.IsInt()) {
				iValue = jValue.GetInt();
			}
			else if (jValue.IsUint()) {
				iValue = static_cast<int32>(jValue.GetUint());
			}
			else if (jValue.IsInt64()) {
				iValue = static_cast<int32>(jValue.GetInt64());
			}
			else if (jValue.IsUint64()) {
				iValue = static_cast<int32>(jValue.GetUint64());
			}
			else if (jValue.IsFloat()) {
				iValue = static_cast<int32>(jValue.GetFloat());
			}
			else if (jValue.IsDouble()) {
				iValue = static_cast<int32>(jValue.GetDouble());
			}
			else {
				std::string strValue = "";
				CRapidJsonHelper::GetMemberValue(jValue, strValue);
				iValue = yd::CStringHelper::String2Numeric(strValue.c_str(), (int32)0);
			}
		}

		// 获取成员值：64位无符号整型
		static void GetMemberValue(rapidjson::Value& jValue, uint64& ullValue) {
			ullValue = 0;
			if (jValue.IsInt()) {
				ullValue = jValue.GetInt();
			}
			else if (jValue.IsUint()) {
				ullValue = jValue.GetUint();
			}
			else if (jValue.IsInt64()) {
				ullValue = static_cast<uint64>(jValue.GetInt64());
			}
			else if (jValue.IsUint64()) {
				ullValue = jValue.GetUint64();
			}
			else if (jValue.IsFloat()) {
				ullValue = static_cast<uint64>(jValue.GetFloat());
			}
			else if (jValue.IsDouble()) {
				ullValue = static_cast<uint64>(jValue.GetDouble());
			}
			else {
				std::string strValue = "";
				CRapidJsonHelper::GetMemberValue(jValue, strValue);
				ullValue = yd::CStringHelper::String2Numeric(strValue.c_str(), (uint64)0);
			}
		}

		// 获取成员值：64位有符号整型
		static void GetMemberValue(rapidjson::Value& jValue, int64& llValue) {
			llValue = 0;
			if (jValue.IsInt()) {
				llValue = jValue.GetInt();
			}
			else if (jValue.IsUint()) {
				llValue = jValue.GetUint();
			}
			else if (jValue.IsInt64()) {
				llValue = jValue.GetInt64();
			}
			else if (jValue.IsUint64()) {
				llValue = static_cast<int64>(jValue.GetUint64());
			}
			else if (jValue.IsFloat()) {
				llValue = static_cast<int64>(jValue.GetFloat());
			}
			else if (jValue.IsDouble()) {
				llValue = static_cast<int64>(jValue.GetDouble());
			}
			else {
				std::string strValue = "";
				CRapidJsonHelper::GetMemberValue(jValue, strValue);
				llValue = yd::CStringHelper::String2Numeric(strValue.c_str(), (int64)0);
			}
		}

		// 获取成员值：单精度浮点型
		static void GetMemberValue(rapidjson::Value& jValue, float& fValue) {
			fValue = 0;
			if (jValue.IsInt()) {
				fValue = static_cast<float>(jValue.GetInt());
			}
			else if (jValue.IsUint()) {
				fValue = static_cast<float>(jValue.GetUint());
			}
			else if (jValue.IsInt64()) {
				fValue = static_cast<float>(jValue.GetInt64());
			}
			else if (jValue.IsUint64()) {
				fValue = static_cast<float>(jValue.GetUint64());
			}
			else if (jValue.IsFloat()) {
				fValue = jValue.GetFloat();
			}
			else if (jValue.IsDouble()) {
				fValue = static_cast<float>(jValue.GetDouble());
			}
			else {
				std::string strValue = "";
				CRapidJsonHelper::GetMemberValue(jValue, strValue);
				fValue = yd::CStringHelper::String2Numeric(strValue.c_str(), (float)0);
			}
		}

		// 获取成员值：双精度浮点型
		static void GetMemberValue(rapidjson::Value& jValue, double& dblValue) {
			dblValue = 0;
			if (jValue.IsInt()) {
				dblValue = jValue.GetInt();
			}
			else if (jValue.IsUint()) {
				dblValue = jValue.GetUint();
			}
			else if (jValue.IsInt64()) {
				dblValue = static_cast<double>(jValue.GetInt64());
			}
			else if (jValue.IsUint64()) {
				dblValue = static_cast<double>(jValue.GetUint64());
			}
			else if (jValue.IsFloat()) {
				dblValue = jValue.GetFloat();
			}
			else if (jValue.IsDouble()) {
				dblValue = jValue.GetDouble();
			}
			else {
				std::string strValue = "";
				CRapidJsonHelper::GetMemberValue(jValue, strValue);
				dblValue = yd::CStringHelper::String2Numeric(strValue.c_str(), (double)0);
			}
		}

		// 轴坐标数据与Json字符串互转
		static const char* AxisCoords2Json(const yd::COORDS* pCoords, std::string& strJson) {
			rapidjson::StringBuffer strBuf;
			rapidjson::Writer<rapidjson::StringBuffer> jWriter(strBuf);
			// Root Begin
			jWriter.StartObject();
			jWriter.Key("ctrl_type"); jWriter.Uint(pCoords->ucCtrlType);
			jWriter.Key("number"); jWriter.Uint(pCoords->ucNumber);
			// "coords: [] Begin
			jWriter.Key("coords");
			jWriter.StartArray();
			for (uint8 i = 0; i < pCoords->ucNumber; ++i) {
				jWriter.StartObject();
				jWriter.Key("device_id"); jWriter.Uint(pCoords->arrCoords[i].uiDeviceId);
				jWriter.Key("card"); jWriter.Uint(pCoords->arrCoords[i].usCard);
				jWriter.Key("axis"); jWriter.Uint(pCoords->arrCoords[i].usAxis);
				jWriter.Key("type"); jWriter.Uint(pCoords->arrCoords[i].ucType);
				// "target": {} Begin
				jWriter.Key("target"); jWriter.StartObject();
				jWriter.Key("use_variable"); jWriter.Bool(pCoords->arrCoords[i].refTarget.bUseVariable);
				jWriter.Key("refer_value"); jWriter.String(pCoords->arrCoords[i].refTarget.szValue);
				jWriter.EndObject();
				// "target": {} End
				// "velocity": {} Begin
				jWriter.Key("velocity"); jWriter.StartObject();
				jWriter.Key("use_variable"); jWriter.Bool(pCoords->arrCoords[i].refVelocity.bUseVariable);
				jWriter.Key("refer_value"); jWriter.String(pCoords->arrCoords[i].refVelocity.szValue);
				jWriter.EndObject();
				// "velocity": {} End
				jWriter.EndObject();
			}
			jWriter.EndArray();
			// "coords: [] End
			jWriter.EndObject();
			// Root End
			strJson = strBuf.GetString();
			return strJson.c_str();
		}
		static yd::COORDS* Json2AxisCoords(const std::string& strJson, yd::COORDS* pCoords) {
			memset(pCoords, 0x00, sizeof(yd::COORDS));
			rapidjson::Document jDoc;
			jDoc.Parse(strJson.c_str());
			if (jDoc.HasParseError()) {
				return nullptr;
			}
			// "ctrl_type": 1
			if (jDoc.HasMember("ctrl_type")) {
				CRapidJsonHelper::GetMemberValue(jDoc["ctrl_type"], pCoords->ucCtrlType);
			}
			// "coords: []
			if (jDoc.HasMember("coords") && jDoc["coords"].IsArray()) {
				for (auto& jCoord : jDoc["coords"].GetArray()) {
					if (pCoords->ucNumber >= MAX_AXIS_COORD_NUMBER) {
						break;
					}
					if (jCoord.HasMember("device_id")) {
						CRapidJsonHelper::GetMemberValue(jCoord["device_id"], pCoords->arrCoords[pCoords->ucNumber].uiDeviceId);
					}
					if (jCoord.HasMember("card")) {
						CRapidJsonHelper::GetMemberValue(jCoord["card"], pCoords->arrCoords[pCoords->ucNumber].usCard);
					}
					if (jCoord.HasMember("axis")) {
						CRapidJsonHelper::GetMemberValue(jCoord["axis"], pCoords->arrCoords[pCoords->ucNumber].usAxis);
					}
					if (jCoord.HasMember("type")) {
						CRapidJsonHelper::GetMemberValue(jCoord["type"], pCoords->arrCoords[pCoords->ucNumber].ucType);
					}
					if (jCoord.HasMember("target") && jCoord["target"].IsObject()) {
						if (jCoord["target"].HasMember("use_variable")) {
							CRapidJsonHelper::GetMemberValue(
								jCoord["target"]["use_variable"],
								pCoords->arrCoords[pCoords->ucNumber].refTarget.bUseVariable);
						}
						if (jCoord["target"].HasMember("refer_value")) {
							std::string strValue = "";
							CRapidJsonHelper::GetMemberValue(
								jCoord["target"]["refer_value"],
								strValue);
							yd::CStringHelper::SafeCopy(
								pCoords->arrCoords[pCoords->ucNumber].refTarget.szValue,
								sizeof(pCoords->arrCoords[pCoords->ucNumber].refTarget.szValue),
								strValue.c_str());
						}
					}
					if (jCoord.HasMember("velocity") && jCoord["velocity"].IsObject()) {
						if (jCoord["velocity"].HasMember("use_variable")) {
							CRapidJsonHelper::GetMemberValue(
								jCoord["velocity"]["use_variable"],
								pCoords->arrCoords[pCoords->ucNumber].refVelocity.bUseVariable);
						}
						if (jCoord["velocity"].HasMember("refer_value")) {
							std::string strValue = "";
							CRapidJsonHelper::GetMemberValue(
								jCoord["velocity"]["refer_value"],
								strValue);
							yd::CStringHelper::SafeCopy(
								pCoords->arrCoords[pCoords->ucNumber].refVelocity.szValue,
								sizeof(pCoords->arrCoords[pCoords->ucNumber].refVelocity.szValue),
								strValue.c_str());
						}
					}
					++pCoords->ucNumber;
				}
			}
			return pCoords;
		}
	};
}