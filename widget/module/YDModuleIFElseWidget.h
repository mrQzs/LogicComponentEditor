#ifndef YDMODULEIFELSEWIDGET_H
#define YDMODULEIFELSEWIDGET_H

#include <QWidget>

#include "yd_protocol.h"

class QLabel;
class YDModule;
class YDModuleConditionWidget;
class YDTask;
class YDModuleHead;

class YDModuleIFElseWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDModuleIFElseWidget(YDModule *m, QWidget *parent = nullptr);

 public:
  int high() const;
  void init();
  void setText(const QString &text);
  void resizeModule();

 public:
  QList<uint32> getTrueProcessIds(uint32 id);
  QList<uint32> getFalseProcessIds(uint32 id);

 signals:
  void sizeNeedChanged(YDModule *);

 public:
  void addTrueModules(YDTask *task,
                      const std::vector<yd::lg::LogicProcess *> &list);
  void addFalseModules(YDTask *task,
                       const std::vector<yd::lg::LogicProcess *> &list);

  void setState(const QMap<uint32, yd::proto::ProcState> &map);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *);

 private slots:
  void slotAddNew();
  void slotShow1(bool);
  void slotShow2(bool);

 private:
  YDModule *m_root;
  YDModuleHead *m_head1;
  YDModuleHead *m_head2;
  YDModuleConditionWidget *m_ifWidget;
  YDModuleConditionWidget *m_elseWidget;

  bool m_isHide1;
  bool m_isHide2;
};

#endif  // YDMODULEIFELSEWIDGET_H
