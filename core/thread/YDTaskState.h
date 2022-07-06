#ifndef YDTASKSTATE_H
#define YDTASKSTATE_H

#include <QTimer>

#include "YDThread.h"

class YDTaskState : public YDThread {
  Q_OBJECT
 public:
  explicit YDTaskState(QObject *parent = nullptr);
  ~YDTaskState();

  void setTime(int msec, quint32 taskId);
  void startrun() override;
  void stop() override;

 signals:
  void sigTransState(quint8 state);

 private slots:
  void getTaskState();

 private:
  int m_msec;
  quint32 m_taskId;
  QTimer *m_timer;
};

#endif  // YDTASKSTATE_H
