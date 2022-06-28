#include "YDIOModel.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMimeData>
#include <QPushButton>

#include "common/YDGlobal.h"
#include "common/YDHelper.h"

YDIOModel::YDIOModel(QObject *parent) : QAbstractListModel{parent} {
  m_strlist << YDIOModel::tr("控制DO输出") << YDIOModel::tr("控制AO输出")
            << YDIOModel::tr("气油缸");
}

YDIOModel::~YDIOModel() {}

int YDIOModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_strlist.size();
}

QVariant YDIOModel::data(const QModelIndex &index, int role) const {
  if (Qt::DisplayRole == role)
    return m_strlist[index.row()];
  else if (Qt::DecorationRole == role)
    return QIcon(":/Module/Module.png");
  return QVariant();
}

Qt::ItemFlags YDIOModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);
  if (index.isValid())
    return Qt::ItemIsDragEnabled | defaultFlags;
  else
    return defaultFlags;
}

QStringList YDIOModel::mimeTypes() const {
  return QStringList() << "YD/Module";
}

QMimeData *YDIOModel::mimeData(const QModelIndexList &indexes) const {
  QMimeData *mimeData = new QMimeData();
  QByteArray encodedata;

  YDModuleCast cast;
  QDataStream stream(&encodedata, QIODeviceBase::WriteOnly);
  for (const QModelIndex &index : indexes) {
    if (index.isValid() && index.column() == 0) {
      Module::Type type = Module::Abs_Motion;
      switch (index.row()) {
        case 0:
          type = Module::Control_DO;
          break;
        case 1:
          type = Module::Control_AO;
          break;
        case 2:
          type = Module::Cylinder;
          break;
        default:
          break;
      }
      cast.ptr = YDHelper::getModule(type);
      stream << cast.i;
    }
  }

  mimeData->setData("YD/Module", encodedata);
  return mimeData;
}
