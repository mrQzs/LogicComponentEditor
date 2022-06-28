#include "YDPropertyModule.h"

#include <QComboBox>
#include <QStringDecoder>

#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "modules/YDModules.h"

YDPropertyModule::YDPropertyModule(YDModule *m, YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr), m_module{m} {}

QVariant YDPropertyModule::value(YDModule *m) const {
  auto p = const_cast<YDPropertyModule *>(this);
  p->updateStrList();
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyModule::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyModule::hasEditor() const { return true; }

QWidget *YDPropertyModule::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyModule::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyModule::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyModule::updateStrList() {
  m_enum.clear();
  m_enum << "";
  auto tid = m_module->getYDTask()->id();

  auto root = YDProjectManage::getYDTaskRoot();
  auto childs = root->childs();
  for (auto s : childs) {
    if (s->id() == tid) {
      QList<YDModule *> modules = s->getModules();
      for (auto m : modules) {
        if (m_module->name() != m->name()) m_enum << m->name();
      }
      break;
    }
  }
}
