#include "YDAxisListModel.h"

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"

YDAxisListModel::YDAxisListModel(QObject *parent) : QAbstractListModel{parent} {
  updateData();
}

YDAxisListModel::~YDAxisListModel() {}

int YDAxisListModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return (int)m_strlist.size();
}

QVariant YDAxisListModel::data(const QModelIndex &index, int role) const {
  if (Qt::DisplayRole == role) return m_strlist[index.row()];
  return QVariant();
}

Qt::ItemFlags YDAxisListModel::flags(const QModelIndex &index) const {
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void YDAxisListModel::updateData() {
  m_strlist.clear();
  auto axis = YDProjectManage::getAxisList();
  for (auto a : axis) {
    QString name = STRTQSTR(a->axis_name.c_str());
    m_strlist.push_back(name);
  }
}
