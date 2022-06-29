#include "YDSafeVariableModel.h"

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "widget/YDDTComboBox.h"
#include "widget/YDNameLineEdit.h"

YDSafeVariableModel::YDSafeVariableModel(QObject *parent)
    : QAbstractTableModel{parent} {}

QVariant YDSafeVariableModel::headerData(int section,
                                         Qt::Orientation orientation,
                                         int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return YDSafeVariableModel::tr("名称");
      case 1:
        return YDSafeVariableModel::tr("逻辑运算符");
      case 2:
        return YDSafeVariableModel::tr("判定条件");
      default:
        break;
    }
  }
  return QVariant();
}

int YDSafeVariableModel::rowCount(const QModelIndex &parent) const {
  return (int)YDProjectManage::getGroupedSafeVariables(m_groupId).size();
}

int YDSafeVariableModel::columnCount(const QModelIndex &) const { return 3; }

QVariant YDSafeVariableModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  auto list = YDProjectManage::getGroupedSafeVariables(m_groupId);

  if (index.row() >= list.size() || index.row() < 0) return QVariant();

  if (role == Qt::DisplayRole) {
    const auto &var = list.at(index.row());

    switch (index.column()) {
      case 0:
        return STRTQSTR(var->variable_name.c_str());
      case 1: {
        QString str;
        if (LOGIC_OPERATOR_AND == var->logic_operator)
          str = YDSafeVariableModel::tr("与");
        else
          str = YDSafeVariableModel::tr("或");
        return str;
      }
      case 2:
        return "...";
      default:
        break;
    }
  }
  return QVariant();
}

Qt::ItemFlags YDSafeVariableModel::flags(const QModelIndex &index) const {
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void YDSafeVariableModel::setGroupId(uint16 id) {
  m_groupId = id;
  beginResetModel();
  endResetModel();
}
