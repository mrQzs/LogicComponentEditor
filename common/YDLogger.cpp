#include "YDLogger.h"

#include <QDateTime>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>

#include "widget/YDShowMessage.h"

YDLogger *YDLogger::s_instance = nullptr;

YDLogger::YDLogger()
    : m_msg{nullptr},
      m_traceStr{YDLogger::tr("[追踪]")},
      m_debugStr{YDLogger::tr("[调试]")},
      m_infoStr{YDLogger::tr("[信息]")},
      m_warnStr{YDLogger::tr("[警告]")},
      m_errorStr{YDLogger::tr("[错误]")},
      m_fatalStr{YDLogger::tr("[致命]")} {
  Q_ASSERT(s_instance == nullptr);
  s_instance = this;

  try {
    m_consoleLog = spdlog::stdout_color_st("LoggerName1");
    m_consoleLog->set_pattern("%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] [%@] %v");
    // with timestamp,
    // thread_id,
    // filename and
    // line number
    std::string level = "info";

    if (level == "trace") {
      m_consoleLog->set_level(spdlog::level::trace);
      m_consoleLog->flush_on(spdlog::level::trace);
    } else if (level == "debug") {
      m_consoleLog->set_level(spdlog::level::debug);
      m_consoleLog->flush_on(spdlog::level::debug);
    } else if (level == "info") {
      m_consoleLog->set_level(spdlog::level::info);
      m_consoleLog->flush_on(spdlog::level::info);
    } else if (level == "warn") {
      m_consoleLog->set_level(spdlog::level::warn);
      m_consoleLog->flush_on(spdlog::level::warn);
    } else if (level == "error") {
      m_consoleLog->set_level(spdlog::level::err);
      m_consoleLog->flush_on(spdlog::level::err);
    }
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }
}

YDLogger::~YDLogger() {
  Q_ASSERT(s_instance == this);
  s_instance = nullptr;
  spdlog::drop_all();
}

std::shared_ptr<spdlog::logger> YDLogger::getConsoleLogger() {
  Q_ASSERT(s_instance != nullptr);
  return s_instance->m_consoleLog;
}

void YDLogger::setMessageWidget(YDShowMessage *w) {
  Q_ASSERT(w != nullptr);
  s_instance->m_msg = w;
}

void YDLogger::log(const QString &str, LogLevel level) {
  Q_ASSERT(s_instance != nullptr);
  std::lock_guard<std::mutex> lock(s_instance->m_mutex);
  Q_UNUSED(lock)
  QString time = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]");

  switch (level) {
    case LogLevel::Trace: {
      s_instance->m_msg->setShowMessage(
          QString("%1 %2 %3").arg(time, s_instance->m_traceStr, str), level);
    } break;
    case LogLevel::Debug: {
      s_instance->m_msg->setShowMessage(
          QString("%1 %2 %3").arg(time, s_instance->m_debugStr, str), level);
    } break;
    case LogLevel::Info: {
      s_instance->m_msg->setShowMessage(
          QString("%1 %2 %3").arg(time, s_instance->m_infoStr, str), level);
    } break;
    case LogLevel::Warning: {
      s_instance->m_msg->setShowMessage(
          QString("%1 %2 %3").arg(time, s_instance->m_warnStr, str), level);
    } break;
    case LogLevel::Error: {
      s_instance->m_msg->setShowMessage(
          QString("%1 %2 %3").arg(time, s_instance->m_errorStr, str), level);
    } break;
    case LogLevel::Fatal: {
      s_instance->m_msg->setShowMessage(
          QString("%1 %2 %3").arg(time, s_instance->m_fatalStr, str), level);
    } break;
    default:
      break;
  }
}

void YDLogger::trace(const QString &str) { log(str, LogLevel::Trace); }

void YDLogger::info(const QString &str) { log(str, LogLevel::Info); }

void YDLogger::debug(const QString &str) { log(str, LogLevel::Debug); }

void YDLogger::warn(const QString &str) { log(str, LogLevel::Warning); }

void YDLogger::err(const QString &str) { log(str, LogLevel::Error); }

void YDLogger::critical(const QString &str) { log(str, LogLevel::Fatal); }
