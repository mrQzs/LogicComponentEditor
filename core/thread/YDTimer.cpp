#include "YDTimer.h"

YDTimer::YDTimer(QObject *parent)
    : YDThread(parent), m_msec{500}, m_timer(nullptr) {}

YDTimer::~YDTimer() {}

void YDTimer::setTime(int msec) {
  m_msec = msec;
  if (m_timer) {
    m_timer->stop();
    m_timer->start(m_msec);
  } else
    startrun();
}

void YDTimer::startrun() {
  if (!m_timer) {
    m_timer = new QTimer;
    connect(m_timer, &QTimer::timeout, this, &YDTimer::timeout);
  } else
    m_timer->stop();

  m_timer->start(m_msec);
}

void YDTimer::stop() {
  if (m_timer) {
    m_timer->stop();
    delete m_timer;
    m_timer = nullptr;
  }
}
