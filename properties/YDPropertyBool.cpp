#include "YDPropertyBool.h"

#include <QCheckBox>

YDPropertyBool::YDPropertyBool(YDProperty *parent) : YDPropertyType{parent} {}

QWidget *YDPropertyBool::editor(QWidget *parent) {
  m_widget = new QCheckBox(parent);
  return m_widget;
}

void YDPropertyBool::updateEditor(YDModule *m) { m_widget->setChecked(get(m)); }

void YDPropertyBool::updateWidget(YDModule *m) {
  set(m, m_widget->checkState());
}
