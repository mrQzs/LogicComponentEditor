#ifndef YDLISTVIEW_H
#define YDLISTVIEW_H

#include <QListView>

class YDListView : public QListView {
  Q_OBJECT
 public:
  YDListView(QWidget* parent = nullptr);

 public:
  void setEdit(const QModelIndex& index);
};

#endif  // YDLISTVIEW_H
