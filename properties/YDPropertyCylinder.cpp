#include "YDPropertyCylinder.h"

#include <QComboBox>
#include <QDebug>
#include <QStringDecoder>

#include "core/YDProjectManage.h"

YDPropertyCylinder::YDPropertyCylinder(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {
  updateStrList();
}

QVariant YDPropertyCylinder::value(YDModule *m) const {
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyCylinder::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyCylinder::hasEditor() const { return true; }

QWidget *YDPropertyCylinder::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyCylinder::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyCylinder::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyCylinder::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto varList = YDProjectManage::getCylinders();
  for (auto a : varList) m_enum << QString::fromLocal8Bit(a->base.name.c_str());
}
