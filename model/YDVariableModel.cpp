#include "YDVariableModel.h"

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "widget/YDDTComboBox.h"
#include "widget/YDNameLineEdit.h"

YDVariableModel::YDVariableModel(QObject *parent)
    : QAbstractTableModel{parent} {}

QVariant YDVariableModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return YDVariableModel::tr("名称");
      case 1:
        return YDVariableModel::tr("数值类型");
      case 2:
        return YDVariableModel::tr("初始值");
      case 3:
        return YDVariableModel::tr("最小值");
      case 4:
        return YDVariableModel::tr("最大值");
      default:
        break;
    }
  }
  return QVariant();
}

int YDVariableModel::rowCount(const QModelIndex &) const {
  return (int)YDProjectManage::GetGroupedGlobalVars(m_groupId).size();
}

int YDVariableModel::columnCount(const QModelIndex &parent) const { return 5; }

QVariant YDVariableModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  auto list = YDProjectManage::GetGroupedGlobalVars(m_groupId);

  if (index.row() >= list.size() || index.row() < 0) return QVariant();

  if (role == Qt::DisplayRole) {
    const auto &var = list.at(index.row());

    switch (index.column()) {
      case 0:
        return QString::fromLocal8Bit(var->variable_name.c_str());
      case 1:
        return YDHelper::getDataType(var->value_type);
      case 2:
        return QString::fromLocal8Bit(var->init_value.c_str());
      case 3:
        return QString::fromLocal8Bit(var->min_value.c_str());
      case 4:
        return QString::fromLocal8Bit(var->max_value.c_str());
      default:
        break;
    }
  }
  return QVariant();
}

bool YDVariableModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
  if (index.isValid() && role == Qt::EditRole) {
    auto list = YDProjectManage::GetGroupedGlobalVars(m_groupId);
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

Qt::ItemFlags YDVariableModel::flags(const QModelIndex &) const {
  return Qt::ItemIsEnabled;
}

void YDVariableModel::setGroupId(uint16 id) {
  m_groupId = id;
  beginResetModel();
  endResetModel();
}
