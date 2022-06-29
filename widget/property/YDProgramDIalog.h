#ifndef YDPROGRAMDIALOG_H
#define YDPROGRAMDIALOG_H

#include "widget/YDDialog.h"

class YDCodeEditor;
class YDBuildOptDialog;
class YDModule;
class QPushButton;
class QLabel;

class YDProgramDIalog : public YDDialog {
  Q_OBJECT
 public:
  YDProgramDIalog(YDModule* m, QWidget* parent = nullptr);

 public:
  virtual QStringList textList() const;
  virtual void setTextList(const QStringList& list);
  void setType(int);

 protected:
  void mousePressEvent(QMouseEvent* e) override;
  void mouseMoveEvent(QMouseEvent* e) override;
  void mouseReleaseEvent(QMouseEvent* e) override;
  void paintEvent(QPaintEvent* event) override;

 signals:
  void sigResult(const QString&);

 private slots:
  void slotSaveClicked();
  void slotCompileClicked();
  void slotClose(bool);

 private:
  QLabel* m_titleLabel;
  QPushButton* m_btn;
  YDModule* m_module;
  YDCodeEditor* m_widget;
  bool m_isCompile;
  QPoint m_curPos;
  bool m_clicked;
  QString m_code;
};

#endif  // YDPROGRAMDIALOG_H
