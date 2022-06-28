#include "YDPropertyMSpeed.h"

#include <QComboBox>
#include <QStringDecoder>

#include "core/YDProjectManage.h"
#include "modules/YDModules.h"

YDPropertyMSpeed::YDPropertyMSpeed(YDModule *m, YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr), m_module{m} {}

QVariant YDPropertyMSpeed::value(YDModule *m) const {
  auto p = const_cast<YDPropertyMSpeed *>(this);
  p->updateStrList();
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyMSpeed::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyMSpeed::hasEditor() const { return true; }

QWidget *YDPropertyMSpeed::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyMSpeed::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyMSpeed::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyMSpeed::updateStrList() {
  m_enum.clear();
  if (0 == m_module->getSpeedWay()) {
    m_enum << "0%"
           << "5%"
           << "10%"
           << "15%"
           << "20%"
           << "25%"
           << "30%"
           << "35%"
           << "40%"
           << "45%"
           << "50%"
           << "55%"
           << "60%"
           << "65%"
           << "70%"
           << "75%"
           << "80%"
           << "85%"
           << "90%"
           << "95%"
           << "100%";
  } else {
    m_enum << "";
    auto varList = YDProjectManage::getAllVirtualVariables();
    for (auto a : varList) {
      QString name = QString::fromLocal8Bit(a->variable_name.c_str(),
                                            a->variable_name.size());
      m_enum << name;
    }
  }
}
