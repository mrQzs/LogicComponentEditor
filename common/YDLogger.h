#ifndef YDLOGGER_H
#define YDLOGGER_H

#include <QCoreApplication>
#include <mutex>

#include "YDGlobal.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

class YDShowMessage;
class QWidget;

class YDLogger {
  Q_DECLARE_TR_FUNCTIONS(YDLogger)
 public:
  YDLogger();
  ~YDLogger();

 public:
  static std::shared_ptr<spdlog::logger> getConsoleLogger();

 public:
  static void setMessageWidget(YDShowMessage* w);
  static void log(const QString& str, LogLevel level);
  static void trace(const QString& str);
  static void info(const QString& str);
  static void debug(const QString& str);
  static void warn(const QString& str);
  static void err(const QString& str);
  static void critical(const QString& str);

 private:
  static YDLogger* s_instance;
  std::mutex m_mutex;
  std::shared_ptr<spdlog::logger> m_consoleLog;
  YDShowMessage* m_msg;
  QString m_traceStr;
  QString m_debugStr;
  QString m_infoStr;
  QString m_warnStr;
  QString m_errorStr;
  QString m_fatalStr;
};

#define TRACE(...)                                                             \
  SPDLOG_LOGGER_CALL(YDLogger::getConsoleLogger().get(), spdlog::level::trace, \
                     __VA_ARGS__)
#define DEBUG(...)                                                             \
  SPDLOG_LOGGER_CALL(YDLogger::getConsoleLogger().get(), spdlog::level::debug, \
                     __VA_ARGS__)
#define INFO(...)                                                             \
  SPDLOG_LOGGER_CALL(YDLogger::getConsoleLogger().get(), spdlog::level::info, \
                     __VA_ARGS__)
#define WARN(...)                                                             \
  SPDLOG_LOGGER_CALL(YDLogger::getConsoleLogger().get(), spdlog::level::warn, \
                     __VA_ARGS__)
#define ERROR(...)                                                           \
  SPDLOG_LOGGER_CALL(YDLogger::getConsoleLogger().get(), spdlog::level::err, \
                     __VA_ARGS__)

#endif  // YDLOGGER_H
