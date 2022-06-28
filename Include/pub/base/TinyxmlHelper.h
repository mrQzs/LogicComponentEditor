#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <platform.h>
#include "pubfuncs.h"
#include "tinyxml2\tinyxml2.h"

namespace yd {
	// Tinyxml 协助类
	class CTinyxmlHelper
	{
	public:
		// 获取属性值(const char*)
		static const char* GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const char* lpszDefault) {
			if (nullptr == pXmlElement) {
				return nullptr == lpszDefault ? "" : lpszDefault;
			}
			const char* lpszValue = pXmlElement->Attribute(lpszName, lpszDefault);
			if (nullptr == lpszValue) {
				return nullptr == lpszDefault ? "" : lpszDefault;
			}
			else {
				return lpszValue;
			}
		}
		// 获取属性值(bool)
		static bool GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const bool& bDefault) {
			if (nullptr == pXmlElement) {
				return bDefault;
			}
			else {
				return pXmlElement->BoolAttribute(lpszName, bDefault);
			}
		}
		// 获取属性值(uint8)
		static uint8 GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const uint8& ucDefault) {
			return (uint8)CTinyxmlHelper::GetAttributeValue(pXmlElement, lpszName, (uint32)ucDefault);
		}
		// 获取属性值(int8)
		static int8 GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const int8& cDefault) {
			return (int8)CTinyxmlHelper::GetAttributeValue(pXmlElement, lpszName, (int32)cDefault);
		}
		// 获取属性值(uint16)
		static uint16 GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const uint16& usDefault) {
			return (uint16)CTinyxmlHelper::GetAttributeValue(pXmlElement, lpszName, (uint32)usDefault);
		}
		// 获取属性值(int16)
		static int16 GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const int16& sDefault) {
			return (int16)CTinyxmlHelper::GetAttributeValue(pXmlElement, lpszName, (int32)sDefault);
		}
		// 获取属性值(uint32)
		static uint32 GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const uint32& uiDefault) {
			if (nullptr == pXmlElement) {
				return uiDefault;
			}
			else {
				return (uint32)pXmlElement->UnsignedAttribute(lpszName, uiDefault);
			}
		}
		// 获取属性值(int32)
		static int32 GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const int32& iDefault) {
			if (nullptr == pXmlElement) {
				return iDefault;
			}
			else {
				return (int32)pXmlElement->IntAttribute(lpszName, iDefault);
			}
		}
		// 获取属性值(uint64)
		static uint64 GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const uint64& ullDefault) {
			if (nullptr == pXmlElement) {
				return ullDefault;
			}
			else {
				return (uint64)pXmlElement->Int64Attribute(lpszName, (int64_t)ullDefault);
			}
		}
		// 获取属性值(int64)
		static int64 GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const int64& llDefault) {
			if (nullptr == pXmlElement) {
				return llDefault;
			}
			else {
				return (int64)pXmlElement->Int64Attribute(lpszName, llDefault);
			}
		}
		// 获取属性值(float)
		static float GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const float& fDefault) {
			if (nullptr == pXmlElement) {
				return fDefault;
			}
			else {
				return pXmlElement->FloatAttribute(lpszName, fDefault);
			}
		}
		// 获取属性值(double)
		static double GetAttributeValue(tinyxml2::XMLElement* pXmlElement, const char* lpszName, const double& dblDefault) {
			if (nullptr == pXmlElement) {
				return dblDefault;
			}
			else {
				return pXmlElement->DoubleAttribute(lpszName, dblDefault);
			}
		}
	};
}
