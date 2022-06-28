#ifndef YDTREEVIEW_H
#define YDTREEVIEW_H

#include <QTreeView>

class YDTreeView : public QTreeView {
  Q_OBJECT
 public:
  YDTreeView(QWidget *parent = nullptr);

 public:
  void setEdit(const QModelIndex &index);
};

#endif  // YDTREEVIEW_H
