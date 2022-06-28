#include "YDDInputWidget.h"

#include <QHBoxLayout>
#include <QHeaderView>

#include "YDDInputModel.h"
#include "YDInputStateView.h"

YDDInputWidget::YDDInputWidget(QWidget *parent)
    : QWidget{parent},
      m_view1{new YDInputStateView(this)},
      m_view2{new YDInputStateView(this)},
      m_deletegate1{new YDDInputDeletegate(m_view1)},
      m_deletegate2{new YDDInputDeletegate(m_view2)},
      m_model1{new YDDInputModel(this)},
      m_model2{new YDDInputModel(this)} {
  auto hlay = new QHBoxLayout(this);
  m_model1->setGroup(0);
  m_model2->setGroup(1);

  m_view1->horizontalHeader()->setStretchLastSection(true);
  m_view1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  m_view2->horizontalHeader()->setStretchLastSection(true);
  m_view2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(20);
  hlay->addWidget(m_view1);
  hlay->addWidget(m_view2);

  m_view1->setModel(m_model1);
  m_view2->setModel(m_model2);

  m_view1->setItemDelegateForColumn(1, m_deletegate1);
  m_view2->setItemDelegateForColumn(1, m_deletegate2);

  m_model1->updateData();
  m_model2->updateData();
}

void YDDInputWidget::updateData() {
  m_model1->updateData();
  m_model2->updateData();
}
