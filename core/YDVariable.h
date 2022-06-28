#ifndef YDVARIABLE_H
#define YDVARIABLE_H

#include <QList>
#include <QString>
#include <QWidget>

#include "YDProjectManage.h"

class YDNameLineEdit;

class YDVariable {
 public:
  YDVariable(YDVariable* parent = nullptr);
  YDVariable(yd::vr::VariableGroup* vg, YDVariable* parent = nullptr);
  YDVariable(yd::vr::SystemVariable* vr, YDVariable* parent = nullptr);

  ~YDVariable();

 public:
  // get
  YDVariable* parent() const;
  QString name() const;
  QList<YDVariable*> childs() const;
  int childSize() const;
  YDVariable* child(int index) const;
  int row() const;
  uint16 groupId() const;
  QWidget* editor(QWidget* parent);

  // set
  void setName(const QString& name);

  // other
  void addChild(YDVariable* var);
  void delChild(YDVariable* var);

  void appendChild(YDVariable* pChild);
  void insertChild(int idx, YDVariable* pChild);
  void removeChild(YDVariable* p);

  void initChild(const std::vector<yd::vr::VariableGroup*>& list);

 private:
  yd::vr::VariableGroup* m_varGroup;
  yd::vr::SystemVariable* m_var;

 private:
  YDVariable* m_parent;
  QList<YDVariable*> m_childs;
  YDNameLineEdit* m_widget;
};

#endif  // YDVARIABLE_H
