#include "YDModuleView.h"

#include <QDataStream>
#include <QDebug>
#include <QDrag>
#include <QMimeData>

#include "common/YDGlobal.h"
#include "modules/YDModule.h"

YDModuleView::YDModuleView(QWidget *parent) : QListView(parent) {
  setDragEnabled(true);
  setDragDropMode(QAbstractItemView::DragOnly);
}

void YDModuleView::startDrag(Qt::DropActions supportedActions) {
  const QModelIndexList indexes = selectedIndexes();
  QMimeData *mimeData = model()->mimeData(indexes);

  if (!mimeData->hasFormat("YD/Module"))
    return QListView::startDrag(supportedActions);
  YDModuleCast cast;
  QByteArray encoded = mimeData->data("YD/Module");
  QDataStream stream(&encoded, QIODeviceBase::ReadOnly);
  stream >> cast.i;
  YDModule *module = cast.ptr;

  QPixmap preview;
  preview = module->preview();

  if (!preview.isNull()) {
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(preview);
    drag->exec(supportedActions);

  } else {
    QListView::startDrag(supportedActions);
  }
}

void YDModuleView::dragEnterEvent(QEvent *) {}
