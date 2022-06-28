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
};

#endif  // YDSHOWMESSAGE_H
