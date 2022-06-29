#ifndef YDCODEMANAGE_H
#define YDCODEMANAGE_H

#include <QDialog>
#include <QModelIndex>

#include "yd_project.h"

class YDCodeEditor;

class YDCodeManage : public QDialog {
  Q_OBJECT
 public:
  YDCodeManage(QWidget *parent = nullptr);

 public:
  void setScript(yd::adv::ExtendScript *script);

 protected:
  void closeEvent(QCloseEvent *);

 signals:
  void sigResult(const QString &);

 private slots:
  void slotSaveClicked();
  void slotCompileClicked();

 private:
  YDCodeEditor *m_codeW;
  yd::adv::ExtendScript *m_script;
  QString m_code;
};

#endif  // YDCODEMANAGE_H
