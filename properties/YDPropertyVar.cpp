#include "YDPropertyVar.h"

#include <QComboBox>
#include <QDebug>
#include <QStringDecoder>

#include "core/YDProjectManage.h"

YDPropertyVar::YDPropertyVar(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {
  updateStrList();
}

QVariant YDPropertyVar::value(YDModule *m) const {
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyVar::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyVar::hasEditor() const { return true; }

QWidget *YDPropertyVar::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyVar::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyVar::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyVar::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto varList = YDProjectManage::getAllVirtualVariables();
  for (auto a : varList) {
    if (a->value_type >= 3 && a->value_type <= 12) {
      QString name = QString::fromLocal8Bit(a->variable_name.c_str(),
                                            a->variable_name.size());
      m_enum << name;
    }
  }
}
