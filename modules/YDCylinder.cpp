#include "YDCylinder.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDCylinderName : public YDPropertyName {
 public:
  QString name() const { return YDCylinderName::tr("名称"); }
  QString codeName() const { return "Name"; }

 protected:
  virtual QString get(YDModule *m) const { return m->name(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) {
      auto name = QSTRTSTR(str);
      int ret = YDProjectManage::updateLogicProcessName(
          m->getYDTask()->id(), m->getLogicProcessId(), name);
      switch (ret) {
        case -1:
          QMessageBox::warning(nullptr, YDCylinderName::tr("错误"),
                               YDCylinderName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDCylinderName::tr("错误"),
                               YDCylinderName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDCylinderCy : public YDPropertyCylinder {
 public:
  QString name() const { return YDCylinderCy::tr("气油缸"); }
  QString codeName() const { return "Cylinder"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getCylinder(); }
  virtual void set(YDModule *m, QString str) { m->setCylinder(str); }
};

class YDCylinderDir : public YDPropertyCyDir {
 public:
  YDCylinderDir(YDModule *m) : YDPropertyCyDir{m} {}
  virtual QString name() const { return YDCylinderDir::tr("运动方向"); }
  virtual QString codeName() const { return "Dir"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getCylinderDir(); }
  virtual void set(YDModule *m, QString str) { m->setCylinderDir(str); }
};

YDCylinder::YDCylinder() {
  setPreview(QPixmap(":/Module/Cylinder.png"));
  auto w = new YDModuleWidget(this, IoColor, IoFColor);

  setWidget(w);

  m_properties << new YDCylinderName;
  m_properties << new YDCylinderCy;
  m_properties << new YDCylinderDir(this);
}

Module::Type YDCylinder::type() const { return Module::Cylinder; }

void YDCylinder::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachCylinderModule(logicProcessId, m_cylinderModule);
  Q_ASSERT(m_cylinderModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDCylinder::tr("气油缸%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDCylinder::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachCylinderModule(lp->id, m_cylinderModule);
  Q_ASSERT(m_cylinderModule);
  setData();
}

void YDCylinder::getData() {
  m_logicProcess->type = LOGIC_PROCESS_CYLINDER;
  auto cy = getCylinder();
  auto list = YDProjectManage::getCylinders();
  for (auto v : list) {
    auto name = STRTQSTR(v->base.name.c_str());
    if (cy == name) {
      m_cylinderModule->device_id = v->base.id;
      if (v->direction1_control.action_value ==
          v->direction2_control.action_value) {
        auto d1name = STRTQSTR(v->direction1_name.c_str());
        if (d1name == getCylinderDir())
          m_cylinderModule->control_direction = 1;
        else
          m_cylinderModule->control_direction = 2;
      } else {
        auto d1name = STRTQSTR(v->direction1_name.c_str());
        if (d1name == getCylinderDir())
          m_cylinderModule->control_direction = 0;
        else
          m_cylinderModule->control_direction = 1;
      }
      break;
    }
  }
}

void YDCylinder::setData() {
  auto list = YDProjectManage::getCylinders();
  for (auto v : list) {
    if (v->base.id == m_cylinderModule->device_id) {
      setCylinder(STRTQSTR(v->base.name));
      if (v->direction1_control.action_value ==
          v->direction2_control.action_value) {
        if (1 == m_cylinderModule->control_direction)
          setCylinderDir(STRTQSTR(v->direction1_name.c_str()));
        else
          setCylinderDir(STRTQSTR(v->direction2_name.c_str()));
      } else {
        if (1 == m_cylinderModule->control_direction)
          setCylinderDir(STRTQSTR(v->direction2_name.c_str()));
        else
          setCylinderDir(STRTQSTR(v->direction1_name.c_str()));
      }
    }
  }
}
