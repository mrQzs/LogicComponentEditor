#include "YDModuleIFElseWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

#include "YDModuleConditionWidget.h"
#include "YDModuleHead.h"
#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "debug/YDDgHelper.h"
#include "model/YDModulePropModel.h"
#include "modules/YDModules.h"

YDModuleIFElseWidget::YDModuleIFElseWidget(YDModule *m, QWidget *parent)
    : QWidget{parent},
      m_root{m},
      m_head1{new YDModuleHead(m, this)},
      m_head2{new YDModuleHead(m, this)},
      m_ifWidget{new YDModuleConditionWidget(m, this)},
      m_elseWidget{new YDModuleConditionWidget(m, this)},
      m_isHide1{false},
      m_isHide2{false} {
  setStyleSheet("border:none;");

  auto hlay = new QHBoxLayout;
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->addSpacing(20);
  hlay->addWidget(m_ifWidget);

  auto hlay2 = new QHBoxLayout;
  hlay2->setContentsMargins(0, 0, 0, 0);
  hlay2->addSpacing(20);
  hlay2->addWidget(m_elseWidget);

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(0, 0, 0, 2);
  vlay->setSpacing(0);
  vlay->addWidget(m_head1);
  vlay->addLayout(hlay);
  vlay->addWidget(m_head2);
  vlay->addLayout(hlay2);

  connect(m_head1, &YDModuleHead::sigClicked, this,
          &YDModuleIFElseWidget::slotShow1);

  connect(m_head2, &YDModuleHead::sigClicked, this,
          &YDModuleIFElseWidget::slotShow2);

  connect(m_ifWidget, &YDModuleConditionWidget::addNew, this,
          &YDModuleIFElseWidget::slotAddNew);
  connect(m_elseWidget, &YDModuleConditionWidget::addNew, this,
          &YDModuleIFElseWidget::slotAddNew);
}

int YDModuleIFElseWidget::high() const {
  int labh = 180;
  int count1 = m_ifWidget->realCount();
  int count2 = m_elseWidget->realCount();

  if (m_isHide1 && m_isHide2)
    return 60;
  else if (m_isHide1 && !m_isHide2)
    return labh + 30 + count2 * 30;
  else if (!m_isHide1 && m_isHide2)
    return labh + count1 * 30 + 30;

  return labh + count1 * 30 + count2 * 30;
}

void YDModuleIFElseWidget::init() {
  auto str1 = m_root->name() + "  " + YDModuleIFElseWidget::tr("为真时");
  auto str2 = m_root->name() + "  " + YDModuleIFElseWidget::tr("为假时");

  m_head1->setText(str1);
  m_head2->setText(str2);

  m_head1->setBgColor("#ec9400");
  m_head1->setFtColor("#ffffff");

  m_head2->setBgColor("#ec9400");
  m_head2->setFtColor("#ffffff");

  m_ifWidget->setTask(m_root->getYDTask());
  m_elseWidget->setTask(m_root->getYDTask());
}

void YDModuleIFElseWidget::setText(const QString &text) {
  auto str1 = text + "  " + YDModuleIFElseWidget::tr("为真时");
  auto str2 = text + "  " + YDModuleIFElseWidget::tr("为假时");

  m_head1->setText(str1);
  m_head2->setText(str2);
}

void YDModuleIFElseWidget::resizeModule() {
  YDHelper::resizeModel(m_ifWidget);
  YDHelper::resizeModel(m_elseWidget);
}

QList<uint32> YDModuleIFElseWidget::getTrueProcessIds(uint32 id) {
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

QList<uint32> YDModuleIFElseWidget::getFalseProcessIds(uint32 id) {
  QList<uint32> list;
  for (int i = 0; i < m_elseWidget->count(); ++i) {
    auto item = m_elseWidget->item(i);
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(item->data(Qt::UserRole));
    auto m = cast.ptr;
    m->setParentId(id);

    if (0 == i) {
      m->setPreviousId(0);
      if (m_elseWidget->count() > 1) {
        YDModuleCast nextcast;
        nextcast.i = qvariant_cast<qintptr>(
            m_elseWidget->item(i + 1)->data(Qt::UserRole));
        m->setNextId(nextcast.ptr->getLogicProcessId());
      }
    } else if (i > 0 && i <= m_elseWidget->count() - 2) {
      YDModuleCast precast;
      YDModuleCast nextcast;
      precast.i =
          qvariant_cast<qintptr>(m_elseWidget->item(i - 1)->data(Qt::UserRole));
      nextcast.i =
          qvariant_cast<qintptr>(m_elseWidget->item(i + 1)->data(Qt::UserRole));

      m->setPreviousId(precast.ptr->getLogicProcessId());
      m->setNextId(nextcast.ptr->getLogicProcessId());
    } else {
      YDModuleCast precast;
      precast.i =
          qvariant_cast<qintptr>(m_elseWidget->item(i - 1)->data(Qt::UserRole));
      m->setPreviousId(precast.ptr->getLogicProcessId());
      m->setNextId(0);
    }

    m->getData();

    list << m->getLogicProcessId();
  }
  return list;
}

void YDModuleIFElseWidget::addTrueModules(
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

void YDModuleIFElseWidget::addFalseModules(
    YDTask *task, const std::vector<yd::lg::LogicProcess *> &list) {
  for (auto lp : list) {
    auto m = YDProjectManage::getModule(lp->type);
    if (m) {
      m->initModule(lp);
      m->setTask(task);
      m_elseWidget->addModule(m);
    }
  }
}

void YDModuleIFElseWidget::setState(const QMap<uint32, yd::proto::ProcState> &map) {
  for (int i = 0; i < m_ifWidget->count(); ++i) {
    auto item = m_ifWidget->item(i);
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(item->data(Qt::UserRole));
    auto m = cast.ptr;
    auto state = map[m->getLogicProcessId()];
    m->setDebugState(state);
  }

  for (int i = 0; i < m_elseWidget->count(); ++i) {
    auto item = m_elseWidget->item(i);
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

void YDModuleIFElseWidget::paintEvent(QPaintEvent *) {
  QPainter p(this);

  auto W = width();
  auto H = height();

  p.save();
  p.setPen(Qt::NoPen);
  p.setBrush(QBrush(QColor("#ec9400")));
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

  p.end();
}

void YDModuleIFElseWidget::slotAddNew() { emit sizeNeedChanged(m_root); }

void YDModuleIFElseWidget::slotShow1(bool b) {
  if (b) {
    m_ifWidget->hide();
  } else {
    m_ifWidget->show();
  }

  m_isHide1 = b;
  m_root->getYDTask()->resizeModel();
}

void YDModuleIFElseWidget::slotShow2(bool b) {
  if (b) {
    m_elseWidget->hide();
  } else {
    m_elseWidget->show();
  }

  m_isHide2 = b;
  m_root->getYDTask()->resizeModel();
}
