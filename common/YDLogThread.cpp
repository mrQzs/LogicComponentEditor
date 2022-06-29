#include "YDLogThread.h"

#include <QDateTime>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>

#include "YDLogger.h"

YDFileLog *YDFileLog::s_instance = nullptr;

YDFileLog::YDFileLog(QObject *parent) : QObject{parent} {
  Q_ASSERT(s_instance == nullptr);
  s_instance = this;

  const std::string log_dir = "./log";
  const std::string logger_name_prefix = "YDLog";
  std::string level = "info";

  try {
    std::string time = QDateTime::currentDateTime()
                           .toString("_yyMMdd_hhmmss")
                           .toUtf8()
                           .constData();

    const std::string logger_name = logger_name_prefix + time;

    m_fileLog = spdlog::create_async<spdlog::sinks::rotating_file_sink_mt>(
        logger_name, log_dir + "/" + logger_name + ".log", 50 * 1024 * 1024,
        10);  // multi part log files, with every part
              // 500M, max 1000 files

    // custom format
    m_fileLog->set_pattern("%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] [%@] %v");

    if (level == "trace") {
      m_fileLog->set_level(spdlog::level::trace);
      m_fileLog->flush_on(spdlog::level::trace);
    } else if (level == "debug") {
      m_fileLog->set_level(spdlog::level::debug);
      m_fileLog->flush_on(spdlog::level::debug);
    } else if (level == "info") {
      m_fileLog->set_level(spdlog::level::info);
      m_fileLog->flush_on(spdlog::level::info);
    } else if (level == "warn") {
      m_fileLog->set_level(spdlog::level::warn);
      m_fileLog->flush_on(spdlog::level::warn);
    } else if (level == "error") {
      m_fileLog->set_level(spdlog::level::err);
      m_fileLog->flush_on(spdlog::level::err);
    }
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }
}

YDFileLog::~YDFileLog() {
  Q_ASSERT(s_instance == this);
  s_instance = nullptr;
}

std::shared_ptr<spdlog::logger> YDFileLog::getFileLogger() {
  Q_ASSERT(s_instance != nullptr);
  return s_instance->m_fileLog;
}

YDLogThread::YDLogThread(QObject *parent)
    : QThread(parent), m_isfirstRun{true}, m_filelog{nullptr} {}

YDLogThread::~YDLogThread() {
  if (m_filelog) delete m_filelog;
}

void YDLogThread::log(const QString &str) {
  m_filelog->getFileLogger()->log(spdlog::level::info,
                                  (const char *)str.toUtf8().constData());
}

void YDLogThread::run() {
  while (true) {
    if (m_isfirstRun) {
      m_isfirstRun = false;
      m_filelog = new YDFileLog;
    }

    if (isInterruptionRequested()) break;
  }
}
