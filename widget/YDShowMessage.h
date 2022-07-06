#ifndef YDSHOWMESSAGE_H
#define YDSHOWMESSAGE_H

#include <QDialog>

#include "common/YDGlobal.h"

class QTextEdit;
class YDShowMessage : public QDialog {
  Q_OBJECT
 public:
  YDShowMessage(QWidget *parent = nullptr);

  void setShowMessage(const QString &info, const LogLevel &level);

 private:
  QTextEdit *m_logText;
  QString m_traceColor;
  QString m_debugColor;
  QString m_infoColor;
  QString m_warnColor;
  QString m_errorColor;
  QString m_fatalColor;
};

#endif  // YDSHOWMESSAGE_H
