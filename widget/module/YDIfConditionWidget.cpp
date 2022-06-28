#include "YDIfConditionWidget.h"

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

YDIfConditionWidget::YDIfConditionWidget(YDModule *m, QWidget *parent)
    : QWidget{parent},
      m_root{m},
      m_head{new YDModuleHead(m, this)},
      m_ifWidget{new YDModuleConditionWidget(m, this)},
      m_isHide{false} {
  setStyleSheet("border:none;");

  auto hlay = new QHBoxLayout;
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addSpacing(20);
  hlay->addWidget(m_ifWidget);

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(0, 0, 0, 2);
  vlay->setSpacing(0);
  vlay->addWidget(m_head);
  vlay->addLayout(hlay);

  connect(m_head, &YDModuleHead::sigClicked, this,
          &YDIfConditionWidget::slotShow);

  connect(m_ifWidget, &YDModuleConditionWidget::addNew, this,
          &YDIfConditionWidget::slotAddNew);
}

int YDIfConditionWidget::high() const {
  int labh = 96;
  int count1 = m_ifWidget->realCount();
  if (m_isHide) return 30;

  return labh + count1 * 30;
}

void YDIfConditionWidget::init() {
  auto text = m_root->name() + "  " + YDIfConditionWidget::tr("为真时");
  m_head->setText(text);
  m_head->setBgColor("#939393");
  m_head->setFtColor("#ffffff");

  m_ifWidget->setTask(m_root->getYDTask());
}

void YDIfConditionWidget::setText(const QString &text) {
  auto str = text + "  " + YDIfConditionWidget::tr("为真时");
  m_head->setText(str);
}

void YDIfConditionWidget::resizeModule() { YDHelper::resizeModel(m_ifWidget); }

QList<uint32> YDIfConditionWidget::getTrueProcessIds(uint32 id) {
  QList<uint32> list;
  for (int i = 0; i < m_ifWidget->count(); ++i) {
    auto item = m_ifWidget->item(i);
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(item->data(Qt::UserRole));
    auto m = cast.ptr;
    m->setParentId(id);

    if (0 == i) {
      m->setPreviousId(0);
      if (m_ifWidget->count() > 1) {
        YDModuleCast nextcast;
        nextcast.i =
            qvariant_cast<qintptr>(m_ifWidget->item(i + 1)->data(Qt::UserRole));
        m->setNextId(nextcast.ptr->getLogicProcessId());
      }
    } else if (i > 0 && i <= m_ifWidget->count() - 2) {
      YDModuleCast precast;
      YDModuleCast nextcast;
      precast.i =
          qvariant_cast<qintptr>(m_ifWidget->item(i - 1)->data(Qt::UserRole));
      nextcast.i =
          qvariant_cast<qintptr>(m_ifWidget->item(i + 1)->data(Qt::UserRole));

      m->setPreviousId(precast.ptr->getLogicProcessId());
      m->setNextId(nextcast.ptr->getLogicProcessId());
    } else {
      YDModuleCast precast;
      precast.i =
          qvariant_cast<qintptr>(m_ifWidget->item(i - 1)->data(Qt::UserRole));
      m->setPreviousId(precast.ptr->getLogicProcessId());
      m->setNextId(0);
    }

    m->getData();
    list << m->getLogicProcessId();
  }
  return list;
}

void YDIfConditionWidget::addTrueModules(
    YDTask *task, const std::vector<yd::lg::LogicProcess *> &list) {
  for (auto lp : list) {
    auto m = YDProjectManage::getModule(lp->type);
    if (m) {
      m->setTask(task);
      m->initModule(lp);
      m_ifWidget->addModule(m);
    }
  }
}

void YDIfConditionWidget::setState(const QMap<uint32, yd::proto::ProcState> &map) {
  for (int i = 0; i < m_ifWidget->count(); ++i) {
    auto item = m_ifWidget->item(i);
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

void YDIfConditionWidget::paintEvent(QPaintEvent *) {
  QPainter p(this);
  p.save();
  p.setPen(Qt::NoPen);
  p.setBrush(QBrush(QColor("#939393")));

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

void YDIfConditionWidget::slotAddNew() { emit sizeNeedChanged(m_root); }

void YDIfConditionWidget::slotShow(bool b) {
  if (b)
    m_ifWidget->hide();
  else
    m_ifWidget->show();

  m_isHide = b;
  m_root->getYDTask()->resizeModel();
}
