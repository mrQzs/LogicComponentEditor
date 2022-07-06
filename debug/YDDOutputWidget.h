#ifndef YDDOUTPUTWIDGET_H
#define YDDOUTPUTWIDGET_H

#include <QWidget>

class YDOutputStateView;
class YDDOutputModel;
class YDDOutputDeletegate;

class YDDOutputWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDDOutputWidget(QWidget* parent = nullptr);

 public:
  void updateData();

 signals:
  void toclose();

 protected:
  void closeEvent(QCloseEvent*);

 private:
  YDOutputStateView* m_view1;
  YDOutputStateView* m_view2;
  YDDOutputDeletegate* m_deletegate1;
  YDDOutputDeletegate* m_deletegate2;
  YDDOutputModel* m_model1;
  YDDOutputModel* m_model2;
};

#endif  // YDDOUTPUTWIDGET_H
