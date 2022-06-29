#ifndef YDDEBUGLOGER_H
#define YDDEBUGLOGER_H

#include <QCoreApplication>
#include <mutex>

#include "YDGlobal.h"

class YDShowMessage;

class YDDebugLoger {
  Q_DECLARE_TR_FUNCTIONS(YDDebugLoger)
 public:
  YDDebugLoger();
  ~YDDebugLoger();

 public:
  static void setMessageWidget(YDShowMessage* w);
  static void info(const QString& info);

 private:
  static YDDebugLoger* s_instance;
  std::mutex m_mutex;
  YDShowMessage* m_msg;
};

#endif  // YDDEBUGLOGER_H
