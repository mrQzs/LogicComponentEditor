#include "YDDebugLoger.h"

#include <QDateTime>

#include "widget/YDShowMessage.h"

YDDebugLoger* YDDebugLoger::s_instance = nullptr;

YDDebugLoger::YDDebugLoger() {
  Q_ASSERT(s_instance == nullptr);
  s_instance = this;
}

YDDebugLoger::~YDDebugLoger() {
  Q_ASSERT(this == s_instance);
  s_instance = nullptr;
}

void YDDebugLoger::setMessageWidget(YDShowMessage* w) {
  Q_ASSERT(w != nullptr);
  s_instance->m_msg = w;
}

void YDDebugLoger::info(const QString& str) {
  Q_ASSERT(s_instance != nullptr);
  std::lock_guard<std::mutex> lock(s_instance->m_mutex);
  Q_UNUSED(lock)
  QString time = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]");
  QString hix = YDDebugLoger::tr("[调试信息]");

  auto text = QString("%1 %2 %3").arg(time, hix, str);
  s_instance->m_msg->setShowMessage(text, LogLevel::Debug);
}
