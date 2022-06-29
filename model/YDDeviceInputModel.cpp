#include "YDDeviceInputModel.h"

#include <QComboBox>

#include "common/YDHelper.h"
#include "widget/YDNameLineEdit.h"

YDDeviceInputModel::YDDeviceInputModel(QObject *parent)
    : QAbstractTableModel{parent} {}

QVariant YDDeviceInputModel::headerData(int section,
                                        Qt::Orientation orientation,
                                        int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return YDDeviceInputModel::tr("组类型");
      case 1:
        return YDDeviceInputModel::tr("序号");
      case 2:
        return YDDeviceInputModel::tr("名称");
      case 3:
        return YDDeviceInputModel::tr("是否启用");
      case 4:
        return YDDeviceInputModel::tr("是否反转");
      case 5:
        return YDDeviceInputModel::tr("标识");
      case 6:
        return YDDeviceInputModel::tr("备注");
      default:
        break;
    }
  }

  return QVariant();
}

int YDDeviceInputModel::rowCount(const QModelIndex &parent) const {
  int size = 0;
  for (auto o : m_diList) {
    size += (int)o->listDIs.size();
  }
  return size;
}

int YDDeviceInputModel::columnCount(const QModelIndex &parent) const {
  return 7;
}

QVariant YDDeviceInputModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  int size = 0;
  for (auto o : m_diList) {
    size += (int)o->listDIs.size();
  }

  if (index.row() >= size || index.row() < 0) return QVariant();

  auto column = index.column();
  int groupIndex = getGroupIndex(index.row());
  const auto &var = getMCDI(index.row());

  switch (column) {
    case 0:
      if (role == Qt::DisplayRole) switch (m_diList[groupIndex]->type) {
          case DITYPE_GENERAL:
            return YDDeviceInputModel::tr("通用输入");
          case DITYPE_POSITIVE_LIMIT:
            return YDDeviceInputModel::tr("正向限位");
          case DITYPE_NEGATIVE_LIMIT:
            return YDDeviceInputModel::tr("负向限位");
          case DITYPE_DRIVER_ALARM:
            return YDDeviceInputModel::tr("驱动报警");
          case DITYPE_HOME_SIGNAL:
            return YDDeviceInputModel::tr("原点信号");
          case DITYPE_MOTOR_ARRIVE:
            return YDDeviceInputModel::tr("电机到位");
        }
      break;
    case 1:
      if (role == Qt::DisplayRole) return QString::number(var->index);
      break;
    case 2:
      if (role == Qt::DisplayRole) return STRTQSTR(var->name);
      break;
    case 3:
      if (role == Qt::CheckStateRole)
        return var->enable;
      else if (role == Qt::DisplayRole)
        return YDDeviceInputModel::tr("是");
      break;
    case 4:
      if (role == Qt::CheckStateRole)
        return var->reverse;
      else if (role == Qt::DisplayRole)
        return YDDeviceInputModel::tr("是");
      break;
    case 5:
      if (role == Qt::DisplayRole) return STRTQSTR(var->label);
      break;
    case 6:
      if (role == Qt::DisplayRole) return STRTQSTR(var->remarks);
      break;
  }

  return QVariant();
}

bool YDDeviceInputModel::setData(const QModelIndex &index,
                                 const QVariant &value, int role) {
  int size = 0;
  for (auto o : m_diList) {
    size += (int)o->listDIs.size();
  }

  if (index.row() >= size || index.row() < 0) return false;

  auto column = index.column();
  const auto &var = getMCDI(index.row());

  switch (column) {
    case 2: {
      if (!value.toString().isEmpty())
        var->name = QSTRTSTR(value.toString());
    } break;
    case 3:
      var->enable = !var->enable;
      break;
    case 4:
      var->reverse = !var->reverse;
      break;
    case 5: {
      if (!value.toString().isEmpty())
        var->label = QSTRTSTR(value.toString());
    } break;
    case 6: {
      if (!value.toString().isEmpty())
        var->remarks = QSTRTSTR(value.toString());
    }
    default:
      break;
  }

  return true;
}

Qt::ItemFlags YDDeviceInputModel::flags(const QModelIndex &index) const {
  if (index.isValid()) {
    switch (index.column()) {
      case 0:
      case 1:
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
      case 3:
      case 4:
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
      default:
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
  } else
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void YDDeviceInputModel::updateModel(
    const std::vector<yd::dev::MCDIGroup *> &list) {
  m_diList = list;
  beginResetModel();
  endResetModel();
}

void YDDeviceInputModel::cleaerModel() {
  m_diList.clear();
  beginResetModel();
  endResetModel();
}

int YDDeviceInputModel::getGroupIndex(int index) const {
  int i = 0;
  ++index;
  for (; i < m_diList.size(); ++i) {
    if (index <= m_diList[i]->listDIs.size())
      break;
    else
      index -= (int)m_diList[i]->listDIs.size();
  }
  if (i >= m_diList.size()) --i;
  return i;
}

yd::dev::MCDI *YDDeviceInputModel::getMCDI(int index) const {
  int i = 0;
  ++index;
  for (; i < m_diList.size(); ++i) {
    if (index <= m_diList[i]->listDIs.size())
      break;
    else
      index -= (int)m_diList[i]->listDIs.size();
  }

  if (i >= m_diList.size()) --i;
  return m_diList[i]->listDIs[--index];
}

QSize YDDeviceInputDelegate::sizeHint(const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const {
  return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *YDDeviceInputDelegate::createEditor(QWidget *parent,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const {
  switch (index.column()) {
    case 3:
    case 4:
      return QStyledItemDelegate::createEditor(parent, option, index);
    default: {
      auto *editor = new QLineEdit(parent);
      connect(editor, &QLineEdit::editingFinished, this,
              &YDDeviceInputDelegate::commitAndCloseEditor2);
      return editor;
    }
  }

  return QStyledItemDelegate::createEditor(parent, option, index);
}

void YDDeviceInputDelegate::setEditorData(QWidget *editor,
                                          const QModelIndex &index) const {
  switch (index.column()) {
    case 3:
    case 4:
      break;
    default: {
      auto str = index.data().toString();
      auto *ed = static_cast<QLineEdit *>(editor);
      ed->setText(str);
    }
  }
}

void YDDeviceInputDelegate::setModelData(QWidget *editor,
                                         QAbstractItemModel *model,
                                         const QModelIndex &index) const {
  switch (index.column()) {
    case 3:
    case 4:
      break;
    default: {
      auto *ed = static_cast<QLineEdit *>(editor);
      model->setData(index, ed->text());
    }
  }
}

void YDDeviceInputDelegate::commitAndCloseEditor() {
  auto *ed = static_cast<QComboBox *>(sender());
  emit commitData(ed);
  emit closeEditor(ed);
}

void YDDeviceInputDelegate::commitAndCloseEditor2() {
  auto *ed = static_cast<QLineEdit *>(sender());
  emit commitData(ed);
  emit closeEditor(ed);
}
