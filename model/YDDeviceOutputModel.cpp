#include "YDDeviceOutputModel.h"

#include <QComboBox>

#include "common/YDHelper.h"
#include "widget/YDNameLineEdit.h"

YDDeviceOutputModel::YDDeviceOutputModel(QObject *parent)
    : QAbstractTableModel{parent} {}

QVariant YDDeviceOutputModel::headerData(int section,
                                         Qt::Orientation orientation,
                                         int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return YDDeviceOutputModel::tr("组类型");
      case 1:
        return YDDeviceOutputModel::tr("序号");
      case 2:
        return YDDeviceOutputModel::tr("名称");
      case 3:
        return YDDeviceOutputModel::tr("是否启用");
      case 4:
        return YDDeviceOutputModel::tr("是否反转");
      case 5:
        return YDDeviceOutputModel::tr("标识");
      case 6:
        return YDDeviceOutputModel::tr("备注");
      default:
        break;
    }
  }

  return QVariant();
}

int YDDeviceOutputModel::rowCount(const QModelIndex &) const {
  int size = 0;
  for (auto o : m_doList) {
    size += (int)o->listDOs.size();
  }
  return size;
}

int YDDeviceOutputModel::columnCount(const QModelIndex &parent) const {
  return 7;
}

QVariant YDDeviceOutputModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  int size = 0;
  for (auto o : m_doList) {
    size += (int)o->listDOs.size();
  }

  if (index.row() >= size || index.row() < 0) return QVariant();

  auto column = index.column();
  int groupIndex = getGroupIndex(index.row());
  const auto &var = getMCDO(index.row());

  switch (column) {
    case 0:
      if (role == Qt::DisplayRole) switch (m_doList[groupIndex]->type) {
          case DITYPE_GENERAL:
            return YDDeviceOutputModel::tr("通用输出");
          case DITYPE_POSITIVE_LIMIT:
            return YDDeviceOutputModel::tr("驱动使能");
          case DITYPE_NEGATIVE_LIMIT:
            return YDDeviceOutputModel::tr("报警清除");
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
        return YDDeviceOutputModel::tr("是");
      break;
    case 4:
      if (role == Qt::CheckStateRole)
        return var->reverse;
      else if (role == Qt::DisplayRole)
        return YDDeviceOutputModel::tr("是");
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

bool YDDeviceOutputModel::setData(const QModelIndex &index,
                                  const QVariant &value, int role) {
  int size = 0;
  for (auto o : m_doList) {
    size += (int)o->listDOs.size();
  }

  if (index.row() >= size || index.row() < 0) return false;

  auto column = index.column();
  const auto &var = getMCDO(index.row());

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

Qt::ItemFlags YDDeviceOutputModel::flags(const QModelIndex &index) const {
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

void YDDeviceOutputModel::updateModel(
    const std::vector<yd::dev::MCDOGroup *> &list) {
  m_doList = list;
  beginResetModel();
  endResetModel();
}

void YDDeviceOutputModel::cleaerModel() {
  m_doList.clear();
  beginResetModel();
  endResetModel();
}

int YDDeviceOutputModel::getGroupIndex(int index) const {
  int i = 0;
  ++index;

  for (; i < m_doList.size(); ++i) {
    if (index <= m_doList[i]->listDOs.size())
      break;
    else
      index -= (int)m_doList[i]->listDOs.size();
  }
  if (i > m_doList.size()) --i;

  return i;
}

yd::dev::MCDO *YDDeviceOutputModel::getMCDO(int index) const {
  int i = 0;
  ++index;
  for (; i < m_doList.size(); ++i) {
    if (index <= m_doList[i]->listDOs.size())
      break;
    else
      index -= (int)m_doList[i]->listDOs.size();
  }
  if (i >= m_doList.size()) --i;
  return m_doList[i]->listDOs[--index];
}

QSize YDDeviceOutputDelegate::sizeHint(const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const {
  return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *YDDeviceOutputDelegate::createEditor(
    QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
  switch (index.column()) {
    case 3:
    case 4:
      return QStyledItemDelegate::createEditor(parent, option, index);
    default: {
      auto *editor = new QLineEdit(parent);
      connect(editor, &QLineEdit::editingFinished, this,
              &YDDeviceOutputDelegate::commitAndCloseEditor2);
      return editor;
    }
  }

  return QStyledItemDelegate::createEditor(parent, option, index);
}

void YDDeviceOutputDelegate::setEditorData(QWidget *editor,
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

void YDDeviceOutputDelegate::setModelData(QWidget *editor,
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

void YDDeviceOutputDelegate::commitAndCloseEditor() {
  auto *ed = static_cast<QComboBox *>(sender());
  emit commitData(ed);
  emit closeEditor(ed);
}

void YDDeviceOutputDelegate::commitAndCloseEditor2() {
  auto *ed = static_cast<QLineEdit *>(sender());
  emit commitData(ed);
  emit closeEditor(ed);
}
