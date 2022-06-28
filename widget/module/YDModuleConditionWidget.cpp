#include "YDModuleConditionWidget.h"

#include <QDataStream>
#include <QDrag>
#include <QDragEnterEvent>
#include <QLabel>
#include <QListWidgetItem>
#include <QMenu>
#include <QMessageBox>
#include <QMimeData>

#include "YDIfConditionWidget.h"
#include "YDModuleIFElseWidget.h"
#include "YDModuleLoopWidget.h"
#include "YDModuleWidget.h"
#include "common/YDGlobal.h"
#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "model/YDModulePropModel.h"
#include "modules/YDModule.h"

YDModuleConditionWidget::YDModuleConditionWidget(YDModule *m, QWidget *parent)
    : QListWidget{parent},
      m_menu{new QMenu(this)},
      m_module{m},
      m_task{nullptr} {
  setDragEnabled(true);
  setAcceptDrops(true);
  setViewMode(QListView::ListMode);
  setResizeMode(QListWidget::Adjust);

  setContextMenuPolicy(Qt::CustomContextMenu);

  m_menu->addAction(QIcon(":/Icon/delete.png"),
                    YDModuleConditionWidget::tr("删除组件"), this,
                    SLOT(slotRemoveModule(bool)));

  connect(this, &YDModuleConditionWidget::customContextMenuRequested, this,
          &YDModuleConditionWidget::slotMenu);
  connect(this, &YDModuleConditionWidget::itemClicked, this,
          &YDModuleConditionWidget::slotItemClick);
}

QString YDModuleConditionWidget::mimeType() {
  return QStringLiteral("YD/DragModule");
}

void YDModuleConditionWidget::addModule(YDModule *m, int row) {
  QListWidgetItem *Item = nullptr;
  if (-1 == row)
    Item = new QListWidgetItem(this);
  else
    Item = new QListWidgetItem();

  YDModuleCast cast;
  cast.ptr = m;
  Item->setSizeHint(QSize(width() - 4, m->high()));
  Item->setData(Qt::UserRole, cast.i);
  switch (m->type()) {
    case Module::If_Condition: {
      auto w = static_cast<YDIfConditionWidget *>(m->widget());
      w->init();
      connect(w, SIGNAL(sizeNeedChanged(YDModule *)), this,
              SLOT(slotChangeItemSize(YDModule *)));
    } break;
    case Module::IfElse_Condition: {
      auto w = static_cast<YDModuleIFElseWidget *>(m->widget());
      w->init();
      connect(w, SIGNAL(sizeNeedChanged(YDModule *)), this,
              SLOT(slotChangeItemSize(YDModule *)));
    } break;
    case Module::Times_Loop: {
      auto w = static_cast<YDModuleLoopWidget *>(m->widget());
      connect(w, SIGNAL(sizeNeedChanged(YDModule *)), this,
              SLOT(slotChangeItemSize(YDModule *)));
      w->init();
    } break;
    case Module::Condition_Loop: {
      auto w = static_cast<YDModuleLoopWidget *>(m->widget());
      connect(w, SIGNAL(sizeNeedChanged(YDModule *)), this,
              SLOT(slotChangeItemSize(YDModule *)));
      w->init();
    } break;
    default: {
      auto w = static_cast<YDModuleWidget *>(m->widget());
      w->setText(m->name());
    } break;
  }

  if (-1 != row) {
    insertItem(row, Item);
  }
  setItemWidget(Item, m->widget());
  emit addNew();
}

void YDModuleConditionWidget::insertModule(YDModule *m, int row) {
  QListWidgetItem *Item = nullptr;
  if (-1 == row)
    Item = new QListWidgetItem(this);
  else
    Item = new QListWidgetItem();

  YDModuleCast cast;
  cast.ptr = m;
  Item->setSizeHint(QSize(width() - 4, m->high()));
  Item->setData(Qt::UserRole, cast.i);

  if (-1 != row) {
    insertItem(row, Item);
  }
  setItemWidget(Item, m->widget());
  emit addNew();
}

void YDModuleConditionWidget::setTask(YDTask *task) { m_task = task; }

int YDModuleConditionWidget::realCount() {
  int c = 0;
  for (int i = 0; i < count(); ++i) {
    auto it = item(i);
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(it->data(Qt::UserRole));
    auto m = cast.ptr;
    if (!m) continue;
    switch (m->type()) {
      case Module::IfElse_Condition:
        c += m->high() / 30;
        break;
      case Module::Times_Loop:
        c += m->high() / 30;
        break;
      case Module::Condition_Loop:
        c += m->high() / 30;
        break;
      default: {
        c += m->high() / 30;
      } break;
    }
  }
  return c;
  // 60.91 337.0266.5
}

void YDModuleConditionWidget::resizeModule() { YDHelper::resizeModel(this); }

void YDModuleConditionWidget::dragEnterEvent(QDragEnterEvent *e) {
  if (e->mimeData()->hasFormat(YDModuleConditionWidget::mimeType()))
    e->accept();
  else if (e->mimeData()->hasFormat(QStringLiteral("YD/Module")))
    e->accept();
  else
    e->ignore();
}

