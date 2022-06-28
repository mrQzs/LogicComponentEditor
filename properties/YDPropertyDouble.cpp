#include "YDPropertyDouble.h"

#include <QDoubleSpinBox>

YDPropertyDouble::YDPropertyDouble(double min, double max, YDProperty *parent)
    : YDPropertyType{parent}, m_min{min}, m_max{max}, m_widget{nullptr} {}

YDPropertyDouble::YDPropertyDouble(double min, double max, QString surfix,
                                   YDProperty *parent)
    : YDPropertyType{parent},
      m_min{min},
      m_max{max},
      m_surfix{surfix},
      m_widget{nullptr} {}

QWidget *YDPropertyDouble::editor(QWidget *parent) {
  m_widget = new QDoubleSpinBox(parent);
  m_widget->setRange(m_min, m_max);
  m_widget->setSuffix(m_surfix);
  m_widget->setDecimals(5);
  m_widget->setSingleStep(0.01);
  return m_widget;
}

void YDPropertyDouble::updateEditor(YDModule *m) { m_widget->setValue(get(m)); }

void YDPropertyDouble::updateWidget(YDModule *m) { set(m, m_widget->value()); }
