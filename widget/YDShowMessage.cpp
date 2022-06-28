#include "YDShowMessage.h"

#include <QTextEdit>
#include <QVBoxLayout>

YDShowMessage::YDShowMessage(QWidget *parent)
    : QDialog{parent}, m_logText{new QTextEdit(this)} {
  setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(m_logText);

  m_logText->setReadOnly(true);
  m_logText->moveCursor(QTextCursor::End);
}

void YDShowMessage::setShowMessage(const QString &info, const LogLevel &level) {
  QString fontColor = "#000000";
  switch (level) {
    case Trace:
      fontColor = "#808080";
      break;
    case Debug:
      fontColor = "#000000";
      break;
    case Info:
      fontColor = "#008000";
      break;
    case Warning:
      fontColor = "#808000";
      break;
    case Error:
      fontColor = "#800000";
      break;
    case Fatal:
      fontColor = "#FF0000";
      break;
  }
  m_logText->append(QString("<font color=%1>%2</font>").arg(fontColor, info));
}
