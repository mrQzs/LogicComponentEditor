#ifndef YDTHREAD_H
#define YDTHREAD_H

#include <QObject>

class YDThread : public QObject {
  Q_OBJECT
 public:
  explicit YDThread(QObject *parent = nullptr);
  virtual ~YDThread();

 public:
  virtual void startrun() = 0;
  virtual void stop() = 0;

 public:
  volatile bool m_stopped;
};

#endif  // YDTHREAD_H
