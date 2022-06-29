#include "YDPropertyAoVar.h"

#include <QComboBox>
#include <QStringDecoder>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "modules/YDModules.h"

YDPropertyAoVar::YDPropertyAoVar(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {}

QVariant YDPropertyAoVar::value(YDModule *m) const {
  auto p = const_cast<YDPropertyAoVar *>(this);
  p->updateStrList();
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyAoVar::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyAoVar::hasEditor() const { return true; }

QWidget *YDPropertyAoVar::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyAoVar::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyAoVar::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyAoVar::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto varList = YDProjectManage::getAOInfos();
  for (auto a : varList) {
    QString name = STRTQSTR(a->io_name.c_str());
    m_enum << name;
  }
}
