#ifndef YDMODULELOOPWIDGET_H
#define YDMODULELOOPWIDGET_H

#include <QWidget>

#include "debug/YDDgHelper.h"
#include "yd_protocol.h"

class QLabel;
class YDModule;
class YDModuleConditionWidget;
class YDTask;
class YDModuleHead;

class YDModuleLoopWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDModuleLoopWidget(int type, YDModule *m, QWidget *parent = nullptr);

 public:
  int high() const;
  void init();
  void setText(const QString &text);

 public:
  QList<uint32> getLoopModulesIds(uint32 id);
  void resizeModel();

 public:
  void addLoopModules(YDTask *task,
                      const std::vector<yd::lg::LogicProcess *> &list);
  void setState(const QMap<uint32, yd::proto::ProcState> &map);

 protected:
  void paintEvent(QPaintEvent *);

 signals:
  void sizeNeedChanged(YDModule *);

 private slots:
  void slotAddNew();
  void slotShow(bool);

 private:
  int m_type;
  YDModule *m_root;
  YDModuleHead *m_head;
  YDModuleConditionWidget *m_loopWidget;
  bool m_isHide;
};

#endif  // YDMODULELOOPWIDGET_H
