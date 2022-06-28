#include "YDWidget.h"

YDWidget::YDWidget(int type, QWidget *parent) : QWidget{parent}, m_type{type} {}

int YDWidget::getType() { return m_type; }

void YDWidget::setType(int type) { m_type = type; }

void YDWidget::mouseReleaseEvent(QMouseEvent *) { emit sigClicked(m_type); }
