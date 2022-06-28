#include "YDPropertyInt.h"

#include <QSpinBox>

YDPropertyInt::YDPropertyInt(int min, int max, YDProperty *parent)
    : YDPropertyType{parent}, m_min{min}, m_max{max}, m_widget{nullptr} {}

YDPropertyInt::YDPropertyInt(int min, int max, QString surfix,
                             YDProperty *parent)
    : YDPropertyType{parent},
      m_min{min},
      m_max{max},
      m_surfix{surfix},
      m_widget{nullptr} {}

QWidget *YDPropertyInt::editor(QWidget *parent) {
  m_widget = new QSpinBox(parent);
  m_widget->setRange(m_min, m_max);
  m_widget->setSuffix(m_surfix);
  return m_widget;
}

void YDPropertyInt::updateEditor(YDModule *m) { m_widget->setValue(get(m)); }

void YDPropertyInt::updateWidget(YDModule *m) { set(m, m_widget->value()); }
