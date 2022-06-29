#include "YDReciVariableModel.h"

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "widget/YDDTComboBox.h"
#include "widget/YDNameLineEdit.h"

YDReciVariableModel::YDReciVariableModel(QObject *parent)
    : QAbstractTableModel{parent} {}

void YDReciVariableModel::updateData() {
  beginResetModel();
  endResetModel();
}

QVariant YDReciVariableModel::headerData(int section,
                                         Qt::Orientation orientation,
                                         int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return YDReciVariableModel::tr("名称");
      case 1:
        return YDReciVariableModel::tr("数值类型");
      case 2:
        return YDReciVariableModel::tr("配方值");
      case 3:
        return YDReciVariableModel::tr("最小值");
      case 4:
        return YDReciVariableModel::tr("最大值");
      default:
        break;
    }
  }
  return QVariant();
}

int YDReciVariableModel::rowCount(const QModelIndex &) const {
  return (int)YDProjectManage::GetGroupedReciVars(m_groupId).size();
}

int YDReciVariableModel::columnCount(const QModelIndex &parent) const {
  return 5;
}

QVariant YDReciVariableModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  auto list = YDProjectManage::GetGroupedReciVars(m_groupId);

  if (index.row() >= list.size() || index.row() < 0) return QVariant();

  if (role == Qt::DisplayRole) {
    const auto &var = list.at(index.row());

    switch (index.column()) {
      case 0:
        return STRTQSTR(var->variable_name.c_str());
      case 1:
        return YDHelper::getDataType(var->value_type);
      case 2:
        return STRTQSTR(var->current_value.c_str());
      case 3:
        return STRTQSTR(var->min_value.c_str());
      case 4:
        return STRTQSTR(var->max_value.c_str());
      default:
        break;
    }
  }
  return QVariant();
}

bool YDReciVariableModel::setData(const QModelIndex &index,
                                  const QVariant &value, int role) {
  if (index.isValid() && role == Qt::EditRole) {
    auto list = YDProjectManage::GetGroupedReciVars(m_groupId);
    if (index.row() >= list.size() || index.row() < 0) return false;

    const auto &var = list.at(index.row());

    switch (index.column()) {
      case 0:
        if (!value.toString().isEmpty())
          var->variable_name =
              std::string(value.toString().toLocal8Bit().data());
        break;
      case 1:
        if (!value.toString().isEmpty())
          var->value_type = YDHelper::getDataTypeIndex(value.toString());
        break;
      case 2:
        if (!value.toString().isEmpty())
          var->init_value = value.toString().toStdString();
        break;
      case 3:
        if (!value.toString().isEmpty())
          var->min_value = value.toString().toStdString();
        break;
      case 4:
        if (!value.toString().isEmpty())
          var->max_value = value.toString().toStdString();
        break;
      default:
        break;
    }

    return true;
  }

  return false;
}

Qt::ItemFlags YDReciVariableModel::flags(const QModelIndex &) const {
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void YDReciVariableModel::setGroupId(uint16 id) {
  m_groupId = id;
  beginResetModel();
  endResetModel();
}
