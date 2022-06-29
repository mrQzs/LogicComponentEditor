#include "YDPropertyIOVar.h"

#include <QComboBox>
#include <QStringDecoder>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "modules/YDModules.h"

YDPropertyIOVar::YDPropertyIOVar(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {}

QVariant YDPropertyIOVar::value(YDModule *m) const {
  auto p = const_cast<YDPropertyIOVar *>(this);
  p->updateStrList();
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyIOVar::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyIOVar::hasEditor() const { return true; }

QWidget *YDPropertyIOVar::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyIOVar::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyIOVar::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyIOVar::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto varList = YDProjectManage::getAllVirtualVariables();
  for (auto a : varList) {
    QString name = STRTQSTR(a->variable_name.c_str());
    m_enum << name;
  }
}
