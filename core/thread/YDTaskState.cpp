#include "YDTaskState.h"

#include <QDebug>
#include <QThread>

#include "debug/YDDgHelper.h"

YDTaskState::YDTaskState(QObject *parent)
    : YDThread{parent}, m_msec{500}, m_timer(nullptr) {}

YDTaskState::~YDTaskState() {}

void YDTaskState::setTime(int msec, quint32 taskId) {
  m_msec = msec;
  m_taskId = taskId;

  startrun();
}

void YDTaskState::startrun() {
  m_stopped = false;
  if (!m_timer) {
    m_timer = new QTimer;
    connect(m_timer, &QTimer::timeout, this, &YDTaskState::getTaskState);
  } else
    m_timer->stop();

  m_timer->start(m_msec);
}

void YDTaskState::stop() {
  m_stopped = true;
  if (m_timer) {
    m_timer->stop();
    delete m_timer;
    m_timer = nullptr;
  }
}

void YDTaskState::getTaskState() {
  if (!m_stopped) {
    quint8 state = 0;

    YDDgHelper::GetTaskDebugState(m_taskId, state);
    emit sigTransState(state);
  }
}
