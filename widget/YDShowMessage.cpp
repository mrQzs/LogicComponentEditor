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
  m_logText->setWordWrapMode(QTextOption::WordWrap);
  m_logText->setStyleSheet("font-size:16px;");
  m_logText->moveCursor(QTextCursor::End);

  //  setShowMessage(
  //      "sd打撒所多撒 D洗你你你里哦几句哦几哦姐 "
  //      "及激励降维打击加大到位我激动我按到位我案件都加到我的骄傲",
  //      Trace);
  //  setShowMessage("sd打撒所多撒 D洗你你你里哦几句哦几哦姐 及激励降维打击",
  //                 Debug);
  //  setShowMessage(
  //      "sd打撒所多撒 D洗你你你里哦几句哦几哦姐 "
  //      "及激励降维打击加大到位我激动我按到位我案件都加到我的骄傲",
  //      Info);
  //  setShowMessage("sd打撒所多撒 D洗你你你里哦几句哦几哦姐 及激励降维打击",
  //                 Warning);
  //  setShowMessage("sd打撒所多撒 D洗你你你里哦几句哦几哦姐及激励降维打击 ",
  //                 Error);

  //  setShowMessage(
  //      "sd打撒所多撒 D洗你你你里哦几句哦几哦姐 "
  //      "及激励降维打击加大到位我激动我按到位我案件都加到我的骄傲",
  //      Fatal);
}

void YDShowMessage::setShowMessage(const QString &info, const LogLevel &level) {
  QString fontColor = "#000000";
  switch (level) {
    case Trace:
      fontColor = "#4C4C4C";
      break;
    case Debug:
      fontColor = "#0053AE";
      break;
    case Info:
      fontColor = "#006000";
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
