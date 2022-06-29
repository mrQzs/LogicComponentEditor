#include "YDMoveModel.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMimeData>
#include <QPushButton>

#include "common/YDGlobal.h"
#include "common/YDHelper.h"

YDMoveModel::YDMoveModel(QObject *parent) : QAbstractListModel{parent} {
  m_strlist << YDMoveModel::tr("绝对运动") << YDMoveModel::tr("相对运动")
            << YDMoveModel::tr("Jog运动") << YDMoveModel::tr("多轴运动")
            << YDMoveModel::tr("停止运动") << YDMoveModel::tr("到位等待");
}

YDMoveModel::~YDMoveModel() {}

int YDMoveModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_strlist.size();
}

QVariant YDMoveModel::data(const QModelIndex &index, int role) const {
  if (Qt::DisplayRole == role)
    return m_strlist[index.row()];
  else if (Qt::DecorationRole == role)
    return QIcon(":/Module/ModuleS.png");
  return QVariant();
}

Qt::ItemFlags YDMoveModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);
  if (index.isValid())
    return Qt::ItemIsDragEnabled | defaultFlags;
  else
    return defaultFlags;
}

QStringList YDMoveModel::mimeTypes() const {
  return QStringList() << "YD/Module";
}

QMimeData *YDMoveModel::mimeData(const QModelIndexList &indexes) const {
  QMimeData *mimeData = new QMimeData();
  QByteArray encodedata;

  YDModuleCast cast;
  QDataStream stream(&encodedata, QIODeviceBase::WriteOnly);
  for (const QModelIndex &index : indexes) {
    if (index.isValid() && index.column() == 0) {
      Module::Type type = Module::Abs_Motion;
      switch (index.row()) {
        case 0:
          type = Module::Abs_Motion;
          break;
        case 1:
          type = Module::Rel_Motion;
          break;
        case 2:
          type = Module::Jog_Motion;
          break;
        case 3:
          type = Module::Mul_Motion;
          break;
        case 4:
          type = Module::Stop_Motion;
          break;
        case 5:
          type = Module::Wait_Motion;
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
