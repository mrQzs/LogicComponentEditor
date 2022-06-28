#pragma once

#include "yddef.h"
#include "mod.h"
#include "mod_macro.h"
#include "SystemHelper.h"
#include "StringHelper.h"

namespace yd {
	// 消息辅助类
	class CMessageHelper
	{
	public:
		CMessageHelper() = delete;
		CMessageHelper(IEvent* pEventHandler, uint64 ullHandleData, IAutoData* pEventData) : 
			m_pEventHandler(pEventHandler), m_ullHandleData(ullHandleData), m_pEventData(pEventData) {
		}

	public:
		// 发送消息
		void PushMessage(uint8 ucLevel, const std::string& strModule, const std::string& strMessage) {
			if (nullptr != m_pEventHandler) {
				m_pEventHandler->OnMessage(m_ullHandleData, ucLevel, strModule.c_str(), strMessage.c_str());
			}
		}

		// 发送状态
		void PushStatus(uint8 ucStatusType, uint64 ullStatusId, uint64 ullStatusData) {
			if (nullptr != m_pEventHandler) {
				m_pEventHandler->OnStatus(m_ullHandleData, ucStatusType, ullStatusId, ullStatusData);
			}
		}

		// 发送结果
		void PushResult(uint64 ullUserData, IAutoData* pData) {
			if (nullptr != m_pEventHandler) {
				m_pEventHandler->OnResult(m_ullHandleData, ullUserData, pData);
			}
		}

		// 获取
		IEvent* GetEventHandler() {
			return m_pEventHandler;
		}
		uint64 GetHandleData() {
			return m_ullHandleData;
		}
		IAutoData* GetEventData() {
			return m_pEventData;
		}

	private:
		IEvent*		m_pEventHandler;
		uint64		m_ullHandleData;
		IAutoData*	m_pEventData;
	};
}