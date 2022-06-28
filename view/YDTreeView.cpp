#include "YDTreeView.h"

YDTreeView::YDTreeView(QWidget *parent) : QTreeView{parent} {}

void YDTreeView::setEdit(const QModelIndex &index) {
  edit(index, QTreeView::DoubleClicked, nullptr);
}
