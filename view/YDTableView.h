#ifndef YDTABLEVIEW_H
#define YDTABLEVIEW_H

#include <QTableView>

class YDTableView : public QTableView {
  Q_OBJECT
 public:
  YDTableView(QWidget *parent = nullptr);
};

class YDAxisTableView : public QTableView {
  Q_OBJECT
 public:
  YDAxisTableView(QWidget *parent = nullptr);

 protected:
  void mousePressEvent(QMouseEvent *event);

 private:
  QModelIndex m_curIndex;
};

#endif  // YDTABLEVIEW_H
