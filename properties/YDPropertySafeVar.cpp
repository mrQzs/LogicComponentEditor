#include "YDPropertySafeVar.h"

#include <QComboBox>
#include <QDebug>
#include <QStringDecoder>

#include "core/YDProjectManage.h"

YDPropertySafeVar::YDPropertySafeVar(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {
  updateStrList();
}

QVariant YDPropertySafeVar::value(YDModule *m) const {
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertySafeVar::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertySafeVar::hasEditor() const { return true; }

QWidget *YDPropertySafeVar::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertySafeVar::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertySafeVar::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertySafeVar::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto varList = YDProjectManage::getAllSafeVariables();
  for (auto a : varList) {
    QString name = QString::fromLocal8Bit(a->variable_name.c_str(),
                                          a->variable_name.size());
    m_enum << name;
  }
}
