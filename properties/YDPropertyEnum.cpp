#include "YDPropertyEnum.h"

#include <QComboBox>

YDPropertyEnum::YDPropertyEnum(QStringList enumText, YDProperty *parent)
    : YDProperty{parent}, m_enum{enumText}, m_widget(nullptr) {}

QVariant YDPropertyEnum::value(YDModule *m) const {
  int index = get(m);
  if (index < 0 || index >= m_enum.size()) index = 0;
  return m_enum.at(index);
}

void YDPropertyEnum::setValue(YDModule *m, QVariant value) {
  int index = m_enum.indexOf(value.toString());
  if (index < 0) index = 0;
  set(m, index);
}

bool YDPropertyEnum::hasEditor() const { return true; }

QWidget *YDPropertyEnum::editor(QWidget *parent) {
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyEnum::updateEditor(YDModule *m) {
  m_widget->setCurrentIndex(get(m));
}

void YDPropertyEnum::updateWidget(YDModule *m) {
  set(m, m_widget->currentIndex());
}
