#include "YDCylinderModel.h"

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"

YDCylinderModel::YDCylinderModel(QObject *parent)
    : QAbstractListModel{parent} {}

YDCylinderModel::~YDCylinderModel() {}

void YDCylinderModel::updateModel() {
  beginResetModel();
  endResetModel();
}

QVariant YDCylinderModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if ((Qt::Horizontal != orientation) || (Qt::DisplayRole != role))
    return QVariant();

  if (0 == section) return YDCylinderModel::tr("气油缸");

  return QVariant();
}

int YDCylinderModel::rowCount(const QModelIndex &) const {
  return (int)YDProjectManage::getCylinders().size();
}

QVariant YDCylinderModel::data(const QModelIndex &index, int role) const {
  auto list = YDProjectManage::getCylinders();
  if (Qt::DisplayRole == role) return STRTQSTR(list[index.row()]->base.name);
  return QVariant();
}
