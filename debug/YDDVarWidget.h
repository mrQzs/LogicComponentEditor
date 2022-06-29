#ifndef YDDVARWIDGET_H
#define YDDVARWIDGET_H

#include <QDialog>

#include "ProtocolClientImpl.h"
#include "ProtocolImp.h"

class YDDAxisVarWidget;
class YDDVariableWidget;
class QTreeWidget;
class QTreeWidgetItem;
class QLabel;
class YDState;
class QPushButton;

class YDDVarWidget : public QDialog {
  Q_OBJECT
 public:
  YDDVarWidget(QWidget *parent = nullptr);
  ~YDDVarWidget();

 public:
  void updateData();

 private slots:
  void slotTreeDooubleClick(const QModelIndex &index);

 signals:
  void start();
  void stop();
  void updateTime(int);

 private:
  void initUi();
  void initTree();

  void showWidget(int type);

 private:
  QTreeWidget *m_menuTree;
  QWidget *m_widget;

  YDDVariableWidget *m_varW;
  YDDAxisVarWidget *m_axisVarW;

  QTreeWidgetItem *m_smi;
  QTreeWidgetItem *m_ssi;

  int m_type;
};
#endif  // YDDVARWIDGET_H
