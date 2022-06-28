#include "YDPropertyName.h"

#include "widget/YDNameLineEdit.h"

YDPropertyName::YDPropertyName(YDProperty *parent) : YDPropertyType{parent} {}

QWidget *YDPropertyName::editor(QWidget *parent) {
  m_widget = new YDNameLineEdit(parent);
  return m_widget;
}

void YDPropertyName::updateEditor(YDModule *m) { m_widget->setText(get(m)); }

void YDPropertyName::updateWidget(YDModule *m) { set(m, m_widget->text()); }
