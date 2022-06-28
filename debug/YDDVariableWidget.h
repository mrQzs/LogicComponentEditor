#ifndef YDDVARIABLEWIDGET_H
#define YDDVARIABLEWIDGET_H

#include <QWidget>

class YDTreeView;
class YDVariableGroupModel;
class YDDVariableView;
class YDDVariableModel;
class YDDVarDeletedage;
class YDVarSetDialog;

class YDDVariableWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDDVariableWidget(QWidget *parent = nullptr);

 public:
  void updateData();

 signals:

 private slots:
  void slotItemClicked(const QModelIndex &index);
  void slotItemDBClicked(const QModelIndex &index);
  void slotItemUpdate(const QModelIndex &index);

 private:
  YDTreeView *m_view1;
  YDVariableGroupModel *m_model1;
  YDDVariableView *m_view2;
  YDDVariableModel *m_model2;
  YDVarSetDialog *m_setDialog;
  // YDDVarDeletedage *m_deletegate;
};

#endif  // YDDVARIABLEWIDGET_H
