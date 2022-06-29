#include "YDPropertyInplaceWaitValue.h"

#include <QDoubleSpinBox>

#include "modules/YDModule.h"

YDPropertyInplaceWaitValue::YDPropertyInplaceWaitValue(YDModule *m, double min,
                                                       double max,
                                                       YDProperty *parent)
    : YDPropertyType{parent},
      m_module{m},
      m_min{min},
      m_max{max},
      m_widget{nullptr} {}

YDPropertyInplaceWaitValue::YDPropertyInplaceWaitValue(YDModule *m, double min,
                                                       double max,
                                                       QString surfix,
                                                       YDProperty *parent)
    : YDPropertyType{parent},
      m_module{m},
      m_min{min},
      m_max{max},
      m_surfix{surfix},
      m_widget{nullptr} {}

QWidget *YDPropertyInplaceWaitValue::editor(QWidget *parent) {
  m_widget = new QDoubleSpinBox(parent);
  m_widget->setRange(m_min, m_max);
  m_widget->setSuffix(m_surfix);
  m_widget->setDecimals(5);
  m_widget->setSingleStep(0.01);
  if (Module::Stop_Motion == m_module->type()) {
    if (m_module->getInplaceWait() == 2)
      m_widget->setEnabled(true);
    else
      m_widget->setDisabled(true);
  } else {
    if (m_module->getInplaceWait() == 3)
      m_widget->setEnabled(true);
    else
      m_widget->setDisabled(true);
  }

  return m_widget;
}

void YDPropertyInplaceWaitValue::updateEditor(YDModule *m) {
  m_widget->setValue(get(m));
}

void YDPropertyInplaceWaitValue::updateWidget(YDModule *m) {
  set(m, m_widget->value());
}
