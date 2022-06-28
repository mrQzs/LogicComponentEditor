#include "YDPropertyDelayValue.h"

#include <QDoubleValidator>
#include <QIntValidator>

#include "widget/YDIntVarComboBox.h"
#include "widget/YDNameLineEdit.h"

YDPropertyDelayValue::YDPropertyDelayValue(int type, YDProperty *parent)
    : YDProperty{parent}, m_type{type} {}

QWidget *YDPropertyDelayValue::editor(QWidget *parent) {
  switch (m_type) {
    case 1: {
      m_widget = new QLineEdit(parent);
    } break;
    case 2: {
      m_widget2 = new YDIntVarComboBox(parent);
    } break;
  }

  return m_widget;
}

void YDPropertyDelayValue::updateEditor(YDModule *m) {
  if (m_widget)
    m_widget->setText(get(m));
  else {
    int index = m_widget2->findText(get(m));
    index = index > 0 ? index : 0;
    m_widget2->setCurrentIndex(index);
  }
}

void YDPropertyDelayValue::updateWidget(YDModule *m) {
  if (m_widget)
    set(m, m_widget->text());
  else
    set(m, m_widget2->currentText());
}
