#include "YDPropertySpeedCard.h"

#include <QComboBox>
#include <QStringDecoder>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "modules/YDModules.h"

YDPropertySpeedCard::YDPropertySpeedCard(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {}

QVariant YDPropertySpeedCard::value(YDModule *m) const {
  auto p = const_cast<YDPropertySpeedCard *>(this);
  p->updateStrList();
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertySpeedCard::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertySpeedCard::hasEditor() const { return true; }

QWidget *YDPropertySpeedCard::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertySpeedCard::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertySpeedCard::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertySpeedCard::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto varList = YDProjectManage::getAllVirtualVariables();
  for (auto a : varList) {
    if (a->value_type == DATA_TYPE_AXIS_COORD) {
      QString name = STRTQSTR(a->variable_name.c_str());
      m_enum << name;
    }
  }
}
