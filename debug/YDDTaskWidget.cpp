#include "YDDTaskWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "YDDgHelper.h"
#include "core/YDTask.h"
#include "model/YDMenuModel.h"
#include "view/YDTreeView.h"
#include "widget/YDNameLineEdit.h"
#include "widget/module/YDTabWidget.h"

YDDTaskWidget::YDDTaskWidget(QWidget *parent)
    : QWidget{parent},
      m_menuView{new YDTreeView(this)},
      m_model{new YDMenuModel(YDProjectManage::getYDTaskRoot(), this)},
      m_widget{nullptr},
      m_task{new QLabel(this)},
      m_taskEdit{new QLabel(this)},
      m_btn1{new QPushButton(this)},
      m_btn2{new QPushButton(this)} {
  m_menuView->setFixedWidth(200);

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_menuView);
  hlay->addStretch();

  m_menuView->setModel(m_model);
  m_menuView->setItemDelegate(new YDMenuDeletegate(m_menuView));

  connect(m_menuView, &QTreeView::clicked, this,
          &YDDTaskWidget::slotTaskItemClick);

  m_task->setText(YDDTaskWidget::tr("任务状态:"));
  m_taskEdit->setText(YDDTaskWidget::tr("未知"));
  m_taskEdit->setDisabled(true);

  m_btn1->setText(YDDTaskWidget::tr("开始调试"));
  m_btn2->setText(YDDTaskWidget::tr("停止调试"));

  m_task->hide();
  m_taskEdit->hide();
  m_taskEdit->setFixedWidth(100);
  m_btn1->hide();
  m_btn2->hide();

  connect(m_btn1, &QPushButton::clicked, this, &YDDTaskWidget::slotStartClick);
  connect(m_btn2, &QPushButton::clicked, this, &YDDTaskWidget::slotStopClick);
}

YDDTaskWidget::~YDDTaskWidget() {}

void YDDTaskWidget::updateDate() {
  auto index = m_menuView->currentIndex();
  YDTask *o = reinterpret_cast<YDTask *>(index.internalPointer());
  if (o) {
    auto id = o->id();
    yd::proto::TaskState state;
    YDDgHelper::getTaskState(id, &state);
    o->setState(state);

    QString strState;
    switch (state.state) {
      case LOGIC_STATE_READY:
        strState = YDDTaskWidget::tr("已就绪");
        break;
      case LOGIC_STATE_IN_PROCESSING:
        strState = YDDTaskWidget::tr("扫描中");
        break;
      case LOGIC_STATE_COMPLETED:
        strState = YDDTaskWidget::tr("已完成");
        break;
      case LOGIC_STATE_FAILED:
        strState = YDDTaskWidget::tr("已失败");
        break;
      default:
        strState = YDDTaskWidget::tr("未知");
        break;
    }

    m_taskEdit->setText(strState);
  }
}

void YDDTaskWidget::slotTaskItemClick(const QModelIndex &index) {
  YDTask *o = reinterpret_cast<YDTask *>(index.internalPointer());
  delete layout();
  m_widget = o->widget();

  auto hhlay = new QHBoxLayout;
  hhlay->addStretch();
  hhlay->addWidget(m_task);
  hhlay->addSpacing(10);
  hhlay->addWidget(m_taskEdit);
  hhlay->addSpacing(50);
  hhlay->addWidget(m_btn1);
  hhlay->addSpacing(10);
  hhlay->addWidget(m_btn2);
  hhlay->addStretch();

  m_task->show();
  m_taskEdit->show();
  m_btn1->show();
  m_btn2->show();

  auto vvlay = new QVBoxLayout;
  vvlay->addLayout(hhlay);
  vvlay->addWidget(m_widget);

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_menuView);
  hlay->addLayout(vvlay);
}

void YDDTaskWidget::slotStartClick(bool) {
  auto index = m_menuView->currentIndex();
  YDTask *o = reinterpret_cast<YDTask *>(index.internalPointer());
  if (o) {
    std::string xmlstr;
    m_id = o->id();
    YDProjectManage::getTaskXmlizedProcesses(m_id, xmlstr);
    YDDgHelper::startLogicTaskDebug(m_id, xmlstr);
  }
}

void YDDTaskWidget::slotStopClick(bool) {
  YDDgHelper::stopLogicTaskDebug(m_id);
}
