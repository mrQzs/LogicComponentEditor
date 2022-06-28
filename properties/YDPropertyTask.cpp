#include "YDPropertyTask.h"

#include <QComboBox>
#include <QStringDecoder>

#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "modules/YDModules.h"

YDPropertyTask::YDPropertyTask(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {}

QVariant YDPropertyTask::value(YDModule *m) const {
  auto p = const_cast<YDPropertyTask *>(this);
  p->updateStrList();
  auto str = get(m);
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyTask::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toString());
}

bool YDPropertyTask::hasEditor() const { return true; }

QWidget *YDPropertyTask::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);
  m_widget->addItems(m_enum);
  return m_widget;
}

void YDPropertyTask::updateEditor(YDModule *m) {
  int index = m_enum.indexOf(get(m));
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyTask::updateWidget(YDModule *m) {
  set(m, m_widget->currentText());
}

void YDPropertyTask::updateStrList() {
  m_enum.clear();
  m_enum << "";
  std::map<uint32, std::string> name;
  YDProjectManage::GetTaskNames(name);
  std::map<uint32, std::string>::iterator itor = name.begin();
  for (; itor != name.end(); ++itor) {
    m_enum << QString::fromLocal8Bit(itor->second.c_str());
  }
}
