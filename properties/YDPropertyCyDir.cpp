#include "YDPropertyCyDir.h"

#include <QComboBox>
#include <QDebug>
#include <QStringDecoder>

#include "core/YDProjectManage.h"
#include "modules/YDModule.h"

YDPropertyCyDir::YDPropertyCyDir(YDModule *m, YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr), m_module{m} {
  updateStrList();
}

QVariant YDPropertyCyDir::value(YDModule *m) const {
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyCyDir::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyCyDir::hasEditor() const { return true; }

QWidget *YDPropertyCyDir::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyCyDir::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyCyDir::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyCyDir::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto varList = YDProjectManage::getCylinders();
  auto cyname = m_module->getCylinder();
  if (!cyname.isEmpty()) {
    for (auto a : varList) {
      QString name = QString::fromLocal8Bit(a->base.name);
      if (name == cyname) {
        m_enum << QString::fromLocal8Bit(a->direction1_name);
        m_enum << QString::fromLocal8Bit(a->direction2_name);
        break;
      }
    }
  }
}
