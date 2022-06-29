#ifndef YDLOGTHREAD_H
#define YDLOGTHREAD_H

#include <QObject>
#include <QThread>

#include "YDGlobal.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

class YDFileLog : public QObject {
  Q_OBJECT
 public:
  explicit YDFileLog(QObject* parent = nullptr);
  ~YDFileLog();

 public:
  static std::shared_ptr<spdlog::logger> getFileLogger();

 private:
  static YDFileLog* s_instance;
  std::shared_ptr<spdlog::logger> m_fileLog;
};

class YDLogThread : public QThread {
  Q_OBJECT
 public:
  explicit YDLogThread(QObject* parent = nullptr);
  ~YDLogThread();

 public:
  static YDLogThread* GetInst() {
    static YDLogThread hw;
    return &hw;
  }

 public slots:
  void log(const QString& str);

 protected:
  void run() override;

 private:
  bool m_isfirstRun;
  YDFileLog* m_filelog;
};

#define FTRACE(...)                                                          \
  SPDLOG_LOGGER_CALL(YDFileLog::getFileLogger().get(), spdlog::level::trace, \
                     __VA_ARGS__)
#define FDEBUG(...)                                                          \
  SPDLOG_LOGGER_CALL(YDFileLog::getFileLogger().get(), spdlog::level::debug, \
                     __VA_ARGS__)
#define FINFO(...)                                                          \
  SPDLOG_LOGGER_CALL(YDFileLog::getFileLogger().get(), spdlog::level::info, \
                     __VA_ARGS__)
#define FWARN(...)                                                          \
  SPDLOG_LOGGER_CALL(YDFileLog::getFileLogger().get(), spdlog::level::warn, \
                     __VA_ARGS__)
#define FERROR(...)                                                        \
  SPDLOG_LOGGER_CALL(YDFileLog::getFileLogger().get(), spdlog::level::err, \
                     __VA_ARGS__)

#endif  // YDLOGTHREAD_H
