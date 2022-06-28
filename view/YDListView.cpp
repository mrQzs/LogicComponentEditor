#include "YDListView.h"

YDListView::YDListView(QWidget *parent) : QListView{parent} {}

void YDListView::setEdit(const QModelIndex &index) {
  edit(index, YDListView::DoubleClicked, nullptr);
}
