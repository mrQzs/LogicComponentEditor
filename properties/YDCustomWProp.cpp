#include "YDCustomWProp.h"

#include "modules/YDModule.h"
#include "widget/YDConditionDialog.h"
#include "widget/YDInplaceWaitDialog.h"
#include "widget/YDSetVariableDialog.h"
#include "widget/property/YDAlarmAction.h"
#include "widget/property/YDProgramDIalog.h"

YDCustomWProp::YDCustomWProp(WidgetType type, YDProperty *parent)
    : YDProperty{parent}, m_module{nullptr}, m_type{type} {}

YDCustomWProp::YDCustomWProp(YDModule *m, WidgetType type, YDProperty *parent)
    : YDProperty{parent}, m_module{m}, m_type{type} {}

bool YDCustomWProp::hasEditor() const { return true; }

QWidget *YDCustomWProp::editor(QWidget *parent) {
  switch (m_type) {
    case e_CONDITION:
      m_widget = new YDConditionDialog();
      break;
    case e_ALARMACTION:
      m_widget = new YDAlarmAction(m_module);
      break;
    case e_INPLACEWAIT:
      m_widget = new YDInplaceWaitDialog();
      break;
    case e_SETVARIABLE:
      m_widget = new YDSetVariableDialog();
      break;
    case e_PROGRAM: {
      m_widget = new YDProgramDIalog(m_module);
      auto ww = reinterpret_cast<YDProgramDIalog *>(m_widget);
      ww->setType(m_module->getCodeType());
    } break;
    default:
      break;
  }
  return m_widget;
}

void YDCustomWProp::updateEditor(YDModule *m) {
  auto list = get(m);

  switch (m_type) {
    case e_CONDITION:
      m_widget->resize(600, 600);
      break;
    case e_INPLACEWAIT:
      m_widget->resize(350, 400);
      break;
    case e_SETVARIABLE:
      m_widget->resize(600, 600);
      break;
    case e_PROGRAM: {
      m_widget->resize(1200, 810);
      auto ww = reinterpret_cast<YDProgramDIalog *>(m_widget);
      ww->setType(m_module->getCodeType());
    } break;
    default:
      break;
  }

  m_widget->setModal(true);

  if (!list.isEmpty()) m_widget->setTextList(list);
}

void YDCustomWProp::updateWidget(YDModule *m) {
  if (m_widget->result() == QDialog::Accepted) set(m, m_widget->textList());
}

QVariant YDCustomWProp::value(YDModule *m) const {
  const QStringList items = get(m);
  return items.isEmpty() ? "Empty list" : items.join(",");
}

void YDCustomWProp::setValue(YDModule *m, QVariant value) {
  if (value.typeId() != QMetaType::QStringList) {
    QVariantList list = value.toList();
    QStringList items;
    for (const QVariant &p : list)
      if (p.typeId() == QMetaType::QString) items << p.toString();

    set(m, items);
  }
}
