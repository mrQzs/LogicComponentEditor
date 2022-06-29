#include "YDTableView.h"

#include <QMouseEvent>

YDTableView::YDTableView(QWidget *parent) : QTableView{parent} {}

YDSingleTableView::YDSingleTableView(QWidget *parent) : QTableView{parent} {}

void YDSingleTableView::mousePressEvent(QMouseEvent *event) {
  auto index = this->indexAt(event->pos());
  clearFocus();
  if (index.isValid()) {
    if (index == m_curIndex) {
      edit(index, QTableView::CurrentChanged, nullptr);
    } else
      m_curIndex = index;
  }
  QTableView::mousePressEvent(event);
}
