#ifndef YDDINPUTWIDGET_H
#define YDDINPUTWIDGET_H

#include <QWidget>

class YDInputStateView;
class YDDInputModel;
class YDDInputDeletegate;

class YDDInputWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDDInputWidget(QWidget *parent = nullptr);

 public:
  void updateData();

 signals:
  void toclose();

 protected:
  void closeEvent(QCloseEvent *);

 private:
  YDInputStateView *m_view1;
  YDInputStateView *m_view2;
  YDDInputDeletegate *m_deletegate1;
  YDDInputDeletegate *m_deletegate2;
  YDDInputModel *m_model1;
  YDDInputModel *m_model2;
};

#endif  // YDDINPUTWIDGET_H
