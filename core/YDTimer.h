#ifndef YDTIMER_H
#define YDTIMER_H

#include <QObject>
#include <QThread>
#include <QTimer>

class YDTimer : public QObject {
  Q_OBJECT
 public:
  explicit YDTimer(QObject *parent = nullptr);
  ~YDTimer();

 public:
  void setTime(int msec);
  void startrun();
  void stop();

 signals:
  void timeout();

 private:
  int m_msec;
  QTimer *m_timer;
};

#endif  // YDTIMER_H
