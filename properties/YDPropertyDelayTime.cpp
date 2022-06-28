#include "YDPropertyDelayTime.h"

#include <QComboBox>
#include <QStringDecoder>

#include "modules/YDModules.h"
#include "widget/YDIntVarComboBox.h"
#include "widget/YDNameLineEdit.h"

YDPropertyDelayTime::YDPropertyDelayTime(YDModule *m, YDProperty *parent)
    : YDProperty{parent}, m_widget1(nullptr), m_widget2{nullptr}, m_module{m} {}

QVariant YDPropertyDelayTime::value(YDModule *m) const {
  if (0 == m_module->getDelayType()) {
    auto v = get(m).toULongLong();
    if (0 == v) m->setDelayValue("0");
  }
  return get(m);
}

void YDPropertyDelayTime::setValue(YDModule *m, QVariant value) {
  set(m, value.toString());
}

bool YDPropertyDelayTime::hasEditor() const { return true; }

QWidget *YDPropertyDelayTime::editor(QWidget *parent) {
  if (0 == m_module->getDelayType()) {
    m_widget1 = new QLineEdit(parent);
    return m_widget1;
  } else {
    m_widget2 = new YDIntVarComboBox(parent);
    return m_widget2;
  }
}

void YDPropertyDelayTime::updateEditor(YDModule *m) {
  if (0 == m_module->getDelayType()) {
    m_widget1->setText(get(m));
  } else {
    int index = m_enum.indexOf(get(m));
    index < 0 ? 0 : index;
    m_widget2->setCurrentIndex(index);
  }
}

void YDPropertyDelayTime::updateWidget(YDModule *m) {
  if (0 == m_module->getDelayType())
    set(m, m_widget1->text());
  else
    set(m, m_widget2->currentText());
}
