#ifndef YDALARMACTION_H
#define YDALARMACTION_H

#include "widget/YDDialog.h"
#include "yd_project.h"

class QCheckBox;
class QLineEdit;
class YDModule;

class YDAlarmAction : public YDDialog {
  Q_OBJECT
 public:
  YDAlarmAction(YDModule *m, QWidget *parent = nullptr);

 public:
  // get
  virtual QStringList textList() const;

  // set
  virtual void setTextList(const QStringList &list);

  // QWidget interface
 protected:
  void focusOutEvent(QFocusEvent *e);

 public slots:
  void slotOkBtnClicked();
  void slotCancelBtnClicked();

  void slotcfChange(const QString &);
  void slotigChange(const QString &);
  void slotrtChange(const QString &);
  void slotspChange(const QString &);

  void slotcfChecked(bool);
  void slotigChecked(bool);
  void slotrtChecked(bool);
  void slotspChecked(bool);

 private:
  void setChecked(const QString &str);

 private:
  YDModule *m_module;

  QCheckBox *m_confirm;
  QLineEdit *m_cfEdit;

  QCheckBox *m_ignore;
  QLineEdit *m_igEdit;

  QCheckBox *m_retry;
  QLineEdit *m_rtEdit;

  QCheckBox *m_stop;
  QLineEdit *m_spEdit;

  QPushButton *m_okBtn;
  QPushButton *m_cancelBtn;

  QList<yd::lg::MessageAction *> m_actions;
};

#endif  // YDALARMACTION_H
