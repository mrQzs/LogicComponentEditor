#include "YDVariable.h"

#include <QHBoxLayout>

#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDVariable::YDVariable(YDVariable *parent)
    : m_parent{parent},
      m_varGroup{nullptr},
      m_var{nullptr},
      m_widget{nullptr} {}

YDVariable::YDVariable(yd::vr::VariableGroup *vg, YDVariable *parent)
    : m_parent{parent}, m_varGroup{vg}, m_var{nullptr}, m_widget{nullptr} {}

YDVariable::YDVariable(yd::vr::SystemVariable *vr, YDVariable *parent)
    : m_parent{parent}, m_varGroup{nullptr}, m_var{vr}, m_widget{nullptr} {}

YDVariable::~YDVariable() {
  if (m_varGroup) YDProjectManage::deleteVariableGroup(m_varGroup->group_id);
  if (m_widget) delete m_widget;
}

YDVariable *YDVariable::parent() const { return m_parent; }

QString YDVariable::name() const {
  return QString::fromLocal8Bit(m_varGroup->group_name);
  ;
}

QList<YDVariable *> YDVariable::childs() const { return m_childs; }

int YDVariable::childSize() const { return m_childs.size(); }

YDVariable *YDVariable::child(int index) const {
  Q_ASSERT(0 <= index && index < m_childs.size());
  return m_childs[index];
}

int YDVariable::row() const {
  if (m_parent) return m_parent->childs().indexOf(this);
  return 0;
}

uint16 YDVariable::groupId() const {
  if (m_varGroup)
    return m_varGroup->group_id;
  else
    return 0;
}

QWidget *YDVariable::editor(QWidget *parent) {
  m_widget = new YDNameLineEdit(parent);
  return m_widget;
}

void YDVariable::setName(const QString &name) {
  m_varGroup->group_name = std::string(name.toLocal8Bit().data());
}

void YDVariable::addChild(YDVariable *var) {
  Q_ASSERT(var);
  m_childs.append(var);
}

void YDVariable::delChild(YDVariable *var) {
  Q_ASSERT(m_childs.removeOne(var));
  delete var;
  var = nullptr;
}

void YDVariable::appendChild(YDVariable *pChild) { m_childs.append(pChild); }

void YDVariable::insertChild(int idx, YDVariable *pChild) {
  m_childs.insert(idx, pChild);
}

void YDVariable::removeChild(YDVariable *p) {
  int index = m_childs.indexOf(p);
  Q_ASSERT(index >= 0);
  m_childs.removeAt(index);
  delete p;
  p = nullptr;
}

void YDVariable::initChild(const std::vector<yd::vr::VariableGroup *> &list) {
  for (auto t : list) {
    auto var = new YDVariable(t, this);
    addChild(var);
  }
}
