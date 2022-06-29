#include "YDPropertyTask.h"

#include <QComboBox>
#include <QStringDecoder>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "modules/YDModules.h"

YDPropertyTask::YDPropertyTask(YDProperty *parent)
    : YDProperty{parent}, m_widget(nullptr) {}

QVariant YDPropertyTask::value(YDModule *m) const {
  auto p = const_cast<YDPropertyTask *>(this);
  p->updateStrList();
  auto str = YDProjectManage::getTaskName(get(m));
  int index = m_enum.indexOf(str);
  if (index < 0) return m_enum.at(0);
  return m_enum.at(index);
}

void YDPropertyTask::setValue(YDModule *m, QVariant value) {
  Q_ASSERT(m_enum.indexOf(value.toString()) >= 0);
  set(m, value.toUInt());
}

bool YDPropertyTask::hasEditor() const { return true; }

QWidget *YDPropertyTask::editor(QWidget *parent) {
  updateStrList();
  m_widget = new QComboBox(parent);

  for (int i = 0; i < m_enum.size(); ++i) {
    m_widget->addItem(m_enum[i]);
    m_widget->setItemData(i, m_idList[i], Qt::UserRole);
  }

  return m_widget;
}

void YDPropertyTask::updateEditor(YDModule *m) {
  qDebug() << m_widget->currentText();
  auto str = YDProjectManage::getTaskName(get(m));
  auto index = m_widget->findText(str);
  index < 0 ? 0 : index;
  m_widget->setCurrentIndex(index);
}

void YDPropertyTask::updateWidget(YDModule *m) {
  auto index = m_widget->currentIndex() - 1;
  uint32 id = 0;
  if (index >= 0) id = m_idList[m_widget->currentIndex() - 1];

  set(m, id);
}

void YDPropertyTask::updateStrList() {
  m_enum.clear();
  m_enum << "";
  std::map<uint32, std::string> name;
  YDProjectManage::GetTaskNames(name);
  std::map<uint32, std::string>::iterator itor = name.begin();
  for (; itor != name.end(); ++itor) {
    m_idList.push_back(itor->first);
    m_enum << STRTQSTR(itor->second.c_str());
  }
}
