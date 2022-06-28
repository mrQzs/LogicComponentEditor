#include "YDPropertyAxis.h"

#include <QComboBox>
#include <QDebug>
#include <QStringDecoder>

#include "core/YDProjectManage.h"

YDPropertyAxis::YDPropertyAxis(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {
  updateStrList();
}

QVariant YDPropertyAxis::value(YDModule *m) const {
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyAxis::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyAxis::hasEditor() const { return true; }

QWidget *YDPropertyAxis::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyAxis::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyAxis::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyAxis::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto axisList = YDProjectManage::getAxisList();
  for (auto a : axisList) {
    QString name = QString::fromLocal8Bit(a->axis_name.c_str());
    m_enum << name;
  }
}
