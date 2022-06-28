#include "YDPropertyDoVar.h"

#include <QComboBox>
#include <QStringDecoder>

#include "core/YDProjectManage.h"
#include "modules/YDModules.h"

YDPropertyDoVar::YDPropertyDoVar(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {}

QVariant YDPropertyDoVar::value(YDModule *m) const {
  auto p = const_cast<YDPropertyDoVar *>(this);
  p->updateStrList();
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyDoVar::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyDoVar::hasEditor() const { return true; }

QWidget *YDPropertyDoVar::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyDoVar::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyDoVar::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyDoVar::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto varList = YDProjectManage::getDOInfos();
  for (auto a : varList) {
    QString name = QString::fromLocal8Bit(a->io_name.c_str());
    m_enum << name;
  }
}
