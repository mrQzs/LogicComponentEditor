#include "YDThread.h"

YDThread::YDThread(QObject *parent) : QObject(parent), m_stopped{false} {}

YDThread::~YDThread() {}
