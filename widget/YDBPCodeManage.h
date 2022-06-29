#ifndef YDBPCODEMANAGE_H
#define YDBPCODEMANAGE_H

#include <QDialog>
#include <QModelIndex>

#include "yd_project.h"

class YDCodeEditor;

class YDBPCodeManage : public QDialog {
  Q_OBJECT
 public:
  YDBPCodeManage(QWidget *parent = nullptr);

 public:
  void setScript();

 protected:
  void closeEvent(QCloseEvent *);

 signals:
  void sigResult(const QString &);

 private slots:
  void slotSaveClicked();
  void slotCompileClicked();

 private:
  YDCodeEditor *m_codeW;
  std::string m_name;
  uint8 m_type;
  QString m_code;
};

#endif  // YDBPCODEMANAGE_H
