#include "YDPropertyString.h"

#include <QDoubleValidator>
#include <QIntValidator>

#include "widget/YDNameLineEdit.h"

YDPropertyString::YDPropertyString(int type, YDProperty *parent)
    : YDPropertyType{parent}, m_type{type} {}

QWidget *YDPropertyString::editor(QWidget *parent) {
  m_widget = new QLineEdit(parent);
  switch (m_type) {
    case 1:
      m_widget->setValidator(new QIntValidator(parent));
      break;
    case 2:
      m_widget->setValidator(new QDoubleValidator(parent));
      break;
  }

  return m_widget;
}

void YDPropertyString::updateEditor(YDModule *m) { m_widget->setText(get(m)); }

void YDPropertyString::updateWidget(YDModule *m) { set(m, m_widget->text()); }
