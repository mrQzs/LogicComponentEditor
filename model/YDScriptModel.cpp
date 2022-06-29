#include "YDScriptModel.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMimeData>
#include <QPushButton>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDScriptModel::YDScriptModel(QObject *parent) : QAbstractListModel{parent} {}

YDScriptModel::~YDScriptModel() {}

int YDScriptModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return (int)YDProjectManage::getScripts().size();
}

QVariant YDScriptModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  auto list = YDProjectManage::getScripts();
  int row = index.row();
  if (row < 0 || row >= list.size()) return QVariant();

  if (Qt::DisplayRole == role)
    return STRTQSTR(list[row]->script_name.c_str());
  else if (Qt::DecorationRole == role)
    return QIcon(":/Icon/subtask.png");

  return QVariant();
}

bool YDScriptModel::setData(const QModelIndex &index, const QVariant &value,
                            int role) {
  if (!index.isValid()) return false;

  auto list = YDProjectManage::getScripts();
  int row = index.row();
  if (row < 0 || row >= list.size()) return false;

  auto str = value.toString();
  if (!str.isEmpty()) {
    auto name = QSTRTSTR(str);

    if (Qt::DisplayRole == role) list[row]->script_name = name;
    return true;
  }

  return false;
}

Qt::ItemFlags YDScriptModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);
  return defaultFlags;
}

void YDScriptModel::updatedata() {
  beginResetModel();
  endResetModel();
}
