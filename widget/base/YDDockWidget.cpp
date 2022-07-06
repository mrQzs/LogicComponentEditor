#include "YDDockWidget.h"

#include <QCloseEvent>

YDDockWidget::YDDockWidget(QWidget *parent) : QDockWidget(parent) {}

void YDDockWidget::closeEvent(QCloseEvent *event) {
  emit sigCloseClicked();
  event->accept();
}
