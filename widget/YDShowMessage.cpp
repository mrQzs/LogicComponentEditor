#include "YDShowMessage.h"

#include <QTextEdit>
#include <QVBoxLayout>

YDShowMessage::YDShowMessage(QWidget *parent)
    : QDialog{parent},
      m_logText{new QTextEdit(this)},
      m_traceColor{"#4C4C4C"},
      m_debugColor{"#0053AE"},
      m_infoColor{"#006000"},
      m_warnColor{"#808000"},
      m_errorColor{"#800000"},
      m_fatalColor{"#FF0000"} {
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
  switch (level) {
    case Trace:
      m_logText->append(
          QString("<font color=%1>%2</font>").arg(m_traceColor, info));
      break;
    case Debug:
      m_logText->append(
          QString("<font color=%1>%2</font>").arg(m_debugColor, info));
      break;
    case Info:
      m_logText->append(
          QString("<font color=%1>%2</font>").arg(m_infoColor, info));
      break;
    case Warning:
      m_logText->append(
          QString("<font color=%1>%2</font>").arg(m_warnColor, info));
      break;
    case Error:
      m_logText->append(
          QString("<font color=%1>%2</font>").arg(m_errorColor, info));
      break;
    case Fatal:
      m_logText->append(
          QString("<font color=%1>%2</font>").arg(m_fatalColor, info));
      break;
  }
}
