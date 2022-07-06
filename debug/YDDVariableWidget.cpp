#include "YDDVariableWidget.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QTreeWidget>

#include "YDDVariableModel.h"
#include "YDDVariableview.h"
#include "YDDgHelper.h"
#include "YDVarSetDialog.h"
#include "core/YDProjectManage.h"
#include "core/YDVariable.h"
#include "model/YDVariableGroupModel.h"
#include "view/YDTreeView.h"

YDDVariableWidget::YDDVariableWidget(QWidget *parent)
    : QWidget{parent},
      m_view1{new YDTreeView(this)},
      m_model1{new YDVariableGroupModel(YDProjectManage::getVarRoot(), this)},
      m_view2{new YDDVariableView(this)},
      m_model2{new YDDVariableModel(this)},
      m_setDialog{nullptr} {
  m_view1->setFixedWidth(200);
  m_view2->horizontalHeader()->setStretchLastSection(true);
  m_view2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  m_view2->setSelectionBehavior(QAbstractItemView::SelectRows);

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_view1);
  hlay->addWidget(m_view2);

  m_model1->setState(false);
  m_view1->setModel(m_model1);
  m_view2->setModel(m_model2);
  m_view2->setColumnWidth(5, 180);

  connect(m_view1, &YDTreeView::clicked, this,
          &YDDVariableWidget::slotItemClicked);

  connect(m_view2, &YDDVariableView::doubleClicked, this,
          &YDDVariableWidget::slotItemDBClicked);
}

void YDDVariableWidget::updateData() {
  YDVariable *gp =
      reinterpret_cast<YDVariable *>(m_view1->currentIndex().internalPointer());
  if (gp) {
    m_model2->updateData(gp->groupId());
  }
}

void YDDVariableWidget::slotItemClicked(const QModelIndex &index) {
  YDVariable *var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var) {
    m_model2->updateData(var->groupId());
  }
}

void YDDVariableWidget::slotItemDBClicked(const QModelIndex &index) {
  YDVariable *gp =
      reinterpret_cast<YDVariable *>(m_view1->currentIndex().internalPointer());
  if (gp) {
    auto row = index.row();
    auto id = gp->groupId();
    yd::proto::MapId2VariableRTValue map;
    auto list = YDProjectManage::getAllVariables(id);
    YDDgHelper::getGroupedVariableValues(id, map);

    if (map.count(list[row]->variable_id) == 1) {
      yd::proto::VariableRTValue value = map.at(list[row]->variable_id);
      if (m_setDialog) delete m_setDialog;
      m_setDialog = new YDVarSetDialog(this);
      m_setDialog->setVar(list[row], value);

      m_setDialog->resize(280, 240);
      m_setDialog->open();
    } else {
      QMessageBox::warning(nullptr, YDDVariableWidget::tr("提示"),
                           YDDVariableWidget::tr("指定分组变量数据为空."));
    }
  }
}

void YDDVariableWidget::slotItemUpdate(const QModelIndex &index) {
  if (index.isValid()) {
  }
}