void YDModuleConditionWidget::dragMoveEvent(QDragMoveEvent *e) {
  if (e->mimeData()->hasFormat(YDModuleConditionWidget::mimeType())) {
    e->setDropAction(Qt::MoveAction);
    e->accept();
  } else if (e->mimeData()->hasFormat(QStringLiteral("YD/Module"))) {
    e->setDropAction(Qt::CopyAction);
    e->accept();
  } else
    e->ignore();
}

void YDModuleConditionWidget::dropEvent(QDropEvent *e) {
  if (e->mimeData()->hasFormat(YDModuleConditionWidget::mimeType())) {
    YDModuleCast cast;
    QByteArray encoded =
        e->mimeData()->data(YDModuleConditionWidget::mimeType());
    QDataStream stream(&encoded, QIODeviceBase::ReadOnly);
    stream >> cast.i;
    auto module = cast.ptr;
    auto pos = e->position().toPoint();

    auto pid = module->getParentId();
    if (module->type() == Module::Jump_Loop) {
      module->setParentId(m_module->getLogicProcessId());
    }
    if (module->isValid()) {
      insertModule(module, indexAt(pos).row());
      m_module->getYDTask()->resizeModel();
      e->accept();
    } else {
      QMessageBox::warning(
          this, YDModuleConditionWidget::tr("提示"),
          YDModuleConditionWidget::tr("跳出循环控件只能添加到循环控件里面!"));
      module->setParentId(pid);
      e->ignore();
    }
  } else if (e->mimeData()->hasFormat(QStringLiteral("YD/Module"))) {
    YDModuleCast cast;
    QByteArray encoded = e->mimeData()->data("YD/Module");
    QDataStream stream(&encoded, QIODeviceBase::ReadOnly);
    stream >> cast.i;
    auto module = cast.ptr;
    module->initModule(m_task, m_module->getLogicProcessId());

    if (module->isValid()) {
      auto pos = e->position().toPoint();
      addModule(module, indexAt(pos).row());
    } else {
      QMessageBox::warning(
          nullptr, YDModuleConditionWidget::tr("提示"),
          YDModuleConditionWidget::tr("跳出循环控件只能添加到循环控件里面!"));
      module->release();
      delete module;
    }
    m_module->getYDTask()->resizeModel();
    e->accept();
  } else
    e->ignore();
}

void YDModuleConditionWidget::startDrag(Qt::DropActions) {
  QListWidgetItem *item = currentItem();

  YDModuleCast cast;
  QByteArray encoded;
  QDataStream stream(&encoded, QIODeviceBase::WriteOnly);
  cast.i = qvariant_cast<qintptr>(item->data(Qt::UserRole));
  auto m = cast.ptr;
  stream << cast.i;

  QMimeData *mimeData = new QMimeData;
  mimeData->setData(YDModuleConditionWidget::mimeType(), encoded);

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setHotSpot({0, 0});

  switch (m->type()) {
    case Module::IfElse_Condition:
    case Module::Times_Loop:
    case Module::Condition_Loop: {
      drag->setPixmap(m->preview(1));
    } break;
    default: {
      drag->setPixmap(m->preview());
    } break;
  }

  if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
    auto w = itemWidget(item);
    delete takeItem(row(item));
    QCoreApplication::removePostedEvents(w);
  }
}

Qt::DropActions YDModuleConditionWidget::supportedDropActions() const {
  return Qt::CopyAction;
}

void YDModuleConditionWidget::slotMenu(const QPoint &pos) {
  auto index = indexAt(pos);
  if (index.isValid()) m_menu->exec(QCursor::pos());
}

void YDModuleConditionWidget::slotRemoveModule(bool) {
  auto index = currentIndex();
  if (index.isValid()) {
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(index.data(Qt::UserRole));
    cast.ptr->getData();

    auto rb =
        QMessageBox::information(this, YDModuleConditionWidget::tr("提示"),
                                 YDModuleConditionWidget::tr("是否删除?"),
                                 YDModuleConditionWidget::tr("确认"),
                                 YDModuleConditionWidget::tr("取消"));

    if (0 == rb) {
      delete takeItem(index.row());
      YDHelper::getModPropModel()->setModule(nullptr);
      cast.ptr->release();
      delete cast.ptr;
      selectModule = nullptr;
    }
  }
}

void YDModuleConditionWidget::slotItemClick(QListWidgetItem *item) {
  YDModuleCast cast;
  cast.i = qvariant_cast<qintptr>(item->data(Qt::UserRole));
  cast.ptr->getData();
  auto m = selectModule;
  selectModule = cast.ptr;
  YDHelper::getModPropModel()->setModule(cast.ptr);
  if (m) m->widget()->update();
  selectModule->widget()->update();
}

void YDModuleConditionWidget::slotChangeItemSize(YDModule *m) {
  for (int i = 0; i < count(); ++i) {
    auto it = item(i);
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(it->data(Qt::UserRole));
    if (m == cast.ptr) {
      it->setSizeHint(QSize(width() - 4, m->high()));
      break;
    }
  }
}
