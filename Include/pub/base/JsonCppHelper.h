#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <platform.h>
#include "pubfuncs.h"
#include "json\json.h"

namespace yd {
	// json 辅助类
	class CJsonCppHelper
	{
	public:
		// 获取属性值(const char*)
		static const char* GetAttributeValue(Json::Value& jObject, const char* lpszName, const char* lpszDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return nullptr == lpszDefault ? "" : lpszDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return nullptr == lpszDefault ? "" : lpszDefault;
			}
			const char* lpszValue = jObject[lpszName].asString().c_str();
			if (nullptr == lpszValue) {
				return nullptr == lpszDefault ? "" : lpszDefault;
			}
			else {
				return lpszValue;
			}
		}
		// 获取属性值(bool)
		static bool GetAttributeValue(Json::Value& jObject, const char* lpszName, bool bDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return bDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return bDefault;
			}
			else {
				return jObject[lpszName].asBool();
			}
		}
		// 获取属性值(uint8)
		static uint8 GetAttributeValue(Json::Value& jObject, const char* lpszName, uint8 ucDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return ucDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return ucDefault;
			}
			else {
				return (uint8)jObject[lpszName].asUInt();
			}
		}
		// 获取属性值(int8)
		static int8 GetAttributeValue(Json::Value& jObject, const char* lpszName, int8 cDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return cDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return cDefault;
			}
			else {
				return (int8)jObject[lpszName].asInt();
			}
		}
		// 获取属性值(uint16)
		static uint16 GetAttributeValue(Json::Value& jObject, const char* lpszName, uint16 usDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return usDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return usDefault;
			}
			else {
				return (uint16)jObject[lpszName].asUInt();
			}
		}
		// 获取属性值(int16)
		static int16 GetAttributeValue(Json::Value& jObject, const char* lpszName, int16 sDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return sDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return sDefault;
			}
			else {
				return (int16)jObject[lpszName].asInt();
			}
		}
		// 获取属性值(uint32)
		static uint32 GetAttributeValue(Json::Value& jObject, const char* lpszName, uint32 uiDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return uiDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return uiDefault;
			}
			else {
				return (uint32)jObject[lpszName].asUInt();
			}
		}
		// 获取属性值(int32)
		static int32 GetAttributeValue(Json::Value& jObject, const char* lpszName, int32 iDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return iDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return iDefault;
			}
			else {
				return (int32)jObject[lpszName].asInt();
			}
		}
		// 获取属性值(uint64)
		static uint64 GetAttributeValue(Json::Value& jObject, const char* lpszName, uint64 ullDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return ullDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return ullDefault;
			}
			else {
				return (uint64)jObject[lpszName].asUInt64();
			}
		}
		// 获取属性值(int64)
		static int64 GetAttributeValue(Json::Value& jObject, const char* lpszName, int64 llDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return llDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return llDefault;
			}
			else {
				return (int64)jObject[lpszName].asInt64();
			}
		}
		// 获取属性值(float)
		static float GetAttributeValue(Json::Value& jObject, const char* lpszName, float fDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return fDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return fDefault;
			}
			else {
				return jObject[lpszName].asFloat();
			}
		}
		// 获取属性值(double)
		static double GetAttributeValue(Json::Value& jObject, const char* lpszName, double dblDefault) {
			if (nullptr == lpszName || strlen(lpszName) <= 0) {
				return dblDefault;
			}
			if (!jObject.isMember(lpszName)) {
				return dblDefault;
			}
			else {
				return jObject[lpszName].asDouble();
			}
		}
	};
}
