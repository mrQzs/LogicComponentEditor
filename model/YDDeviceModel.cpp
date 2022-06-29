#include "YDDeviceModel.h"

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"

YDDeviceModel::YDDeviceModel(QObject *parent) : QAbstractListModel{parent} {}

YDDeviceModel::~YDDeviceModel() {}

QVariant YDDeviceModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const {
  if ((Qt::Horizontal != orientation) || (Qt::DisplayRole != role))
    return QVariant();

  if (0 == section) return YDDeviceModel::tr("设备列表");

  return QVariant();
}

int YDDeviceModel::rowCount(const QModelIndex &) const {
  return (int)YDProjectManage::getMotionDevices().size();
}

QVariant YDDeviceModel::data(const QModelIndex &index, int role) const {
  auto list = YDProjectManage::getMotionDevices();
  if (Qt::DisplayRole == role) return STRTQSTR(list[index.row()]->base.name);
  return QVariant();
}
