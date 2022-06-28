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
  static std::shared_ptr<spdlog::logger> getFileLogger();

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
  std::shared_ptr<spdlog::logger> m_fileLog;
  YDShowMessage* m_msg;
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

#define FTRACE(...)                                                         \
  SPDLOG_LOGGER_CALL(YDLogger::getFileLogger().get(), spdlog::level::trace, \
                     __VA_ARGS__)
#define FDEBUG(...)                                                         \
  SPDLOG_LOGGER_CALL(YDLogger::getFileLogger().get(), spdlog::level::debug, \
                     __VA_ARGS__)
#define FINFO(...)                                                         \
  SPDLOG_LOGGER_CALL(YDLogger::getFileLogger().get(), spdlog::level::info, \
                     __VA_ARGS__)
#define FWARN(...)                                                         \
  SPDLOG_LOGGER_CALL(YDLogger::getFileLogger().get(), spdlog::level::warn, \
                     __VA_ARGS__)
#define FERROR(...)                                                       \
  SPDLOG_LOGGER_CALL(YDLogger::getFileLogger().get(), spdlog::level::err, \
                     __VA_ARGS__)

#endif  // YDLOGGER_H
