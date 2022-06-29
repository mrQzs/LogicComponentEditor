#include "YDModuleLoopWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

#include "YDModuleConditionWidget.h"
#include "YDModuleHead.h"
#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "model/YDModulePropModel.h"
#include "modules/YDModules.h"

YDModuleLoopWidget::YDModuleLoopWidget(int type, YDModule *m, QWidget *parent)
    : QWidget{parent},
      m_type(type),
      m_root{m},
      m_head{new YDModuleHead(m, this)},
      m_loopWidget{new YDModuleConditionWidget(m, this)},
      m_isHide{false} {
  auto hlay = new QHBoxLayout;
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addSpacing(20);
  hlay->addWidget(m_loopWidget);

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(0, 0, 0, 2);
  vlay->setSpacing(0);
  vlay->addWidget(m_head);
  vlay->addLayout(hlay);

  connect(m_head, &YDModuleHead::sigClicked, this,
          &YDModuleLoopWidget::slotShow);

  connect(m_loopWidget, &YDModuleConditionWidget::addNew, this,
          &YDModuleLoopWidget::slotAddNew);
}

int YDModuleLoopWidget::high() const {
  int labh = 94;
  int count1 = m_loopWidget->realCount();

  if (m_isHide) return 30;

  return labh + count1 * 30;
}

void YDModuleLoopWidget::init() {
  // m_head->setIcon(m_root->icon());
  m_head->setText(m_root->name());

  if (0 == m_type)
    m_head->setBgColor("#1e6af8");
  else
    m_head->setBgColor("#2e6a10");

  m_head->setFtColor("#ffffff");

  m_loopWidget->setTask(m_root->getYDTask());
}

void YDModuleLoopWidget::setText(const QString &text) { m_head->setText(text); }

QList<uint32> YDModuleLoopWidget::getLoopModulesIds(uint32 id) {
  QList<uint32> list;
  for (int i = 0; i < m_loopWidget->count(); ++i) {
    auto item = m_loopWidget->item(i);
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(item->data(Qt::UserRole));
    auto m = cast.ptr;
    m->setParentId(id);

    if (0 == i) {
      m->setPreviousId(0);
      if (m_loopWidget->count() > 1) {
        YDModuleCast nextcast;
        nextcast.i = qvariant_cast<qintptr>(
            m_loopWidget->item(i + 1)->data(Qt::UserRole));
        m->setNextId(nextcast.ptr->getLogicProcessId());
      } else
        m->setNextId(0);
    } else if (i > 0 && i <= m_loopWidget->count() - 2) {
      YDModuleCast precast;
      YDModuleCast nextcast;
      precast.i =
          qvariant_cast<qintptr>(m_loopWidget->item(i - 1)->data(Qt::UserRole));
      nextcast.i =
          qvariant_cast<qintptr>(m_loopWidget->item(i + 1)->data(Qt::UserRole));

      m->setPreviousId(precast.ptr->getLogicProcessId());
      m->setNextId(nextcast.ptr->getLogicProcessId());
    } else {
      YDModuleCast precast;
      precast.i =
          qvariant_cast<qintptr>(m_loopWidget->item(i - 1)->data(Qt::UserRole));
      m->setPreviousId(precast.ptr->getLogicProcessId());
      m->setNextId(0);
    }

    m->getData();
    list << m->getLogicProcessId();
  }
  return list;
}

void YDModuleLoopWidget::resizeModel() { m_loopWidget->resizeModule(); }

void YDModuleLoopWidget::addLoopModules(
    YDTask *task, const std::vector<yd::lg::LogicProcess *> &list) {
  for (auto lp : list) {
    auto m = YDProjectManage::getModule(lp->type);
    if (m) {
      m->setTask(task);
      m->initModule(lp);
      m_loopWidget->addModule(m);
    }
  }
}

void YDModuleLoopWidget::setState(
    const QMap<uint32, yd::proto::ProcState> &map) {
  for (int i = 0; i < m_loopWidget->count(); ++i) {
    auto item = m_loopWidget->item(i);
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(item->data(Qt::UserRole));
    auto m = cast.ptr;
    auto state = map[m->getLogicProcessId()];
    m->setDebugState(state);
    switch (m->type()) {
      case Module::If_Condition:
      case Module::IfElse_Condition:
      case Module::Condition_Loop:
      case Module::Times_Loop:
        m->setStateMap(map);
        break;
      default:
        break;
    }
  }
}

void YDModuleLoopWidget::paintEvent(QPaintEvent *) {
  QPainter p(this);
  p.save();
  p.setPen(Qt::NoPen);

  if (0 == m_type)
    p.setBrush(QBrush(QColor("#1e6af8")));
  else
    p.setBrush(QBrush(QColor("#2e6a10")));

  auto W = width();
  auto H = height();

  p.drawRect(QRect(0, 0, 20, H - 3));
  p.restore();

  QPen pen("#4abcaf");
  pen.setWidth(3);
  p.setPen(pen);
  auto x = 3;
  auto y = H - 3;
  auto w = W - 3;
  auto h = H - 3;

  p.drawLine(x, y, w, h);
}

void YDModuleLoopWidget::slotAddNew() { emit sizeNeedChanged(m_root); }

void YDModuleLoopWidget::slotShow(bool b) {
  if (b)
    m_loopWidget->hide();
  else
    m_loopWidget->show();

  m_isHide = b;
  m_root->getYDTask()->resizeModel();
}
