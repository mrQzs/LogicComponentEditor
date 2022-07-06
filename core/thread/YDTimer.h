#ifndef YDTIMER_H
#define YDTIMER_H

#include <QTimer>

#include "YDThread.h"

class YDTimer : public YDThread {
  Q_OBJECT
 public:
  explicit YDTimer(QObject *parent = nullptr);
  ~YDTimer();

 public:
  void setTime(int msec);
  virtual void startrun();
  virtual void stop();

 signals:
  void timeout();

 private:
  int m_msec;
  QTimer *m_timer;
};

#endif  // YDTIMER_H
