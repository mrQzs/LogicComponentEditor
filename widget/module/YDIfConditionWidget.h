#ifndef YDIFCONDITIONWIDGET_H
#define YDIFCONDITIONWIDGET_H

#include <QWidget>

#include "debug/YDDgHelper.h"
#include "yd_project.h"

class QLabel;
class YDModule;
class YDModuleConditionWidget;
class YDTask;
class YDModuleHead;
;

class YDIfConditionWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDIfConditionWidget(YDModule *m, QWidget *parent = nullptr);

 public:
  int high() const;
  void init();
  void setText(const QString &text);
  void resizeModule();

 public:
  QList<uint32> getTrueProcessIds(uint32 id);

 signals:
  void sizeNeedChanged(YDModule *);

 public:
  void addTrueModules(YDTask *task,
                      const std::vector<yd::lg::LogicProcess *> &list);

  void setState(const QMap<uint32, yd::proto::ProcState> &map);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *);

 private slots:
  void slotAddNew();
  void slotShow(bool);

 private:
  YDModule *m_root;
  YDModuleHead *m_head;
  YDModuleConditionWidget *m_ifWidget;
  bool m_isHide;
};

#endif  // YDIFCONDITIONWIDGET_H
