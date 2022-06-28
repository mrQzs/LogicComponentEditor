#ifndef YDPROGRAMDIALOG_H
#define YDPROGRAMDIALOG_H

#include "widget/YDDialog.h"

class YDCodeEditor;
class YDBuildOptDialog;
class YDModule;
class QPushButton;

class YDProgramDIalog : public YDDialog {
  Q_OBJECT
 public:
  YDProgramDIalog(YDModule* m, QWidget* parent = nullptr);

 public:
  virtual QStringList textList() const;
  virtual void setTextList(const QStringList& list);
  void setType(int);
  bool isSaved();

 signals:
  void sigResult(const QString&);

 private slots:
  void slotSaveClicked();
  void slotCompileClicked();
  void slotClose(bool);

 private:
  QPushButton* m_btn;
  YDModule* m_module;
  YDCodeEditor* m_widget;
  bool m_isSaved;
  bool m_isCompile;
};

#endif  // YDPROGRAMDIALOG_H
