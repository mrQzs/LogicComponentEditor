#include "YDTimer.h"

YDTimer::YDTimer(QObject *parent)
    : QObject(parent), m_timer(nullptr), m_msec{500} {}

YDTimer::~YDTimer() { stop(); }

void YDTimer::setTime(int msec) {
  m_msec = msec;
  m_timer->stop();
  m_timer->start(m_msec);
}

void YDTimer::startrun() {
  if (!m_timer) {
    m_timer = new QTimer;
    connect(m_timer, &QTimer::timeout, this, &YDTimer::timeout);
  }

  m_timer->start(m_msec);
}

void YDTimer::stop() {
  if (m_timer) {
    m_timer->stop();
    delete m_timer;
    m_timer = nullptr;
  }
}
