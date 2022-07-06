#include "YDWidget.h"

#include <QDebug>

YDWidget::YDWidget(int type, QWidget *parent) : QWidget{parent}, m_type{type} {}

YDWidget::~YDWidget() { 
//qDebug() << "Enter in, Type:" << m_type; 
}

int YDWidget::getType() { return m_type; }

void YDWidget::setType(int type) { m_type = type; }

void YDWidget::mouseReleaseEvent(QMouseEvent *) { emit sigClicked(m_type); }
